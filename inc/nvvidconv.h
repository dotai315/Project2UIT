#ifndef _NVVIDCONV_H_
#define _NVVIDCONV_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>

enum GstNvVideoFlipMethod
{
    NONE,
    COUNTERCLOCKWISE,
    ROTATE_180,
    CLOCKWISE,
    HORIZONTAL_FLIP,
    UPPER_RIGHT_DIAGONAL,
    VERTIALCAL_FLIP,
    UPPER_LEFT_DIAGONAL
};

enum GstInterpolationMethod
{
    NEAREST,
    BILINEAR,
    FIVE_TAP,
    TEN_TAP,
    SMART,
    NICEST
};

typedef struct __NVVIDCONV_DATA
{
    cJSON *nvvidconvJSON;
} _nvvidconvData; 

/* Constructor */
_nvvidconvData *nvvidconv_init(void);

/* set method */
void nvvidconv_ReadJSONContent(_nvvidconvData *data, const char *filepath);

/* get method */
char *nvvidconv_getPropertiesName(_nvvidconvData *data);
char *nvvidconv_getPropertiesParent(_nvvidconvData *data);
bool nvvidconv_getPropertiesQoS(_nvvidconvData *data);
bool nvvidconv_getPropertiesSilent(_nvvidconvData *data);
enum GstNvVideoFlipMethod nvvidconv_getPropertiesFlipMethod(_nvvidconvData *data);
unsigned int nvvidconv_getPropertiesOutputBuffers(_nvvidconvData *data);
enum GstInterpolationMethod nvvidconv_getPropertiesInterpolationMethod(_nvvidconvData *data);
int nvvidconv_getPropertiesLeft(_nvvidconvData *data);
int nvvidconv_getPropertiesRight(_nvvidconvData *data);
int nvvidconv_getPropertiesTop(_nvvidconvData *data);
int nvvidconv_getPropertiesBottom(_nvvidconvData *data);
bool nvvidconv_getPropertiesB1Output(_nvvidconvData *data);

char *nvvidconv_getCapabilitiesVideoXraw(_nvvidconvData *data);
char *nvvidconv_getCapabilitiesVideoXrawMemory(_nvvidconvData *data);

void nvvidconv_free(_nvvidconvData *data);

#endif