#ifndef __NVARGUSCAMERASRC_H_
#define __NVARGUSCAMERASRC_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>

enum GstNvarguscamWBMode{
    GST_NVCAM_WB_MODE_OFF,
    GST_NVCAM_WB_MODE_AUTO,
    GST_NVCAM_WB_MODE_INCANDESCENT,
    GST_NVCAM_WB_MODE_FLUORESCENT,
    GST_NVCAM_WB_MODE_WARM_FLUORESCENT,
    GST_NVCAM_WB_MODE_DAYLIGHT,
    GST_NVCAM_WB_MODE_CLOUDY_DAYLIGHT,
    GST_NVCAM_WB_MODE_TWILIGHT,
    GST_NVCAM_WB_MODE_SHADE,
    GST_NVCAM_WB_MODE_MANUAL
};

enum GstNvArgusCamTNRMode {
    GST_NVCAM_NR_OFF,
    GST_NVCAM_NR_FAST,
    GST_NVCAM_NR_HIGHQUALITY
};

enum GstNvArgusCamEEMode {
    GST_NVCAM_EE_OFF,
    GST_NVCAM_EE_FAST,
    GST_NVCAM_EE_HIGHQUALITY
};

enum GstNvArgusCamAeAntiBandingMode {
    GST_NVCAM_AEANTIBANDING_OFF,
    GST_NVCAM_AEANTIBANDING_AUTO,
    GST_NVCAM_AEANTIBANDING_50HZ,
    GST_NVCAM_AEANTIBANDING_60HZ
};

typedef struct __NVARGUSCAMERASCAMERASRC_DATA
{
    cJSON *nvarguscamerasrcJSON;
} _nvarguscamerasrcData; 

/* Constructor */
_nvarguscamerasrcData                   *nvarguscamerasrc_init(void);

/* set method */
void                                    nvarguscamerasrc_ReadJSONContent                   (_nvarguscamerasrcData *data, const char *filepath);

// get method
char                                    *nvarguscamerasrc_getPropertiesName                 (_nvarguscamerasrcData *data);
char                                    *nvarguscamerasrc_getPropertiesParent               (_nvarguscamerasrcData *data);
unsigned int                            nvarguscamerasrc_getPropertiesBlocksize             (_nvarguscamerasrcData *data);
int                                     nvarguscamerasrc_getPropertiesNumBuffers            (_nvarguscamerasrcData *data);
bool                                    nvarguscamerasrc_getPropertiesTypefind              (_nvarguscamerasrcData *data);
bool                                    nvarguscamerasrc_getPropertiesDoTimeStamp           (_nvarguscamerasrcData *data);
bool                                    nvarguscamerasrc_getPropertiesSilent                (_nvarguscamerasrcData *data);
unsigned int                            nvarguscamerasrc_getPropertiesTimeout               (_nvarguscamerasrcData *data);
enum GstNvarguscamWBMode                nvarguscamerasrc_getPropertiesWbmode                (_nvarguscamerasrcData *data);
float                                   nvarguscamerasrc_getPropertiesSaturation            (_nvarguscamerasrcData *data);
int                                     nvarguscamerasrc_getPropertiesSensorId              (_nvarguscamerasrcData *data);
int                                     nvarguscamerasrc_getPropertiesSensorMode            (_nvarguscamerasrcData *data);
int                                     nvarguscamerasrc_getPropertiesTotalSensorModes      (_nvarguscamerasrcData *data);
char                                    *nvarguscamerasrc_getPropertiesExposureTimeRange    (_nvarguscamerasrcData *data);
char                                    *nvarguscamerasrc_getPropertiesGainRange            (_nvarguscamerasrcData *data);
char                                    *nvarguscamerasrc_getPropertiesIspDigitalGainRange  (_nvarguscamerasrcData *data);
float                                   nvarguscamerasrc_getPropertiesTnrStrength           (_nvarguscamerasrcData *data);
enum GstNvArgusCamTNRMode               nvarguscamerasrc_getPropertiesTnrMode               (_nvarguscamerasrcData *data);
enum GstNvArgusCamEEMode                nvarguscamerasrc_getPropertiesEEmode                (_nvarguscamerasrcData *data);
float                                   nvarguscamerasrc_getPropertiesEEStrength            (_nvarguscamerasrcData *data);
enum GstNvArgusCamAeAntiBandingMode     nvarguscamerasrc_getPropertiesAeantibanding         (_nvarguscamerasrcData *data);
float                                   nvarguscamerasrc_getPropertiesExposureCompensation  (_nvarguscamerasrcData *data);
bool                                    nvarguscamerasrc_getPropertiesAelock                (_nvarguscamerasrcData *data);
char                                    *nvarguscamerasrc_getPropertiesAeregion             (_nvarguscamerasrcData *data);
bool                                    nvarguscamerasrc_getPropertiesAwblock               (_nvarguscamerasrcData *data);
bool                                    nvarguscamerasrc_getPropertiesBufapiVersion         (_nvarguscamerasrcData *data);
char                                    *nvarguscamerasrc_getCapabilitiesVideoXrawMemory    (_nvarguscamerasrcData *data);


/* Destructor */
void                                    nvarguscamerasrc_free(_nvarguscamerasrcData *data);

//API 
bool                                    nvarguscamerasrc_isRead(_nvarguscamerasrcData *data);

#endif