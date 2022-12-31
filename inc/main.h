#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <gst/gst.h>
#include "nvarguscamerasrc.h"
#include "nvvidconv.h"
#include "omxh264enc.h"
#include "rtspclientsink.h"

#define BUF_LEN (10 * (sizeof(struct inotify_event) + 1024 + 1))
