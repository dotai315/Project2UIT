#include "main.h"

pthread_t readJSONThread;
pthread_t gstCameraThread;

_nvarguscamerasrcData *nvarguscamerasrcData;
_nvvidconvData *nvvidconvData;
_omxh264encData *omxh264encData;
_rtspclientsinkData *rtspclientsinkData;

GstElement              *pipeline;
GstElement              *nvarguscamerasrc;
GstElement              *nvvidconv;
GstElement              *omxh264enc;
GstElement              *rtspclientsink;
GstElementFactory       *nvarguscamerasrcFactory;
GstElementFactory       *nvvidconvFactory;
GstElementFactory       *omxh264encFactory;
GstElementFactory       *rtspclientsinkFactory;
GstStateChangeReturn    ret;
gboolean                terminate = FALSE;
GstBus                  *bus;
GstMessage              *msg;
GstCaps                 *caps;

char *file_path;

static gboolean link_elements_with_filter (GstElement *element1, GstElement *element2, GstCaps *caps)
{
    gboolean link_ok;
    g_print("link src to dest\n");
    link_ok = gst_element_link_filtered (element1, element2, caps);

    g_print("caps unref\n");
    gst_caps_unref (caps);

    if (!link_ok) {
        g_warning ("Failed to link element1 and element2!\n");
    }
    else
    {
        g_print("Link OK\n");
    }

    return link_ok;
}

//gst-launch-1.0 
//nvarguscamerasrc sensor_id=0 ! 'video/x-raw(memory:NVMM),width=3280, height=2464, framerate=21/1, format=NV12' !  
//nvvidconv flip-method=2 ! 'video/x-raw, width=816, height=616' ! 
//omxh264enc ! 'video/x-h264,stream-format=byte-stream' ! 
//rtspclientsink location=rtsp://localhost:8554/mystream

void cameraInit(void)
{
    nvarguscamerasrcFactory = gst_element_factory_find("nvarguscamerasrc");
    nvvidconvFactory = gst_element_factory_find("nvvidconv");
    omxh264encFactory = gst_element_factory_find("omxh264enc");
    rtspclientsinkFactory = gst_element_factory_find("rtspclientsink");
    nvarguscamerasrc = gst_element_factory_create(nvarguscamerasrcFactory, "nvarguscamerasrc");
    nvvidconv = gst_element_factory_create(nvvidconvFactory, "nvvidconv");
    omxh264enc= gst_element_factory_create(omxh264encFactory, "omxh264enc");
    rtspclientsink = gst_element_factory_create(rtspclientsinkFactory, "rtspclientsink");
    pipeline = gst_pipeline_new("camera-pipeline");
    gst_bin_add_many(GST_BIN(pipeline), nvarguscamerasrc, nvvidconv, omxh264enc, rtspclientsink, NULL);
    nvarguscamerasrc_ReadJSONContent(nvarguscamerasrcData, file_path);
    nvvidconv_ReadJSONContent(nvvidconvData, file_path);
    omxh264enc_ReadJSONContent(omxh264encData, file_path);
    rtspclientsink_ReadJSONContent(rtspclientsinkData, file_path);

    //nvarguscamerasrc sensor_id=0 ! 'video/x-raw(memory:NVMM),width=3280, height=2464, framerate=21/1, format=NV12'
    g_object_set(nvarguscamerasrc, "sensor-id", nvarguscamerasrc_getPropertiesSensorId(nvarguscamerasrcData), NULL);
    caps = gst_caps_from_string(nvarguscamerasrc_getCapabilitiesVideoXrawMemory(nvarguscamerasrcData));
    link_elements_with_filter(nvarguscamerasrc, nvvidconv, caps);

    //nvvidconv flip-method=2 ! 'video/x-raw, width=816, height=616' 
    g_object_set(nvvidconv, "flip-method", nvvidconv_getPropertiesFlipMethod(nvvidconvData), NULL);
    caps = gst_caps_from_string(nvvidconv_getCapabilitiesVideoXraw(nvvidconvData));
    link_elements_with_filter(nvvidconv, omxh264enc, caps);

    caps = gst_caps_from_string(omxh264enc_getCapabilitiesVideoXh264(omxh264encData));
    link_elements_with_filter(omxh264enc, rtspclientsink, caps);

    //rtspclientsink location=rtsp://localhost:8554/mystream
    g_object_set(rtspclientsink, "location", rtspclientsink_getPropertiesLocation(rtspclientsinkData), NULL);
}

void cameraUpdate(void)
{
    nvarguscamerasrc = gst_element_factory_create(nvarguscamerasrcFactory, "nvarguscamerasrc");
    nvvidconv = gst_element_factory_create(nvvidconvFactory, "nvvidconv");
    omxh264enc= gst_element_factory_create(omxh264encFactory, "omxh264enc");
    rtspclientsink = gst_element_factory_create(rtspclientsinkFactory, "rtspclientsink");
    pipeline = gst_pipeline_new("camera-pipeline");
    gst_bin_add_many(GST_BIN(pipeline), nvarguscamerasrc, nvvidconv, omxh264enc, rtspclientsink, NULL);
    nvarguscamerasrc_ReadJSONContent(nvarguscamerasrcData, file_path);
    nvvidconv_ReadJSONContent(nvvidconvData, file_path);
    omxh264enc_ReadJSONContent(omxh264encData, file_path);
    rtspclientsink_ReadJSONContent(rtspclientsinkData, file_path);

    //nvarguscamerasrc sensor_id=0 ! 'video/x-raw(memory:NVMM),width=3280, height=2464, framerate=21/1, format=NV12'
    g_object_set(nvarguscamerasrc, "sensor-id", nvarguscamerasrc_getPropertiesSensorId(nvarguscamerasrcData), NULL);
    printf("nva caps: %s\n", nvarguscamerasrc_getCapabilitiesVideoXrawMemory(nvarguscamerasrcData));
    caps = gst_caps_from_string(nvarguscamerasrc_getCapabilitiesVideoXrawMemory(nvarguscamerasrcData));
    link_elements_with_filter(nvarguscamerasrc, nvvidconv, caps);

    //nvvidconv flip-method=2 ! 'video/x-raw, width=816, height=616' 
    g_object_set(nvvidconv, "flip-method", nvvidconv_getPropertiesFlipMethod(nvvidconvData), NULL);
    printf("nvvidconv caps: %s\n", nvvidconv_getCapabilitiesVideoXraw(nvvidconvData));
    caps = gst_caps_from_string(nvvidconv_getCapabilitiesVideoXraw(nvvidconvData));
    link_elements_with_filter(nvvidconv, omxh264enc, caps);

    printf("omxh264enc caps: %s\n", omxh264enc_getCapabilitiesVideoXh264(omxh264encData));
    caps = gst_caps_from_string(omxh264enc_getCapabilitiesVideoXh264(omxh264encData));
    link_elements_with_filter(omxh264enc, rtspclientsink, caps);

    //rtspclientsink location=rtsp://localhost:8554/mystream
    g_object_set(rtspclientsink, "location", rtspclientsink_getPropertiesLocation(rtspclientsinkData), NULL);
}

void cameraPlay(void)
{
    /* Start playing */
    ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void cameraPause(void)
{
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref(nvarguscamerasrcFactory);
    gst_object_unref(nvvidconvFactory);
    gst_object_unref(omxh264encFactory);
    gst_object_unref(rtspclientsinkFactory);
    gst_object_unref (pipeline);
}

void sigUser1Handler(int signum)
{
    signal(SIGUSR1, SIG_IGN);
    cameraPause();
    cameraUpdate();
    printf("Here\n");
    cameraPlay();
    signal(SIGUSR1, sigUser1Handler);
}

void *readJSONThreadFunc(void *vargp)
{
    int inotifyFd;
    int wd;
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    ssize_t numRead;
    char *p;
    struct inotify_event *event;

    inotifyFd = inotify_init();
    if (inotifyFd == -1)
    {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    wd = inotify_add_watch(inotifyFd, file_path, IN_MODIFY);
    if (wd == -1)
    {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        numRead = read(inotifyFd, buf, BUF_LEN);
        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            if (event->mask & IN_MODIFY)
            {
                kill(getpid(), SIGUSR1);
            }
            p += sizeof(struct inotify_event) + event->len;
        }
    }

    return NULL;
}

void *gstCameraThreadFunc(void *vargp)
{
    cameraInit();
    //cameraUpdate();

    cameraPlay();

    /* Wait until error, EOS or State Change */
    bus = gst_element_get_bus (pipeline);
    do {
        msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_STATE_CHANGED);

        /* Parse message */
        if (msg != NULL) {
            GError *err;
            gchar *debug_info;
            switch (GST_MESSAGE_TYPE (msg)) {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error (msg, &err, &debug_info);
                g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
                g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
                g_clear_error (&err);
                g_free (debug_info);
                terminate = TRUE;
                break;
            case GST_MESSAGE_EOS:
                g_print ("End-Of-Stream reached.\n");
                terminate = TRUE;
                break;
            case GST_MESSAGE_STATE_CHANGED:
                /* We are only interested in state-changed messages from the pipeline */
                if (GST_MESSAGE_SRC (msg) == GST_OBJECT (pipeline)) {
                    GstState old_state, new_state, pending_state;
                    gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
                    g_print ("\nPipeline state changed from %s to %s:\n",
                    gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
                }
                break;
            default:
                /* We should not reach here because we only asked for ERRORs, EOS and STATE_CHANGED */
                g_printerr ("Unexpected message received.\n");
                break;
            }
            gst_message_unref (msg);
        }
    } while (!terminate);

    gst_object_unref(bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref(nvarguscamerasrcFactory);
    gst_object_unref(nvvidconvFactory);
    gst_object_unref(omxh264encFactory);
    gst_object_unref(rtspclientsinkFactory);
    gst_object_unref (pipeline);

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s file_path\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    gst_init(&argc, &argv);
    file_path = argv[1];

    nvarguscamerasrcData = nvarguscamerasrc_init();
    nvvidconvData = nvvidconv_init();
    omxh264encData = omxh264enc_init();
    rtspclientsinkData = rtspclientsink_init();

    cameraInit();

    signal(SIGUSR1, sigUser1Handler);
    pthread_create(&readJSONThread, NULL, readJSONThreadFunc, NULL);
    pthread_create(&gstCameraThread, NULL, gstCameraThreadFunc, NULL);
    pthread_join(gstCameraThread, NULL);
    pthread_join(readJSONThread, NULL);

    exit(EXIT_SUCCESS);
}