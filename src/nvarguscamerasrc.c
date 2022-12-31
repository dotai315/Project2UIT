#include "nvarguscamerasrc.h"

static size_t getFileSize(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}

_nvarguscamerasrcData *nvarguscamerasrc_init(void)
{
    _nvarguscamerasrcData *newData = (_nvarguscamerasrcData *)malloc(sizeof(_nvarguscamerasrcData));
    return newData;
}

void nvarguscamerasrc_ReadJSONContent(_nvarguscamerasrcData *data, const char *filepath)
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
    data->nvarguscamerasrcJSON = cJSON_GetObjectItemCaseSensitive(monitor, "nvarguscamerasrc");
}

char *nvarguscamerasrc_getPropertiesName(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "name");
    if (name->valuestring == NULL)
    {
        return "nvarguscamerasrc0";
    }
    return name->valuestring;
}

char *nvarguscamerasrc_getPropertiesParent(_nvarguscamerasrcData *data)
{
    return NULL;
}

unsigned int nvarguscamerasrc_getPropertiesBlocksize(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *blocksize = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "blocksize");
    if (cJSON_IsNull(blocksize))
    {
        return 4096;
    }
    return (unsigned int)blocksize->valuedouble;
}

int nvarguscamerasrc_getPropertiesNumBuffers(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *num_buffers = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "num_buffers");
    if (cJSON_IsNull(num_buffers))
    {
        return -1;
    }
    return num_buffers->valueint;
}

bool nvarguscamerasrc_getPropertiesTypefind(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *typefind = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "typefind");
    if (cJSON_IsBool(typefind))
    {
        if (cJSON_IsTrue(typefind))
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

bool nvarguscamerasrc_getPropertiesDoTimeStamp(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr,"json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *do_timestamp = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "do_timestamp");
    if (cJSON_IsBool(do_timestamp))
    {
        if (cJSON_IsTrue(do_timestamp))
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

bool nvarguscamerasrc_getPropertiesSilent(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *silent = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "silent");
    if (cJSON_IsBool(silent))
    {
        if (cJSON_IsTrue(silent))
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

unsigned int nvarguscamerasrc_getPropertiesTimeout(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *timeout = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "timeout");
    if (cJSON_IsNumber(timeout))
    {
        return (unsigned int)timeout->valuedouble;
    }
    return 0;
}

enum GstNvarguscamWBMode nvarguscamerasrc_getPropertiesWbmode(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *wbmode = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "wbmode");
    if (cJSON_IsNumber(wbmode))
    {
        return wbmode->valueint;
    }
    return 1;
}

float nvarguscamerasrc_getPropertiesSaturation(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *saturation = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "saturation");
    if (cJSON_IsNumber(saturation))
    {
        return (float)saturation->valuedouble;
    }
    return 1;
}

int nvarguscamerasrc_getPropertiesSensorId(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *sensor_id = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "sensor_id");
    if (cJSON_IsNumber(sensor_id))
    {
        return sensor_id->valueint;
    }
    return 0;
}

int nvarguscamerasrc_getPropertiesSensorMode(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *sensor_mode = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "sensor_mode");
    if (cJSON_IsNumber(sensor_mode))
    {
        return sensor_mode->valueint;
    }
    return 0;
}

int nvarguscamerasrc_getPropertiesTotalSensorModes(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *total_sensor_modes = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "total_sensor_modes");
    if (cJSON_IsNumber(total_sensor_modes))
    {
        return total_sensor_modes->valueint;
    }
    return 0;
}

char *nvarguscamerasrc_getPropertiesExposureTimeRange(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *exposuretimerange = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "exposuretimerange");
    return exposuretimerange->valuestring;
}

char *nvarguscamerasrc_getPropertiesGainRange(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *gainrange = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "gainrange");
    return gainrange->valuestring;
}

char *nvarguscamerasrc_getPropertiesIspDigitalGainRange(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *ispdigitalgainrange = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "ispdigitalgainrange");
    return ispdigitalgainrange->valuestring;
}

float nvarguscamerasrc_getPropertiesTnrStrength(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *tnr_strength = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "tnr_strength");
    if (cJSON_IsNumber(tnr_strength))
    {
        return (float)tnr_strength->valuedouble;
    }
    return -1;
}

enum GstNvArgusCamTNRMode nvarguscamerasrc_getPropertiesTnrMode(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *tnr_mode = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "tnr_mode");
    if (cJSON_IsNumber(tnr_mode))
    {
        return tnr_mode->valueint;
    }
    return GST_NVCAM_NR_FAST;
}

enum GstNvArgusCamEEMode nvarguscamerasrc_getPropertiesEEmode(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *ee_mode = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "ee_mode");
    if (cJSON_IsNumber(ee_mode))
    {
        return ee_mode->valueint;
    }
    return GST_NVCAM_EE_FAST;
}

float nvarguscamerasrc_getPropertiesEEStrength(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *ee_strength = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "ee_strength");
    if (cJSON_IsNumber(ee_strength))
    {
        return (float)ee_strength->valuedouble;
    }
    return -1;
}

enum GstNvArgusCamAeAntiBandingMode nvarguscamerasrc_getPropertiesAeantibanding(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *aeantibanding = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "aeantibanding");
    if (cJSON_IsNumber(aeantibanding))
    {
        return aeantibanding->valueint;
    }
    return GST_NVCAM_AEANTIBANDING_AUTO;
}

float nvarguscamerasrc_getPropertiesExposureCompensation(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *exposureCompensation = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "exposurecompensation");
    if (cJSON_IsNumber(exposureCompensation))
    {
        return (float)exposureCompensation->valuedouble;
    }
    return 0;
}

bool nvarguscamerasrc_getPropertiesAelock(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *aelock = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "aelock");
    if (cJSON_IsBool(aelock))
    {
        if (cJSON_IsTrue(aelock))
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

char *nvarguscamerasrc_getPropertiesAeregion(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        return NULL;
    }

    cJSON *aeregion = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "aeregion");
    return aeregion->valuestring;
}

bool nvarguscamerasrc_getPropertiesAwblock(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *awblock = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "awblock");
    if (cJSON_IsBool(awblock))
    {
        if (cJSON_IsTrue(awblock))
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

bool nvarguscamerasrc_getPropertiesBufapiVersion(_nvarguscamerasrcData *data)
{
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *bufapiVersion = cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "bufapi_version");
    if (cJSON_IsBool(bufapiVersion))
    {
        if (cJSON_IsTrue(bufapiVersion))
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

char *nvarguscamerasrc_getCapabilitiesVideoXrawMemory(_nvarguscamerasrcData *data)
{
    char *str = (char *)malloc(sizeof(char) * 100);
    if (nvarguscamerasrc_isRead(data) == false)
    {
        fprintf(stderr, "json have not read yet\n");
        exit(EXIT_FAILURE);
    }

    cJSON *video_xraw_memory= cJSON_GetObjectItemCaseSensitive(data->nvarguscamerasrcJSON, "video_xraw_memory");
    cJSON *width = cJSON_GetObjectItemCaseSensitive(video_xraw_memory, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(video_xraw_memory, "height");
    cJSON *framerate = cJSON_GetObjectItemCaseSensitive(video_xraw_memory, "framerate");
    cJSON *format = cJSON_GetObjectItemCaseSensitive(video_xraw_memory, "format");
    if (cJSON_IsNumber(width))
    {
        snprintf(str,100, "video/x-raw(memory:NVMM), width=(int)%d, height=(int)%d, framerate=(fraction)%d/1, format=%s",width->valueint, height->valueint, framerate->valueint, format->valuestring);
        return str;
    }
    return NULL;
}

void nvarguscamerasrc_free(_nvarguscamerasrcData *data)
{
    free(data);
    data = NULL;
}

bool nvarguscamerasrc_isRead(_nvarguscamerasrcData *data)
{
    if (data->nvarguscamerasrcJSON == NULL)
    {
        return false;
    }
    return true;
}
