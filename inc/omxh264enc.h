#ifndef _OMXH264ENC_H_
#define _OMXH264ENC_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>

enum GstOMXideoEncControlRate
{
    DISABLE,
    VARIABLE,
    CONSTANT,
    VARIABLE_SKIP_FRAMES,
    CONSTANT_SKIP_FRAMES
};

enum GstOmxVideoEncTemporalTradeoffType
{
    GST_OMX_VIDENC_DROP_NO_FRAMES,
    GST_OMX_VIDENC_DROP_1_IN_5_FRAMES,
    GST_OMX_VIDENC_DROP_1_IN_3_FRAMES,
    GST_OMX_VIDENC_DROP_1_IN_2_FRAMES,
    GST_OMX_VIDENC_DROP_2_IN_3_FRAMES
};

enum GstOMXVideoEncHwPreset
{
    UltraFastPreset,
    FastPreset,
    MediumPreset,
    SlowPreset
};

enum GstOmxVideoEncProfileType
{
    GST_OMX_VIDENC_BASELINE_PROFILE,
    GST_OMX_VIDENC_MAIN_PROFILE,
    GST_OMX_VIDENC_HIGH_PROFILE
};

typedef struct __OMXH264ENC_DATA
{
    cJSON *omxh264encJSON;
} _omxh264encData; 

_omxh264encData *omxh264enc_init(void);

void omxh264enc_ReadJSONContent(_omxh264encData *data, char *filepath);

char *omxh264enc_getPropertiesName(_omxh264encData *data);
char *omxh264enc_getPropertiesParent(_omxh264encData *data);
bool omxh264enc_getPropertiesQoS(_omxh264encData *data);
enum GstOMXideoEncControlRate omxh264enc_getPropertiesControlRate(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesBitrate(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesPeakBitrate(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesQuantIFrames(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesQuantPFrames(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesQuantBFrames(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesIFrameInterval(_omxh264encData *data);
bool omxh264enc_getPropertiesSliceIntraRefreshEnable(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesSliceIntraRefreshInterval(_omxh264encData *data);
bool omxh264enc_getPropertiesBitPacketization(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesVbvSize(_omxh264encData *data);
enum GstOmxVideoEncTemporalTradeoffType omxh264enc_getPropertiesTemporalTradeoff(_omxh264encData *data);
bool omxh264enc_getPropertiesEnableMVBufferMeta(_omxh264encData *data);
char *omxh264enc_getPropertiesQpRange(_omxh264encData *data);
bool omxh264enc_getPropertiesMeasureEnccoderLatency(_omxh264encData *data);
bool omxh264enc_getPropertiesEnableTwopassCBR(_omxh264encData *data);
enum GstOMXVideoEncHwPreset omxh264enc_getPropertiesPresetLevel(_omxh264encData *data);
bool omxh264enc_getPropertiesEnableStringentBitrate(_omxh264encData *data);
bool omxh264enc_getPropertiesInsertSpsPps(_omxh264encData *data);
unsigned int omxh264enc_getPropertiesNumBFrames(_omxh264encData *data);
unsigned long omxh264enc_getPropertiesSliceHeaderSpacing(_omxh264encData *data);
enum GstOmxVideoEncProfileType omxh264enc_getPropertiesProfile(_omxh264encData *data);
bool omxh264enc_getPropertiesInsertAud(_omxh264encData *data);
bool omxh264enc_getPropertiesInsertVui(_omxh264encData *data);
bool omxh264enc_getPropertiesCabacEntropyCoding(_omxh264encData *data);

char *omxh264enc_getCapabilitiesVideoXraw(_omxh264encData *data);
char *omxh264enc_getCapabilitiesVideoXrawMemory(_omxh264encData *data);
char *omxh264enc_getCapabilitiesVideoXh264(_omxh264encData *data);

#endif