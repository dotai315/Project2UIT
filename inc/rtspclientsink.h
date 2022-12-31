#ifndef _RTSPCLIENTSINK_H_
#define _RTSPCLIENTSINK_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>

enum GstRTSPLowerTrans 
{
    GST_RTSP_LOWER_TRANS_UNKNOWN = 0,
    GST_RTSP_LOWER_TRANS_UDP = 1,
    GST_RTSP_LOWER_TRANS_UDP_MCAST = 2,
    GST_RTSP_LOWER_TRANS_TCP = 4,
    GST_RTSP_LOWER_TRANS_HTTP = 16,
    GST_RTSP_LOWER_TRANS_TLS = 32
};

enum GTlsCertificateFlags
{
    G_TLS_CERTIFICATE_UNKNOWN_CA = 1,
    G_TLS_CERTIFICATE_BAD_IDENTITY = 2,
    G_TLS_CERTIFICATE_NOT_ACTIVATED = 4, 
    G_TLS_CERTIFICATE_EXPIRED = 8, 
    G_TLS_CERTIFICATE_REVOKED = 16, 
    G_TLS_CERTIFICATE_INSECURE = 32,
    G_TLS_CERTIFICATE_GENERIC_ERROR = 64,
    G_TLS_CERTIFICATE_VALIDATE_ALL = 127
};

enum GstRTSPClientSinkNtpTimeSource
{
    NTP,
    UNIX,
    RUNNING_TIME,
    CLOCK_TIME
};

enum GstRTSPProfile
{
    GST_RTSP_PROFILE_UNKNOWN = 0,
    GST_RTSP_PROFILE_AVP = 1,
    GST_RTSP_PROFILE_SAVP = 2,
    GST_RTSP_PROFILE_AVPF = 4,
    GST_RTSP_PROFILE_SAVPF = 8
};

typedef struct __RTSPCLIENTSINK_DATA
{
    cJSON *rtspclientsinkJSON;
} _rtspclientsinkData; 

_rtspclientsinkData *rtspclientsink_init(void);

void rtspclientsink_ReadJSONContent(_rtspclientsinkData *data, char *filepath);

char *rtspclientsink_getPropertiesName(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesParent(_rtspclientsinkData *data);
bool rtspclientsink_getPropertiesAsyncHandling(_rtspclientsinkData *data);
bool rtspclientsink_getPropertiesMessageForward(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesLocation(_rtspclientsinkData *data);
enum GstRTSPLowerTrans rtspclientsink_getPropertiesProtocols(_rtspclientsinkData *data);
bool rtspclientsink_getPropertiesDebug(_rtspclientsinkData *data);
unsigned int rtspclientsink_getPropertiesRetry(_rtspclientsinkData *data);
uint64_t rtspclientsink_getPropertiesTimeout(_rtspclientsinkData *data);
uint64_t rtspclientsink_getPropertiesTcpTimeout(_rtspclientsinkData *data);
unsigned int rtspclientsink_getPropertiesLatency(_rtspclientsinkData *data);
unsigned int rtspclientsink_getPropertiesRtxTime(_rtspclientsinkData *data);
bool rtspclientsink_getPropertiesDoRtspKeepAlive(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesProxy(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesProxyId(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesProxyPw(_rtspclientsinkData *data);
unsigned int rtspclientsink_getPropertiesRtpBlockSize(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesUserId(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesUserPw(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesPortRange(_rtspclientsinkData *data);
int rtspclientsink_getPropertiesUdpBufferSize(_rtspclientsinkData *data);
bool rtspclientsink_getPropertiesUdpReconnect(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesMulticastIface(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesSdes(_rtspclientsinkData *data);
enum GTlsCertificateFlags rtspclientsink_getPropertiesTlsValidationFlags(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesTlsDatabase(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesTlsInteraction(_rtspclientsinkData *data);
enum GstRTSPClientSinkNtpTimeSource rtspclientsink_getPropertiesNtpTimeSource(_rtspclientsinkData *data);
char *rtspclientsink_getPropertiesUserAgent(_rtspclientsinkData *data);
enum GstRTSPProfile rtspclientsink_getPropertiesProfiles(_rtspclientsinkData *data);



#endif