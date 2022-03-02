/*
 * BroadcomTabKeyDetector.h
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ALEXA_CLIENT_SDK_KWD_BROADCOM_INCLUDE_KWD_BROADCOM_TAB_KEY_DETECTOR_H_
#define ALEXA_CLIENT_SDK_KWD_BROADCOM_INCLUDE_KWD_BROADCOM_TAB_KEY_DETECTOR_H_

#include <atomic>
#include <string>
#include <thread>
#include <unordered_set>

#include <AVSCommon/Utils/AudioFormat.h>
#include <AVSCommon/AVS/AudioInputStream.h>
#include <AVSCommon/SDKInterfaces/KeyWordObserverInterface.h>
#include <AVSCommon/SDKInterfaces/KeyWordDetectorStateObserverInterface.h>

#include "KWD/AbstractKeywordDetector.h"

namespace alexaClientSDK {
namespace kwd {

using namespace avsCommon;
using namespace avsCommon::avs;
using namespace avsCommon::sdkInterfaces;

class BroadcomTabKeyDetector : public AbstractKeywordDetector {
public:
    /**
     * Creates a @c BroadcomTabKeyDetector.
     *
     * @param stream The stream of audio data. This should be formatted in LPCM encoded with 16 bits per sample and
     * have a sample rate of 16 kHz. Additionally, the data should be in little endian format.
     * @param audioFormat The format of the audio data located within the stream.
     * @param keyWordObservers The observers to notify of keyword detections.
     * @param keyWordDetectorStateObservers The observers to notify of state changes in the engine.
     * @param modelFilePath The path to the model file.
     * @param msToPushPerIteration The amount of data in milliseconds to push to Sensory at a time. Smaller sizes will
     * lead to less delay but more CPU usage. Additionally, larger amounts of data fed into the engine per iteration
     * might lead longer delays before receiving keyword detection events. This has been defaulted to 10 milliseconds
     * as it is a good trade off between CPU usage and recognition delay. Additionally, this was the amount used by
     * Sensory in example code.
     * @return A new @c BroadcomTabKeyDetector, or @c nullptr if the operation failed.
     */
    static std::unique_ptr<BroadcomTabKeyDetector> create(
        std::shared_ptr<AudioInputStream> stream,
        std::unordered_set<std::shared_ptr<KeyWordObserverInterface>> keyWordObservers,
        std::unordered_set<std::shared_ptr<KeyWordDetectorStateObserverInterface>> keyWordDetectorStateObservers,
        std::chrono::milliseconds msDelayToReadTabKey = std::chrono::milliseconds(10));

    /**
     * Destructor.
     */
    ~BroadcomTabKeyDetector() override;

private:
    /**
     * Constructor.
     *
     * @param stream The stream of audio data. This should be formatted in LPCM encoded with 16 bits per sample and
     * have a sample rate of 16 kHz. Additionally, the data should be in little endian format.
     * @param audioFormat The format of the audio data located within the stream.
     * @param keyWordObservers The observers to notify of keyword detections.
     * @param keyWordDetectorStateObservers The observers to notify of state changes in the engine.
     * @param msToPushPerIteration The amount of data in milliseconds to push to Broadcom at a time. Smaller sizes will
     * lead to less delay but more CPU usage. Additionally, larger amounts of data fed into the engine per iteration
     * might lead longer delays before receiving keyword detection events. This has been defaulted to 10 milliseconds
     * as it is a good trade off between CPU usage and recognition delay. Additionally, this was the amount used by
     * Sensory in example code.
     */
    BroadcomTabKeyDetector(
        std::shared_ptr<AudioInputStream> stream,
        std::unordered_set<std::shared_ptr<KeyWordObserverInterface>> keyWordObservers,
        std::unordered_set<std::shared_ptr<KeyWordDetectorStateObserverInterface>> keyWordDetectorStateObservers,
        std::chrono::milliseconds msToPushPerIteration = std::chrono::milliseconds(10));

    /**
     * Initializes the stream reader, sets up the Sensory engine, and kicks off a thread to begin processing data from
     * the stream. This function should only be called once with each new @c SensoryKeywordDetector.
     *
     * @param modelFilePath The path to the model file.
     * @return @c true if the engine was initialized properly and @c false otherwise.
     */
    bool init();

    /// The main function that reads data and feeds it into the engine.
    void detectionLoop();

    /// Indicates whether the internal main loop should keep running.
    std::atomic<bool> m_isShuttingDown;

    /// The stream of audio data.
    const std::shared_ptr<avsCommon::avs::AudioInputStream> m_stream;

    /// The reader that will be used to read audio data from the stream.
    std::shared_ptr<avsCommon::avs::AudioInputStream::Reader> m_streamReader;

    /**
     * This serves as a reference point used when notifying observers of keyword detection indices since Sensory has no
     * way of specifying a start index.
     */
    avsCommon::avs::AudioInputStream::Index m_beginIndexOfStreamReader;

    /// Internal thread that reads audio from the buffer and feeds it to the Sensory engine.
    std::thread m_detectionThread;

};

}  // namespace kwd
}  // namespace alexaClientSDK

#endif  // ALEXA_CLIENT_SDK_KWD_BROADCOM_INCLUDE_KWD_BROADCOM_TAB_KEY_DETECTOR_H_
