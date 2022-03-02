/*
 * BroadcomTabKeyDetector.cpp
 *
 * Copyright 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <memory>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <AVSCommon/Utils/Logger/Logger.h>

#include "Broadcom/BroadcomTabKeyDetector.h"

namespace alexaClientSDK {
namespace kwd {


#define NUMBER_DIALLED_EVENT 101
#define EVENT_SENDER_ID      0x01
#define NOTIFY_HANDLER_ID    0x02
#define POLL_DELAY_MS        10
#define EPOLL_NUM_EVTS       5
#define PKT_BUFFER_SIZE      2048

using namespace avsCommon::utils::logger;

/// String to identify log entries originating from this file.
static const std::string TAG("BroadcomTabKeyDetector");

/**
 * Create a LogEntry using this file's TAG and the specified event string.
 *
 * @param The event string for this @c LogEntry.
 */
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

/// The timeout to use for read calls to the SharedDataStream.
const std::chrono::milliseconds TIMEOUT_FOR_READ_CALLS = std::chrono::milliseconds(1000);

/// The compatible endianness which is little endian.
static const avsCommon::utils::AudioFormat::Endianness SENSORY_COMPATIBLE_ENDIANNESS =
    avsCommon::utils::AudioFormat::Endianness::LITTLE;


std::unique_ptr<BroadcomTabKeyDetector> BroadcomTabKeyDetector::create(
    std::shared_ptr<avsCommon::avs::AudioInputStream> stream,
    std::unordered_set<std::shared_ptr<avsCommon::sdkInterfaces::KeyWordObserverInterface>> keyWordObservers,
    std::unordered_set<std::shared_ptr<avsCommon::sdkInterfaces::KeyWordDetectorStateObserverInterface>>
        keyWordDetectorStateObservers,
    std::chrono::milliseconds msDelayToReadTabKey) {
    if (!stream) {
        ACSDK_ERROR(LX("createFailed").d("reason", "nullStream"));
        return nullptr;
    }

    std::unique_ptr<BroadcomTabKeyDetector> detector(new BroadcomTabKeyDetector(
        stream, keyWordObservers, keyWordDetectorStateObservers));

    if (!detector->init()) {
        ACSDK_ERROR(LX("createFailed").d("reason", "initDetectorFailed"));
        return nullptr;
    }
    return detector;
}

BroadcomTabKeyDetector::~BroadcomTabKeyDetector() {
    m_isShuttingDown = true;
    if (m_detectionThread.joinable()) {
        m_detectionThread.join();
    }
}

BroadcomTabKeyDetector::BroadcomTabKeyDetector(
    std::shared_ptr<AudioInputStream> stream,
    std::unordered_set<std::shared_ptr<KeyWordObserverInterface>> keyWordObservers,
    std::unordered_set<std::shared_ptr<KeyWordDetectorStateObserverInterface>> keyWordDetectorStateObservers,
    std::chrono::milliseconds msToPushPerIteration) :
        AbstractKeywordDetector(keyWordObservers, keyWordDetectorStateObservers),
        m_stream{stream}
    {
}

bool BroadcomTabKeyDetector::init() {
    m_streamReader = m_stream->createReader(AudioInputStream::Reader::Policy::BLOCKING);
    if (!m_streamReader) {
        ACSDK_ERROR(LX("initFailed").d("reason", "createStreamReaderFailed"));
        return false;
    }

    m_isShuttingDown = false;
    m_detectionThread = std::thread(&BroadcomTabKeyDetector::detectionLoop, this);
    return true;
}

void BroadcomTabKeyDetector::detectionLoop() {
    notifyKeyWordDetectorStateObservers(KeyWordDetectorStateObserverInterface::KeyWordDetectorState::ACTIVE);

    const char* keyword = "ALEXA";
    int n;
    int connfd = 0;
    int pfd = 0;
    int sfd = 0;
    int listfd = 0;
    struct epoll_event evts[EPOLL_NUM_EVTS];
    struct epoll_event evt;
    char eventBuff[1025];
    struct sockaddr_in host_addr;
    int event = -1;

    ACSDK_DEBUG9(LX("Broadcom tabkey detector thread."));
    /* Open our epoll fd */
    pfd = epoll_create1(0);
    if (pfd < 0)
    {
        ACSDK_ERROR(LX("createFailed").d("reason", "initEpollFailed"));
        return;
    }

    listfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listfd == -1) {
        ACSDK_ERROR(LX("createFailed").d("reason", "initSocketFailed"));
        ::close(pfd);
        return;
    }

    memset(&host_addr, 0, sizeof(host_addr));

    host_addr.sin_family = AF_INET;
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    host_addr.sin_port = htons(34854);
    ACSDK_DEBUG9(LX("Broadcom tabkey detector: open socket").d("port", host_addr.sin_port));

    if( bind(listfd, (struct sockaddr*)&host_addr, sizeof(host_addr)) == -1) {
        ACSDK_ERROR(LX("createFailed").d("reason", "bindSocketFailed"));
        ::close(pfd);
        ::close(listfd);
        return;
    }

    if(listen(listfd, 10) == -1){
        ACSDK_ERROR(LX("createFailed").d("reason", "listenSocketFailed"));
        ::close(pfd);
        ::close(listfd);
        return;
    }

    ACSDK_INFO(LX("Broadcom tabkey detector: listen on port").d("port", host_addr.sin_port));
    evt.events   = EPOLLIN;
    evt.data.ptr = (void*)listfd;
    epoll_ctl(pfd, EPOLL_CTL_ADD, listfd, &evt);


    while (!m_isShuttingDown) {

        int status = epoll_wait(pfd, evts, EPOLL_NUM_EVTS, POLL_DELAY_MS );
        if (status <= 0)
        {
            continue;
        }

        ACSDK_DEBUG9(LX("Broadcom tabkey main loop"));
        /* Iterate through all detected events */
        for (int i = 0; i < status; i++)
        {
            if (!(evts[i].events & EPOLLIN))
            {
                continue;
            }

            sfd = (int)evts[i].data.ptr;
            if( sfd == listfd ){
                connfd = accept(sfd, (struct sockaddr*)NULL ,NULL);
                ACSDK_DEBUG9(LX("Broadcom tabkey accept connection"));
                if( connfd > 0 ){
                    evt.events   = EPOLLIN;
                    evt.data.ptr = (void*)connfd;
                    epoll_ctl(pfd, EPOLL_CTL_ADD, connfd, &evt);
                    continue;
                }
            }

            memset(eventBuff, '0', sizeof(eventBuff));

            while ((n = read(sfd, eventBuff, sizeof(eventBuff)-1))> 0) {

                eventBuff[n] = 0;
                event = atoi(eventBuff);
                switch (event) {
                    case NUMBER_DIALLED_EVENT :
                        ACSDK_INFO(LX("Broadcom socket received tab key cmd."));
                        m_beginIndexOfStreamReader = m_streamReader->tell();
                        notifyKeyWordObservers(
                            m_stream,
                            keyword,
                            avsCommon::sdkInterfaces::KeyWordObserverInterface::UNSPECIFIED_INDEX,
                            avsCommon::sdkInterfaces::KeyWordObserverInterface::UNSPECIFIED_INDEX);
                        break;
                default :
                    ACSDK_ERROR(LX("invalidCmd").d("reason", "invalidEvent"));
                }
            }
            ::close(sfd);
        }
    }
    m_streamReader->close();
    ::close(listfd);
    ::close(pfd);
}

}  // namespace kwd
}  // namespace alexaClientSDK
