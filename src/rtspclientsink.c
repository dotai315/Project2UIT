#include "rtspclientsink.h"

static size_t getFileSize(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}

_rtspclientsinkData *rtspclientsink_init(void)
{
    _rtspclientsinkData *newData = (_rtspclientsinkData *)malloc(sizeof(_rtspclientsinkData));
    return newData;
}

void rtspclientsink_ReadJSONContent(_rtspclientsinkData *data, char *filepath)
{
    char *contentJsonFile = NULL;
    cJSON *monitor = NULL;
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        exit(EXIT_FAILURE);
    }

    size_t fileSz = getFileSize(fp);

    contentJsonFile = (char *)malloc(sizeof(char) * (fileSz + 1));

    size_t newLen = fread(contentJsonFile, sizeof(char), fileSz, fp);
    if (ferror(fp) != 0)
    {
        fputs("Error reading file", stderr);
        exit(EXIT_FAILURE);
    }
    else
    {
        contentJsonFile[newLen++] = '\0';
    }

    monitor = cJSON_Parse(contentJsonFile);
    if (monitor == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    data->rtspclientsinkJSON= cJSON_GetObjectItemCaseSensitive(monitor, "rtspclientsink");
}

char *rtspclientsink_getPropertiesName(_rtspclientsinkData *data)
{
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "name");
    if (name->valuestring == NULL)
    {
        return "rtspclientsink0";
    }
    return name->valuestring;
}

char *rtspclientsink_getPropertiesParent(_rtspclientsinkData *data)
{
    return NULL;
}

bool rtspclientsink_getPropertiesAsyncHandling(_rtspclientsinkData *data)
{
    cJSON *asyncHandling = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "async_handling");
    if (cJSON_IsBool(asyncHandling))
    {
        if (cJSON_IsTrue(asyncHandling))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool rtspclientsink_getPropertiesMessageForward(_rtspclientsinkData *data)
{
    cJSON *messageForward = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "message_forward");
    if (cJSON_IsBool(messageForward))
    {
        if (cJSON_IsTrue(messageForward))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

char *rtspclientsink_getPropertiesLocation(_rtspclientsinkData *data)
{
    cJSON *location = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "location");
    if (location->valuestring == NULL)
    {
        return NULL;
    }
    return location->valuestring;
}

enum GstRTSPLowerTrans rtspclientsink_getPropertiesProtocols(_rtspclientsinkData *data)
{
    cJSON *protocols = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "protocols");
    if (cJSON_IsNumber(protocols))
    {
        return protocols->valueint;
    }
    return 7;
}

bool rtspclientsink_getPropertiesDebug(_rtspclientsinkData *data)
{
    cJSON *debug = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "debug");
    if (cJSON_IsBool(debug))
    {
        if (cJSON_IsTrue(debug))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

unsigned int rtspclientsink_getPropertiesRetry(_rtspclientsinkData *data)
{
    cJSON *retry = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "retry");
    if (cJSON_IsNull(retry))
    {
        return 20;
    }
    return (unsigned int)retry->valuedouble;
}

uint64_t rtspclientsink_getPropertiesTimeout(_rtspclientsinkData *data)
{
    cJSON *timeout = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "timeout");
    if (cJSON_IsNull(timeout))
    {
        return 5000000;
    }
    return (unsigned int)timeout->valuedouble;
}

uint64_t rtspclientsink_getPropertiesTcpTimeout(_rtspclientsinkData *data)
{
    cJSON *timeoutTCP = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "tcp_timeout");
    if (cJSON_IsNull(timeoutTCP))
    {
        return 20000000;
    }
    return (unsigned int)timeoutTCP->valuedouble;
}

unsigned int rtspclientsink_getPropertiesLatency(_rtspclientsinkData *data)
{
    cJSON *latency = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "latency");
    if (cJSON_IsNull(latency))
    {
        return 2000;
    }
    return (unsigned int)latency->valuedouble;
}

unsigned int rtspclientsink_getPropertiesRtxTime(_rtspclientsinkData *data)
{
    cJSON *rtx_time = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "rtx_time");
    if (cJSON_IsNull(rtx_time))
    {
        return 500;
    }
    return (unsigned int)rtx_time->valuedouble;
}

bool rtspclientsink_getPropertiesDoRtspKeepAlive(_rtspclientsinkData *data)
{
    cJSON *do_rtsp_keep_alive = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "do_rtsp_keep_alive");
    if (cJSON_IsBool(do_rtsp_keep_alive))
    {
        if (cJSON_IsTrue(do_rtsp_keep_alive))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

char *rtspclientsink_getPropertiesProxy(_rtspclientsinkData *data)
{
    cJSON *proxy = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "proxy");
    if (proxy->valuestring == NULL)
    {
        return NULL;
    }
    return proxy->valuestring;
}

char *rtspclientsink_getPropertiesProxyId(_rtspclientsinkData *data)
{
    cJSON *proxyId = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "proxy_id");
    if (proxyId->valuestring == NULL)
    {
        return NULL;
    }
    return proxyId->valuestring;
}

char *rtspclientsink_getPropertiesProxyPw(_rtspclientsinkData *data)
{
    cJSON *proxyPw = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "proxy_pw");
    if (proxyPw->valuestring == NULL)
    {
        return NULL;
    }
    return proxyPw->valuestring;
}

unsigned int rtspclientsink_getPropertiesRtpBlockSize(_rtspclientsinkData *data)
{
    cJSON *rtp_blocksize = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "rtp_blocksize");
    if (cJSON_IsNull(rtp_blocksize))
    {
        return 0;
    }
    return (unsigned int)rtp_blocksize->valuedouble;
}

char *rtspclientsink_getPropertiesUserId(_rtspclientsinkData *data)
{
    cJSON *userId = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "user_id");
    if (userId->valuestring == NULL)
    {
        return NULL;
    }
    return userId->valuestring;
}

char *rtspclientsink_getPropertiesUserPw(_rtspclientsinkData *data)
{
    cJSON *userPw = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "user_pw");
    if (userPw->valuestring == NULL)
    {
        return NULL;
    }
    return userPw->valuestring;
}

char *rtspclientsink_getPropertiesPortRange(_rtspclientsinkData *data)
{
    cJSON *portRange = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "port_range");
    if (portRange->valuestring == NULL)
    {
        return NULL;
    }
    return portRange->valuestring;
}

int rtspclientsink_getPropertiesUdpBufferSize(_rtspclientsinkData *data)
{
    cJSON *udp_buffer_size = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "udp_buffer_size");
    if (cJSON_IsNull(udp_buffer_size))
    {
        return 524288;
    }
    return udp_buffer_size->valueint;
}

bool rtspclientsink_getPropertiesUdpReconnect(_rtspclientsinkData *data)
{
    cJSON *udp_reconnect = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "udp_reconnect");
    if (cJSON_IsBool(udp_reconnect))
    {
        if (cJSON_IsTrue(udp_reconnect))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

char *rtspclientsink_getPropertiesMulticastIface(_rtspclientsinkData *data)
{
    cJSON *multicast_iface = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "multicast_iface");
    if (multicast_iface->valuestring == NULL)
    {
        return NULL;
    }
    return multicast_iface->valuestring;
}

char *rtspclientsink_getPropertiesSdes(_rtspclientsinkData *data)
{
    return NULL;
}

enum GTlsCertificateFlags rtspclientsink_getPropertiesTlsValidationFlags(_rtspclientsinkData *data)
{
    cJSON *tls_validation_flags = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "tls_validation_flags");
    if (cJSON_IsNull(tls_validation_flags))
    {
        return G_TLS_CERTIFICATE_VALIDATE_ALL;
    }
    return tls_validation_flags->valueint;
}

char *rtspclientsink_getPropertiesTlsDatabase(_rtspclientsinkData *data)
{
    return NULL;
}

char *rtspclientsink_getPropertiesTlsInteraction(_rtspclientsinkData *data)
{
    return NULL;
}

enum GstRTSPClientSinkNtpTimeSource rtspclientsink_getPropertiesNtpTimeSource(_rtspclientsinkData *data)
{
    cJSON *ntp_time_source = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "ntp_time_source");
    if (cJSON_IsNull(ntp_time_source))
    {
        return NTP;
    }
    return ntp_time_source->valueint;
}

char *rtspclientsink_getPropertiesUserAgent(_rtspclientsinkData *data)
{
    cJSON *user_agent = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "user_agent");
    if (user_agent->valuestring == NULL)
    {
        return "GStreamer/1.14.5";
    }
    return user_agent->valuestring;
}

enum GstRTSPProfile rtspclientsink_getPropertiesProfiles(_rtspclientsinkData *data)
{
    cJSON *profiles = cJSON_GetObjectItemCaseSensitive(data->rtspclientsinkJSON, "profiles");
    if (cJSON_IsNull(profiles))
    {
        return GST_RTSP_PROFILE_AVP;
    }
    return profiles->valueint;
}
