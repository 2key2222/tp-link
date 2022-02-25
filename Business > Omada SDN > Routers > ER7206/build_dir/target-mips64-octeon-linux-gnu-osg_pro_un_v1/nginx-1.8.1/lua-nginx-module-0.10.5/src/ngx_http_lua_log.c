
/*
 * Copyright (C) Xiaozhe Wang (chaoslawful)
 * Copyright (C) Yichun Zhang (agentzh)
 */


#ifndef DDEBUG
#define DDEBUG 0
#endif
#define _FILE_OFFSET_BITS  64
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <sys/msg.h>
#include <errno.h>
#include "ddebug.h"


#include "ngx_http_lua_log.h"
#include "ngx_http_lua_util.h"

#define WIFIDOG_MSG_MAX_LENGTH 64 

typedef struct _wifidogMsg{
    long msg_type;
    char msg_content[WIFIDOG_MSG_MAX_LENGTH];
}wifidogMsg;


static int ngx_http_lua_print(lua_State *L);
static int ngx_http_lua_ngx_log(lua_State *L);
static int log_wrapper(ngx_log_t *log, const char *ident,
    ngx_uint_t level, lua_State *L);
static void ngx_http_lua_inject_log_consts(lua_State *L);


/**
 * Wrapper of nginx log functionality. Take a log level param and varargs of
 * log message params.
 *
 * @param L Lua state pointer
 * @retval always 0 (don't return values to Lua)
 * */
int
ngx_http_lua_ngx_log(lua_State *L)
{
    ngx_log_t                   *log;
    ngx_http_request_t          *r;
    const char                  *msg;
    int                          level;

    r = ngx_http_lua_get_req(L);

    if (r && r->connection && r->connection->log) {
        log = r->connection->log;

    } else {
    log = ngx_cycle->log;
    }

    level = luaL_checkint(L, 1);
    if (level < NGX_LOG_STDERR || level > NGX_LOG_DEBUG) {
        msg = lua_pushfstring(L, "bad log level: %d", level);
        return luaL_argerror(L, 1, msg);
    }

    /* remove log-level param from stack */
    lua_remove(L, 1);

    return log_wrapper(log, "[lua] ", (ngx_uint_t) level, L);
}


/**
 * Override Lua print function, output message to nginx error logs. Equal to
 * ngx.log(ngx.NOTICE, ...).
 *
 * @param L Lua state pointer
 * @retval always 0 (don't return values to Lua)
 * */
int
ngx_http_lua_print(lua_State *L)
{
    ngx_log_t                   *log;
    ngx_http_request_t          *r;

    r = ngx_http_lua_get_req(L);

    if (r && r->connection && r->connection->log) {
        log = r->connection->log;

    } else {
    log = ngx_cycle->log;
    }

    return log_wrapper(log, "[lua] ", NGX_LOG_NOTICE, L);
}


static int
log_wrapper(ngx_log_t *log, const char *ident, ngx_uint_t level,
    lua_State *L)
{
    u_char              *buf;
    u_char              *p, *q;
    ngx_str_t            name;
    int                  nargs, i;
    size_t               size, len;
    size_t               src_len = 0;
    int                  type;
    const char          *msg;
    lua_Debug            ar;

    if (level > log->log_level) {
        return 0;
    }

#if 1
    /* add debug info */

    lua_getstack(L, 1, &ar);
    lua_getinfo(L, "Snl", &ar);

    /* get the basename of the Lua source file path, stored in q */
    name.data = (u_char *) ar.short_src;
    if (name.data == NULL) {
        name.len = 0;

    } else {
        p = name.data;
        while (*p != '\0') {
            if (*p == '/' || *p == '\\') {
                name.data = p + 1;
            }
            p++;
        }

        name.len = p - name.data;
    }

#endif

    nargs = lua_gettop(L);

    size = name.len + NGX_INT_T_LEN + sizeof(":: ") - 1;

    if (*ar.namewhat != '\0' && *ar.what == 'L') {
        src_len = ngx_strlen(ar.name);
        size += src_len + sizeof("(): ") - 1;
    }

    for (i = 1; i <= nargs; i++) {
        type = lua_type(L, i);
        switch (type) {
            case LUA_TNUMBER:
            case LUA_TSTRING:
                lua_tolstring(L, i, &len);
                size += len;
                break;

            case LUA_TNIL:
                size += sizeof("nil") - 1;
                break;

            case LUA_TBOOLEAN:
                if (lua_toboolean(L, i)) {
                    size += sizeof("true") - 1;

                } else {
                    size += sizeof("false") - 1;
                }

                break;

            case LUA_TTABLE:
                if (!luaL_callmeta(L, i, "__tostring")) {
                    return luaL_argerror(L, i, "expected table to have "
                                         "__tostring metamethod");
                }

                lua_tolstring(L, -1, &len);
                size += len;
                break;

            case LUA_TLIGHTUSERDATA:
                if (lua_touserdata(L, i) == NULL) {
                    size += sizeof("null") - 1;
                    break;
                }

                continue;

            default:
                msg = lua_pushfstring(L, "string, number, boolean, or nil "
                                      "expected, got %s",
                                      lua_typename(L, type));
                return luaL_argerror(L, i, msg);
        }
    }

    buf = lua_newuserdata(L, size);

    p = ngx_copy(buf, name.data, name.len);

    *p++ = ':';

    p = ngx_snprintf(p, NGX_INT_T_LEN, "%d",
                     ar.currentline ? ar.currentline : ar.linedefined);

    *p++ = ':'; *p++ = ' ';

    if (*ar.namewhat != '\0' && *ar.what == 'L') {
        p = ngx_copy(p, ar.name, src_len);
        *p++ = '(';
        *p++ = ')';
        *p++ = ':';
        *p++ = ' ';
    }

    for (i = 1; i <= nargs; i++) {
        type = lua_type(L, i);
        switch (type) {
            case LUA_TNUMBER:
            case LUA_TSTRING:
                q = (u_char *) lua_tolstring(L, i, &len);
                p = ngx_copy(p, q, len);
                break;

            case LUA_TNIL:
                *p++ = 'n';
                *p++ = 'i';
                *p++ = 'l';
                break;

            case LUA_TBOOLEAN:
                if (lua_toboolean(L, i)) {
                    *p++ = 't';
                    *p++ = 'r';
                    *p++ = 'u';
                    *p++ = 'e';

                } else {
                    *p++ = 'f';
                    *p++ = 'a';
                    *p++ = 'l';
                    *p++ = 's';
                    *p++ = 'e';
                }

                break;

            case LUA_TTABLE:
                luaL_callmeta(L, i, "__tostring");
                q = (u_char *) lua_tolstring(L, -1, &len);
                p = ngx_copy(p, q, len);
                break;

            case LUA_TLIGHTUSERDATA:
                *p++ = 'n';
                *p++ = 'u';
                *p++ = 'l';
                *p++ = 'l';

                break;

            default:
                return luaL_error(L, "impossible to reach here");
        }
    }

    if (p - buf > (off_t) size) {
        return luaL_error(L, "buffer error: %d > %d", (int) (p - buf),
                          (int) size);
    }

    ngx_log_error(level, log, 0, "%s%*s", ident, (size_t) (p - buf), buf);

    return 0;
}

static int ngx_http_lua_sendfile(lua_State *L)  
{  
    size_t                      len;  
    ngx_http_request_t        *r;  
    ngx_str_t                  path;  
    ngx_int_t                  rc;  
    ngx_uint_t                 level;  
    ngx_log_t                 *log;  
    ngx_buf_t                 *b;  
    ngx_chain_t                out;  
    ngx_open_file_info_t       of;  
    ngx_http_core_loc_conf_t  *clcf;  
    int                        offset;  
    int                        bytes;  
    char                      *filename;  
  
    r = ngx_http_lua_get_req(L);
  
    if (r == NULL)   
    {  
        luaL_error(L, "fuck no request object found!");  
        return 1;  
   }  
    
    filename = (char *) lua_tolstring(L, 1, &len);  
    offset   = lua_tonumber(L, 2);  
    bytes    = lua_tonumber(L, 3);  
  
    if (r && r->connection && r->connection->log) {
        log = r->connection->log;

    } else {
    log = ngx_cycle->log;
    }
  
    path.len = ngx_strlen(filename);  
  
    path.data = ngx_pnalloc(r->pool, path.len + 1);  
    if (path.data == NULL) {  
        return 0;  
    }  
  
    (void) ngx_cpystrn(path.data, (u_char *) filename, path.len + 1);  
  
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, log, 0, "ngx send lua filename: \"%s\"", filename);  
  
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);  
  
    ngx_memzero(&of, sizeof(ngx_open_file_info_t));  
  
    of.read_ahead = clcf->read_ahead;  
    of.directio = clcf->directio;  
    of.valid = clcf->open_file_cache_valid;  
    of.min_uses = clcf->open_file_cache_min_uses;  
    of.errors = clcf->open_file_cache_errors;  
    of.events = clcf->open_file_cache_events;  
  
    if (ngx_http_set_disable_symlinks(r, clcf, &path, &of) != NGX_OK)   
    {  
        return 0;//NGX_HTTP_INTERNAL_SERVER_ERROR;  
    }  
  
    if (ngx_open_cached_file(clcf->open_file_cache, &path, &of, r->pool) != NGX_OK)  
    {  
        switch (of.err)   
    { 
  
        case 0:  
            return 0;//NGX_HTTP_INTERNAL_SERVER_ERROR;  
  
        case NGX_ENOENT:  
        case NGX_ENOTDIR:  
        case NGX_ENAMETOOLONG:  
  
            level = NGX_LOG_ERR;  
            rc = NGX_HTTP_NOT_FOUND;  
            break;  
  
        case NGX_EACCES:  
#if (NGX_HAVE_OPENAT)  
        case NGX_EMLINK:  
        case NGX_ELOOP:  
#endif  
            level = NGX_LOG_ERR;  
            rc = NGX_HTTP_FORBIDDEN;  
            break;  
  
        default:  
  
            level = NGX_LOG_CRIT;  
            rc = NGX_HTTP_INTERNAL_SERVER_ERROR;  
            break;  
        }  
  
        if (rc != NGX_HTTP_NOT_FOUND || clcf->log_not_found)   
    {  
            ngx_log_error(level, log, of.err, "%s \"%s\" failed", of.failed, path.data);  
        }  
  
        return 0;//rc;  
    }  
  
    r->root_tested = !r->error_page;  
  
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, log, 0, "http static fd: %d", of.fd);  
  
    if (offset < 0) {  
        offset = 0;  
    }  
  
    if (bytes <= 0) {  
        bytes = of.size - offset;  
    }  
  
  
#if !(NGX_WIN32) /* the not regular files are probably Unix specific */  
  
    if (!of.is_file)   
    {  
        ngx_log_error(NGX_LOG_CRIT, log, 0, "\"%s\" is not a regular file", path.data);  
  
        return 0;//NGX_HTTP_NOT_FOUND;  
    }  
  
#endif  
  
    if (r->method & NGX_HTTP_POST)
    {  
        return 0;//NGX_HTTP_NOT_ALLOWED;  
    }  
  
    rc = ngx_http_discard_request_body(r);  
  
    if (rc != NGX_OK)   
    {  
        return 0;//rc;  
    }  
  
    log->action = "sending response to client";  
  
    len = (offset + bytes) >= of.size ? of.size : (offset + bytes);  
  
    r->headers_out.status = NGX_HTTP_OK;  
    r->headers_out.content_length_n = len - offset;  
    r->headers_out.last_modified_time = of.mtime;  
  
    if (ngx_http_set_content_type(r) != NGX_OK)   
    {  
        return 0;//NGX_HTTP_INTERNAL_SERVER_ERROR;  
    }  
  
    if (r != r->main && of.size == 0)   
    {  
         ngx_http_send_header(r);  
         return 0;//  
    }  
  
    r->allow_ranges = 1;  
  
    /* we need to allocate all before the header would be sent */  
  
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));  
    if (b == NULL)   
    {  
        return 0;//NGX_HTTP_INTERNAL_SERVER_ERROR;  
    }  
  
    b->file = ngx_pcalloc(r->pool, sizeof(ngx_file_t));  
    if (b->file == NULL)   
    {  
        return 0;//NGX_HTTP_INTERNAL_SERVER_ERROR;  
    }  
  
    rc = ngx_http_send_header(r);  
  
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only)   
    {  
        return 0;//rc;  
    }  
  
    b->file_pos = offset;  
    b->file_last = (offset + bytes) >= of.size ? of.size : (offset + bytes);  
  
    b->in_file = 1;  
    b->last_buf = (r == r->main) ? 1: 0;  
    b->last_in_chain = 1;  
  
    b->file->fd = of.fd;  
    b->file->name = path;
    b->file->log = log;  
    b->file->directio = of.is_directio;  
  
    out.buf = b;  
    out.next = NULL;  
  
    ngx_http_output_filter(r, &out);  
    return 0;//  
} 

/*
 * args[0]:msg_key (int)
 * args[1]:msg_type (long)
 * args[2]:msg_content (string)
 */
static int ngx_http_lua_sendMsg(lua_State *L)  
{  
    ngx_http_request_t        *r = NULL;  
    ngx_log_t                 *log = NULL;  
    wifidogMsg                sendMsg;
    int                       sendLength = 0;
    int                       msg_key = 0;
    long                      msg_type = 0;
    char                      *msg_content = NULL;
    size_t                                 msg_length = 0;
    size_t                                 msg_max = 0;
    int                       nargs = 0;
    int                       wifidog_msgid = 0;
        


    r = ngx_http_lua_get_req(L);
  
    if (r == NULL)   
    {  
        luaL_error(L, "fuck no request object found!");  
        return 1;  
    }  

    if (r && r->connection && r->connection->log) {
        log = r->connection->log;

    } else {
    log = ngx_cycle->log; 
    }  
  
   
    nargs = lua_gettop(L);  

    if (3 != nargs)
    {
        ngx_log_error(NGX_LOG_ERR, log, 0, "The argc is not correct:[%d]", nargs);  

        lua_pushstring(L, "The argc is not correct");
        return 1;
    }

    msg_key = (int)lua_tonumber(L, 1);
    msg_type = (long)lua_tonumber(L, 2);
    msg_content = (char *) lua_tolstring(L, 3, &msg_length);  
    msg_max   = WIFIDOG_MSG_MAX_LENGTH;

    if (msg_length > msg_max)
    {
        ngx_log_error(NGX_LOG_ERR, log, 0, "the msg is too long:[%d]-[%d]", msg_length, msg_max);  
        lua_pushstring(L, "The msg is too long");
        return 1;
    }

    if (0 == wifidog_msgid)
    {
        key_t key;
        int msgid = -1;  
        
        key=(key_t)msg_key;

        msgid = msgget(key, IPC_EXCL);
        if (msgid >= 0)
        {
            /* Don't need to clean the msg left in the queue */
            ngx_log_error(NGX_LOG_DEBUG, log, 0, "already exist msg_queue:[%d]", msgid);  
        }
        else
        {
            /* The wifidog is not ready */
            ngx_log_error(NGX_LOG_ERR, log, 0, "wifidog is not ready:[%d]", msgid);  
            lua_pushstring(L, "The wifidog is not ready");
            return 1;           
        }
        
        wifidog_msgid = msgid;
    }


    memset(&sendMsg, 0, sizeof(wifidogMsg));
    sendMsg.msg_type = msg_type;
    snprintf(sendMsg.msg_content, msg_max, "%s", msg_content);
    sendMsg.msg_content[WIFIDOG_MSG_MAX_LENGTH - 1] = '\0';
    sendLength = sizeof(wifidogMsg) -sizeof(long);
    
    if (msgsnd(wifidog_msgid, (void *)&sendMsg, sendLength, IPC_NOWAIT))
    {
            struct msqid_ds msg_stat;
            ngx_log_error(NGX_LOG_ERR, log, 0, "msgsnd failed.[%d]-[%d][%d][%d][%d][%d][%d][%d]", 
            errno,
            EACCES,
            EAGAIN,
            EFAULT,
            EIDRM,
            EINTR,
            EINVAL,
            ENOMEM
            );
            if (-1 == msgctl(wifidog_msgid, IPC_STAT, &msg_stat))
            {
                ngx_log_error(NGX_LOG_ERR, log, 0, "Get msgctl failed.[%d][%d]", wifidog_msgid, errno);
            }
            ngx_log_error(NGX_LOG_ERR, log, 0, "@@[%u]{%u}@@", msg_stat.msg_cbytes, msg_stat.msg_qnum);
            lua_pushstring(L, "Send msg failed.");
            return 1; 
    }

    lua_pushstring(L, "OK");
    return 1;
    
}

static int ngx_http_lua_getMac(lua_State *L) 
{
        ngx_http_request_t        *r = NULL;  
        ngx_log_t                      *log = NULL;
        char *req_ip;
        char *dev;
        int sd;
        
        struct arpreq arpreq;
        struct sockaddr_in *sin;
        struct in_addr ina;
        unsigned char *hw_addr = NULL;
        char macStr[64];
        size_t dev_length = 0;
        int rc;
        int nargs;

        r = ngx_http_lua_get_req(L);
      
        if (r == NULL)   
        {  
            luaL_error(L, "fuck no request object found!");  
            return 1;  
        }

        if (r && r->connection && r->connection->log) {
            log = r->connection->log;

        } else {
        log = ngx_cycle->log;
        } 
      
       
        nargs = lua_gettop(L);  

        if (2 != nargs)
        {
            ngx_log_error(NGX_LOG_ERR, log, 0, "The argc is not correct:[%d]", nargs);  

            lua_pushstring(L, "The argc is not correct");
            return 1;
        }

        req_ip = (char *) lua_tolstring(L, 1, &dev_length);  
        dev = (char *) lua_tolstring(L, 2, &dev_length);         

        sd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sd < 0)
        {
            ngx_log_error(NGX_LOG_ERR, log, 0, "socket error\n");  
            lua_pushstring(L, "00:00:00:00:00:00");
            return 1;  
        }

        /* Try to find an entry in arp cache for the ip address specified */ 
                          
       /*you must add this becasue some system will return "Invlid argument"
        because some argument isn't zero */

        memset(&arpreq, 0, sizeof(struct arpreq));

        sin = (struct sockaddr_in *) &arpreq.arp_pa;
        memset(sin, 0, sizeof(struct sockaddr_in));
        sin->sin_family = AF_INET;
        ina.s_addr = inet_addr(req_ip);
        memcpy(&sin->sin_addr, (char *)&ina, sizeof(struct in_addr));
        
        strncpy(arpreq.arp_dev, dev, sizeof(arpreq.arp_dev));
        
        rc = ioctl(sd, SIOCGARP, &arpreq);
        memset(macStr, 0, sizeof(macStr));
        if (rc < 0)
        {
                memcpy(macStr,"00:00:00:00:00:00",strlen("00:00:00:00:00:00")+1);
        }
        else
        {
                hw_addr = (unsigned char *) (arpreq.arp_ha.sa_data);            
                sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", hw_addr[0], hw_addr[1], hw_addr[2], hw_addr[3], hw_addr[4], hw_addr[5]);
        }

        close(sd);

        lua_pushstring(L, macStr);
        return 1;  
}

void  
ngx_http_lua_inject_log_api(lua_State *L)  
{  
    ngx_http_lua_inject_log_consts(L);  
  
    lua_pushcfunction(L, ngx_http_lua_ngx_log);  
    lua_setfield(L, -2, "log");  
  
    lua_pushcfunction(L, ngx_http_lua_sendfile);
    lua_setfield(L, -2, "sendfile");  

    lua_pushcfunction(L, ngx_http_lua_sendMsg);
    lua_setfield(L, -2, "sendMsg");

    lua_pushcfunction(L, ngx_http_lua_getMac);
    lua_setfield(L, -2, "getMac");
  
    lua_pushcfunction(L, ngx_http_lua_print);  
    lua_setglobal(L, "print");  
} 


static void
ngx_http_lua_inject_log_consts(lua_State *L)
{
    /* {{{ nginx log level constants */
    lua_pushinteger(L, NGX_LOG_STDERR);
    lua_setfield(L, -2, "STDERR");

    lua_pushinteger(L, NGX_LOG_EMERG);
    lua_setfield(L, -2, "EMERG");

    lua_pushinteger(L, NGX_LOG_ALERT);
    lua_setfield(L, -2, "ALERT");

    lua_pushinteger(L, NGX_LOG_CRIT);
    lua_setfield(L, -2, "CRIT");

    lua_pushinteger(L, NGX_LOG_ERR);
    lua_setfield(L, -2, "ERR");

    lua_pushinteger(L, NGX_LOG_WARN);
    lua_setfield(L, -2, "WARN");

    lua_pushinteger(L, NGX_LOG_NOTICE);
    lua_setfield(L, -2, "NOTICE");

    lua_pushinteger(L, NGX_LOG_INFO);
    lua_setfield(L, -2, "INFO");

    lua_pushinteger(L, NGX_LOG_DEBUG);
    lua_setfield(L, -2, "DEBUG");
    /* }}} */
}

/* vi:set ft=c ts=4 sw=4 et fdm=marker: */
