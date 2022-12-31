#include "nvvidconv.h"

static size_t getFileSize(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}

_nvvidconvData *nvvidconv_init(void)
{
    _nvvidconvData *newData = (_nvvidconvData *)malloc(sizeof(_nvvidconvData));
    return newData;
}

void nvvidconv_ReadJSONContent(_nvvidconvData *data, const char *filepath)
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
    data->nvvidconvJSON= cJSON_GetObjectItemCaseSensitive(monitor, "nvvidconv");
}

char *nvvidconv_getPropertiesName(_nvvidconvData *data)
{
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "name");
    if (name->valuestring == NULL)
    {
        return "nvvidconv0";
    }
    return name->valuestring;
}

char *nvvidconv_getPropertiesParent(_nvvidconvData *data)
{
    return NULL;
}

bool nvvidconv_getPropertiesQoS(_nvvidconvData *data)
{
    cJSON *qos = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "qos");
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

bool nvvidconv_getPropertiesSilent(_nvvidconvData *data)
{
    cJSON *silent = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "silent");
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
    return false;
}

enum GstNvVideoFlipMethod nvvidconv_getPropertiesFlipMethod(_nvvidconvData *data)
{
    cJSON *flip_method = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "flip_method");
    if (cJSON_IsNumber(flip_method))
    {
        return flip_method->valueint;
    }
    return 0;
}

unsigned int nvvidconv_getPropertiesOutputBuffers(_nvvidconvData *data)
{
    cJSON *output_buffers = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "output_buffers");
    if (cJSON_IsNull(output_buffers))
    {
        return 4;
    }
    return (unsigned int)output_buffers->valuedouble;
}

enum GstInterpolationMethod nvvidconv_getPropertiesInterpolationMethod(_nvvidconvData *data)
{
    cJSON *interpolation_method = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "interpolation_method");
    if (cJSON_IsNumber(interpolation_method))
    {
        return interpolation_method->valueint;
    }
    return 0;
}

int nvvidconv_getPropertiesLeft(_nvvidconvData *data)
{
    cJSON *left = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "left");
    if (cJSON_IsNumber(left))
    {
        return left->valueint;
    }
    return 0;
}

int nvvidconv_getPropertiesRight(_nvvidconvData *data)
{
    cJSON *right = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "right");
    if (cJSON_IsNumber(right))
    {
        return right->valueint;
    }
    return 0;
}

int nvvidconv_getPropertiesTop(_nvvidconvData *data)
{
    cJSON *top = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "top");
    if (cJSON_IsNumber(top))
    {
        return top->valueint;
    }
    return 0;
}

int nvvidconv_getPropertiesBottom(_nvvidconvData *data)
{
    cJSON *bottom = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "bottom");
    if (cJSON_IsNumber(bottom))
    {
        return bottom->valueint;
    }
    return 0;
}

bool nvvidconv_getPropertiesB1Output(_nvvidconvData *data)
{
    cJSON *b1_output = cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "b1_output");
    if (cJSON_IsBool(b1_output))
    {
        if (cJSON_IsTrue(b1_output))
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

char *nvvidconv_getCapabilitiesVideoXraw(_nvvidconvData *data)
{
    char *str = (char *)malloc(sizeof(char) * 100);

    cJSON *video_xraw= cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "video_xraw");
    cJSON *width = cJSON_GetObjectItemCaseSensitive(video_xraw, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(video_xraw, "height");
    cJSON *framerate = cJSON_GetObjectItemCaseSensitive(video_xraw, "framerate");
    cJSON *format = cJSON_GetObjectItemCaseSensitive(video_xraw, "format");
    if (cJSON_IsNumber(width))
    {
        snprintf(str,100, "video/x-raw, width=(int)%d, height=(int)%d, framerate=(fraction)%d/1, format=%s",width->valueint, height->valueint, framerate->valueint, format->valuestring);
        return str;
    }
    return NULL;
}

char *nvvidconv_getCapabilitiesVideoXrawMemory(_nvvidconvData *data)
{
    char *str = (char *)malloc(sizeof(char) * 100);
    cJSON *video_xraw_memory= cJSON_GetObjectItemCaseSensitive(data->nvvidconvJSON, "video_xraw_memory");
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

void nvvidconv_free(_nvvidconvData *data)
{
    free(data);
    data = NULL;
}
