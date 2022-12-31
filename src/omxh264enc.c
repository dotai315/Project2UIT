#include "omxh264enc.h"

static size_t getFileSize(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}

_omxh264encData *omxh264enc_init(void)
{
    _omxh264encData *newData = (_omxh264encData *)malloc(sizeof(_omxh264encData));
    return newData;
}

void omxh264enc_ReadJSONContent(_omxh264encData *data, char *filepath)
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
    data->omxh264encJSON= cJSON_GetObjectItemCaseSensitive(monitor, "omxh264enc");
}

char *omxh264enc_getPropertiesName(_omxh264encData *data)
{
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "name");
    if (name->valuestring == NULL)
    {
        return "omxh264enc-omxh264enc0";
    }
    return name->valuestring;
}

char *omxh264enc_getPropertiesParent(_omxh264encData *data)
{
    return NULL;
}

bool omxh264enc_getPropertiesQoS(_omxh264encData *data)
{
    cJSON *qos = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "qos");
    if (cJSON_IsBool(qos))
    {
        if (cJSON_IsTrue(qos))
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

enum GstOMXideoEncControlRate omxh264enc_getPropertiesControlRate(_omxh264encData *data)
{
    cJSON *control_rate = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "control_rate");
    if (cJSON_IsNumber(control_rate))
    {
        return control_rate->valueint;
    }
    return VARIABLE;
}

unsigned int omxh264enc_getPropertiesBitrate(_omxh264encData *data)
{
    cJSON *bitrate = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "bitrate");
    if (cJSON_IsNull(bitrate))
    {
        return 4000000;
    }
    return (unsigned int)bitrate->valuedouble;
}

unsigned int omxh264enc_getPropertiesPeakBitrate(_omxh264encData *data)
{
    cJSON *peak_bitrate = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "peak_bitrate");
    if (cJSON_IsNull(peak_bitrate))
    {
        return 0;
    }
    return (unsigned int)peak_bitrate->valuedouble;
}

unsigned int omxh264enc_getPropertiesQuantIFrames(_omxh264encData *data)
{
    cJSON *quant_i_frames = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "quant_i_frames");
    if (cJSON_IsNull(quant_i_frames))
    {
        return 4294967295;
    }
    return (unsigned int)quant_i_frames->valuedouble;
}

unsigned int omxh264enc_getPropertiesQuantPFrames(_omxh264encData *data)
{
    cJSON *quant_p_frames = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "quant_p_frames");
    if (cJSON_IsNull(quant_p_frames))
    {
        return 4294967295;
    }
    return (unsigned int)quant_p_frames->valuedouble;
}

unsigned int omxh264enc_getPropertiesQuantBFrames(_omxh264encData *data)
{
    cJSON *quant_b_frames = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "quant_b_frames");
    if (cJSON_IsNull(quant_b_frames))
    {
        return 4294967295;
    }
    return (unsigned int)quant_b_frames->valuedouble;
}

unsigned int omxh264enc_getPropertiesIFrameInterval(_omxh264encData *data)
{
    cJSON *iframeinterval = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "iframeinterval");
    if (cJSON_IsNull(iframeinterval))
    {
        return 0;
    }
    return (unsigned int)iframeinterval->valuedouble;
}

bool omxh264enc_getPropertiesSliceIntraRefreshEnable(_omxh264encData *data)
{
    cJSON *sliceintrarefreshenable = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "sliceintrarefreshenable");
    if (cJSON_IsBool(sliceintrarefreshenable))
    {
        if (cJSON_IsTrue(sliceintrarefreshenable))
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

unsigned int omxh264enc_getPropertiesSliceIntraRefreshInterval(_omxh264encData *data)
{
    cJSON *sliceintrarefreshinterval = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "sliceintrarefreshinterval");
    if (cJSON_IsNull(sliceintrarefreshinterval))
    {
        return 60;
    }
    return (unsigned int)sliceintrarefreshinterval->valuedouble;
}

bool omxh264enc_getPropertiesBitPacketization(_omxh264encData *data)
{
    cJSON *bit_packetization = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "bit_packetization");
    if (cJSON_IsBool(bit_packetization))
    {
        if (cJSON_IsTrue(bit_packetization))
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

unsigned int omxh264enc_getPropertiesVbvSize(_omxh264encData *data)
{
    cJSON *vbv_size = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "vbv_size");
    if (cJSON_IsNull(vbv_size))
    {
        return 10;
    }
    return (unsigned int)vbv_size->valuedouble;
}

enum GstOmxVideoEncTemporalTradeoffType omxh264enc_getPropertiesTemporalTradeoff(_omxh264encData *data)
{
    cJSON *temporal_tradeoff = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "temporal_tradeoff");
    if (cJSON_IsNumber(temporal_tradeoff))
    {
        return temporal_tradeoff->valueint;
    }
    return GST_OMX_VIDENC_DROP_NO_FRAMES;
}

bool omxh264enc_getPropertiesEnableMVBufferMeta(_omxh264encData *data)
{
    cJSON *enablemvbuffermeta = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "enablemvbuffermeta");
    if (cJSON_IsBool(enablemvbuffermeta))
    {
        if (cJSON_IsTrue(enablemvbuffermeta))
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

char *omxh264enc_getPropertiesQpRange(_omxh264encData *data)
{
    cJSON *qp_range = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "qp_range");
    if (qp_range->valuestring == NULL)
    {
        return "-1,-1:-1,-1:-1,-1";
    }
    return qp_range->valuestring;
}

bool omxh264enc_getPropertiesMeasureEnccoderLatency(_omxh264encData *data)
{
    cJSON *measureencoderlatency = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "measureencoderlatency");
    if (cJSON_IsBool(measureencoderlatency))
    {
        if (cJSON_IsTrue(measureencoderlatency))
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

bool omxh264enc_getPropertiesEnableTwopassCBR(_omxh264encData *data)
{
    cJSON *enabletwopasscbr = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "enabletwopasscbr");
    if (cJSON_IsBool(enabletwopasscbr))
    {
        if (cJSON_IsTrue(enabletwopasscbr))
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

enum GstOMXVideoEncHwPreset omxh264enc_getPropertiesPresetLevel(_omxh264encData *data)
{
    cJSON *preset_level = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "preset_level");
    if (cJSON_IsNumber(preset_level))
    {
        return preset_level->valueint;
    }
    return UltraFastPreset;
}

bool omxh264enc_getPropertiesEnableStringentBitrate(_omxh264encData *data)
{
    cJSON *enablestringentbitrate = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "enablestringentbitrate");
    if (cJSON_IsBool(enablestringentbitrate))
    {
        if (cJSON_IsTrue(enablestringentbitrate))
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

bool omxh264enc_getPropertiesInsertSpsPps(_omxh264encData *data)
{
    cJSON *insert_sps_pps = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "insert_sps_pps");
    if (cJSON_IsBool(insert_sps_pps))
    {
        if (cJSON_IsTrue(insert_sps_pps))
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

unsigned int omxh264enc_getPropertiesNumBFrames(_omxh264encData *data)
{
    cJSON *num_b_frames = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "num_b_frames");
    if (cJSON_IsNull(num_b_frames))
    {
        return 0;
    }
    return (unsigned int)num_b_frames->valuedouble;
}

unsigned long omxh264enc_getPropertiesSliceHeaderSpacing(_omxh264encData *data)
{
    cJSON *slice_header_spacing = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "slice_header_spacing");
    if (cJSON_IsNull(slice_header_spacing))
    {
        return 0;
    }
    return (unsigned int)slice_header_spacing->valuedouble;
}

enum GstOmxVideoEncProfileType omxh264enc_getPropertiesProfile(_omxh264encData *data)
{
    cJSON *profile = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "profile");
    if (cJSON_IsNumber(profile))
    {
        return profile->valueint;
    }
    return GST_OMX_VIDENC_BASELINE_PROFILE;
}

bool omxh264enc_getPropertiesInsertAud(_omxh264encData *data)
{
    cJSON *insert_aud = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "insert_aud");
    if (cJSON_IsBool(insert_aud))
    {
        if (cJSON_IsTrue(insert_aud))
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

bool omxh264enc_getPropertiesInsertVui(_omxh264encData *data)
{
    cJSON *insert_vui = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "insert_vui");
    if (cJSON_IsBool(insert_vui))
    {
        if (cJSON_IsTrue(insert_vui))
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

bool omxh264enc_getPropertiesCabacEntropyCoding(_omxh264encData *data)
{
    cJSON *cabac_entropy_coding = cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "cabac_entropy_coding");
    if (cJSON_IsBool(cabac_entropy_coding))
    {
        if (cJSON_IsTrue(cabac_entropy_coding))
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

char *omxh264enc_getCapabilitiesVideoXraw(_omxh264encData *data)
{
    char *str = (char *)malloc(sizeof(char) * 100);
    cJSON *video_xraw= cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "video_xraw");
    cJSON *width = cJSON_GetObjectItemCaseSensitive(video_xraw, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(video_xraw, "height");
    cJSON *framerate = cJSON_GetObjectItemCaseSensitive(video_xraw, "framerate");
    if (cJSON_IsNumber(width))
    {
        snprintf(str,100, "video/x-raw, width=(int)%d, height=(int)%d, framerate=(fraction)%d/1",width->valueint, height->valueint, framerate->valueint);
        return str;
    }
    return NULL;
}

char *omxh264enc_getCapabilitiesVideoXrawMemory(_omxh264encData *data)
{
    char *str = (char *)malloc(sizeof(char) * 100);
    cJSON *video_xraw_memory= cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "video_xraw_memory");
    cJSON *width = cJSON_GetObjectItemCaseSensitive(video_xraw_memory, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(video_xraw_memory, "height");
    cJSON *framerate = cJSON_GetObjectItemCaseSensitive(video_xraw_memory, "framerate");
    if (cJSON_IsNumber(width))
    {
        snprintf(str,100, "video/x-raw(memory:NVMM), width=(int)%d, height=(int)%d, framerate=(fraction)%d/1",width->valueint, height->valueint, framerate->valueint);
        return str;
    }
    return NULL;
}

char *omxh264enc_getCapabilitiesVideoXh264(_omxh264encData *data)
{
    char *str = (char *)malloc(sizeof(char) * 100);
    cJSON *video_xraw_h264= cJSON_GetObjectItemCaseSensitive(data->omxh264encJSON, "video_xraw_h264");
    cJSON *width = cJSON_GetObjectItemCaseSensitive(video_xraw_h264, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(video_xraw_h264, "height");
    cJSON *stream_format = cJSON_GetObjectItemCaseSensitive(video_xraw_h264, "stream_format");
    if (cJSON_IsNumber(width))
    {
        snprintf(str,100, "video/x-h264, width=(int)%d, height=(int)%d, stream-format=%s",width->valueint, height->valueint, stream_format->valuestring);
        return str;
    }
    return NULL;
}
