/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (C) 2012 Zhibin Wu, Simon Davie, Nico Kaiser
 * Copyright (C) 2012 QiSS ME Project Team
 * Copyright (C) 2012 Twisted, Sean Neeley
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright (C) 2012 Tomasz Rostanski
 *
=======
 * Copyright (C) 2012 GalaxyICS
 * Copyright (C) 2012 Pavel Kirpichyov aka WaylandACE

>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
 * Copyright (C) 2012 GalaxyICS
 * Copyright (C) 2012 Pavel Kirpichyov aka WaylandACE

>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "CameraHAL"

<<<<<<< HEAD
<<<<<<< HEAD
#define LOG_NDEBUG 1      /* disable LOGV */
//#define DUMP_PARAMS 1   /* dump parameteters after get/set operation */

#define MAX_CAMERAS_SUPPORTED 2

#define CAMERA_ID_FRONT 1
#define CAMERA_ID_BACK 0

#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <cutils/log.h>
#include <ui/legacy/Overlay.h>
#include <camera/CameraParameters.h>
#include <hardware/camera.h>
#include <binder/IMemory.h>
#include "CameraHardwareInterface.h"
#include <cutils/properties.h>
#include <gralloc_priv.h>
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
//#define GRALLOC_USAGE_PMEM_PRIVATE_ADSP GRALLOC_USAGE_PRIVATE_0

#include <camera/CameraParameters.h>
#include <hardware/camera.h>
#include <binder/IMemory.h>
#include <gralloc_priv.h>
#include "CameraHardwareInterface.h"
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

using android::sp;
using android::Overlay;
using android::String8;
using android::IMemory;
using android::IMemoryHeap;
using android::CameraParameters;

using android::CameraInfo;
<<<<<<< HEAD
<<<<<<< HEAD
using android::SEC_getCameraInfo;
using android::SEC_getNumberOfCameras;
using android::SEC_openCameraHardware;
using android::CameraHardwareInterface;

static sp<CameraHardwareInterface> gCameraHals[MAX_CAMERAS_SUPPORTED];
static unsigned int gCamerasOpen = 0;
//static android::Mutex gCameraDeviceLock;
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
using android::HAL_getCameraInfo;
using android::HAL_getNumberOfCameras;
using android::HAL_openCameraHardware;
using android::CameraHardwareInterface;

static sp<CameraHardwareInterface> qCamera;
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

static int camera_device_open(const hw_module_t* module, const char* name,
                              hw_device_t** device);
static int camera_device_close(hw_device_t* device);
static int camera_get_number_of_cameras(void);
static int camera_get_camera_info(int camera_id, struct camera_info *info);
<<<<<<< HEAD
<<<<<<< HEAD
int camera_get_number_of_cameras(void);
static inline void rotateJPEG(void* src,size_t size);
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

static struct hw_module_methods_t camera_module_methods = {
    open: camera_device_open
};

camera_module_t HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        module_api_version: CAMERA_DEVICE_API_VERSION_1_0,
        hal_api_version: 0,
        id: CAMERA_HARDWARE_MODULE_ID,
<<<<<<< HEAD
<<<<<<< HEAD
        name: "7x30 CameraHal Module",
        author: "Zhibin Wu",
=======
        name: "Camera HAL",
        author: "Zhibin Wu & Marcin Chojnacki & Pavel Kirpichyov",
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
        name: "Camera HAL",
        author: "Zhibin Wu & Marcin Chojnacki & Pavel Kirpichyov",
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
        methods: &camera_module_methods,
        dso: NULL, /* remove compilation warnings */
        reserved: {0}, /* remove compilation warnings */
    },
    get_number_of_cameras: camera_get_number_of_cameras,
    get_camera_info: camera_get_camera_info,
};

typedef struct priv_camera_device {
    camera_device_t base;
    /* specific "private" data can go here (base.priv) */
    int cameraid;
    /* new world */
    preview_stream_ops *window;
    camera_notify_callback notify_callback;
    camera_data_callback data_callback;
    camera_data_timestamp_callback data_timestamp_callback;
    camera_request_memory request_memory;
    void *user;
<<<<<<< HEAD
<<<<<<< HEAD
    int mFixFocus;
=======
    int preview_started;
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
    int preview_started;
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    /* old world*/
    int preview_width;
    int preview_height;
    sp<Overlay> overlay;
    gralloc_module_t const *gralloc;
} priv_camera_device_t;

<<<<<<< HEAD
<<<<<<< HEAD

static struct {
    int type;
    const char *text;
} msg_map[] = {
    {0x0001, "CAMERA_MSG_ERROR"},
    {0x0002, "CAMERA_MSG_SHUTTER"},
    {0x0004, "CAMERA_MSG_FOCUS"},
    {0x0008, "CAMERA_MSG_ZOOM"},
    {0x0010, "CAMERA_MSG_PREVIEW_FRAME"},
    {0x0020, "CAMERA_MSG_VIDEO_FRAME"},
    {0x0040, "CAMERA_MSG_POSTVIEW_FRAME"},
    {0x0080, "CAMERA_MSG_RAW_IMAGE"},
    {0x0100, "CAMERA_MSG_COMPRESSED_IMAGE"},
    {0x0200, "CAMERA_MSG_RAW_IMAGE_NOTIFY"},
    {0x0400, "CAMERA_MSG_PREVIEW_METADATA"},
    {0x0000, "CAMERA_MSG_ALL_MSGS"}, //0xFFFF
    {0x0000, "NULL"},
};

static void dump_msg(const char *tag, int msg_type)
{
    int i;
    for (i = 0; msg_map[i].type; i++) {
        if (msg_type & msg_map[i].type) {
            ALOGI("%s: %s", tag, msg_map[i].text);
        }
    }
}

/*******************************************************************
 * overlay hook
 *******************************************************************/

static void wrap_set_fd_hook(void *data, int fd)
{
    priv_camera_device_t* dev = NULL;
    ALOGV("%s+++: data %p", __FUNCTION__, data);

    if(!data)
        return;

    dev = (priv_camera_device_t*) data;
}

static void wrap_set_crop_hook(void *data,
                               uint32_t x, uint32_t y,
                               uint32_t w, uint32_t h)
{
    priv_camera_device_t* dev = NULL;
    ALOGV("%s+++: %p", __FUNCTION__,data);

    if(!data)
        return;

    dev = (priv_camera_device_t*) data;
}

//QiSS ME for preview
static void wrap_queue_buffer_hook(void *data, void* buffer)
{
    sp<IMemoryHeap> heap;
    priv_camera_device_t* dev = NULL;
    preview_stream_ops* window = NULL;
    ALOGV("%s+++: %p", __FUNCTION__,data);

    if(!data)
        return;

    dev = (priv_camera_device_t*) data;

    window = dev->window;

    //QiSS ME fix video preview crash
    if(window == 0)
        return;

    heap = gCameraHals[dev->cameraid]->getPreviewHeap();
    if(heap == 0)
        return;

    int offset = (int)buffer;
    char *frame = (char *)(heap->base()) + offset;

    ALOGV("%s: base:%p offset:%i frame:%p", __FUNCTION__,
         heap->base(), offset, frame);
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
static camera_memory_t *wrap_memory_data(priv_camera_device_t *dev, const sp<IMemory>& dataPtr) {
    if (!dev->request_memory)
        return NULL;

    size_t size;
    ssize_t offset;

    sp<IMemoryHeap> heap = dataPtr->getMemory(&offset, &size);
    void *data = (void *)((char *)(heap->base()) + offset);

    camera_memory_t *mem = dev->request_memory(-1, size, 1, dev->user);

    memcpy(mem->data, data, size);

    return mem;
}

static void wrap_notify_callback(int32_t msg_type, int32_t ext1, int32_t ext2, void* user) {
    if(!user)
        return;

    priv_camera_device_t* dev = (priv_camera_device_t*) user;

    if (dev->notify_callback)
        dev->notify_callback(msg_type, ext1, ext2, dev->user);
}

void CameraHAL_HandlePreviewData(priv_camera_device_t* dev, const sp<IMemory>& dataPtr) {
    preview_stream_ops_t *mWindow = dev->window;
    if(mWindow == NULL) return;

    size_t size;
    ssize_t offset;

    sp<IMemoryHeap> heap = dataPtr->getMemory(&offset, &size);
    if(heap == 0) {
        ALOGE("%s: heap allocation failed", __FUNCTION__);
        return;
    }

    char *frame = (char *)(heap->base()) + offset;

    ALOGV("%s: base:%p offset:%i frame:%p", __FUNCTION__, heap->base(), offset, frame);
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

    int stride;
    void *vaddr;
    buffer_handle_t *buf_handle;

<<<<<<< HEAD
<<<<<<< HEAD
    int width = dev->preview_width;
    int height = dev->preview_height;
    if (0 != window->dequeue_buffer(window, &buf_handle, &stride)) {
        ALOGE("%s: could not dequeue gralloc buffer", __FUNCTION__);
        goto skipframe;
    }
    if (0 == dev->gralloc->lock(dev->gralloc, *buf_handle,
                                GRALLOC_USAGE_SW_WRITE_MASK,
                                0, 0, width, height, &vaddr)) {
        // the code below assumes YUV, not RGB
        if (dev->cameraid==CAMERA_ID_FRONT) {
            /*
            * The YUV420 Semi-Planar frame is constructed as follows:
            *
            * - the Y values are stored in one plane:
            * |-------------------------------| _
            * | Y0 | Y1 | Y2 | Y3 | ... | |
            * | ... | height
            * | | |
            * |-------------------------------| -
            * <------------ width ------------>
            *
            * - the U and V values (sub-sampled by 2) are stored in another plane:
            * |-------------------------------| _
            * | U0 | V0 | U2 | V2 | .... | |
            * | ... | height/2
            * | | |
            * |-------------------------------| -
            * <------------ width ------------>
            */

            uint8_t *buff = (uint8_t *)vaddr;
            int pos = 0;

            //swap Y plane
            for (int y = 0; y < height; ++y)
            {
                pos = y * width;                
                for (int x = 0; x < width; ++x)
                    buff[pos + x] = frame[pos + width - x - 1];
            }

            //swap UV plane
            for (int y = 0; y < height/2; ++y)
            {
                pos += width;
                for (int x = 0; x < width; ++x)
                    buff[pos + x] = frame[pos + width - x - 2];
            }
        } else
            memcpy(vaddr, frame, width * height * 3 / 2);
	        ALOGV("%s: copy frame to gralloc buffer", __FUNCTION__);
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    if (0 != mWindow->dequeue_buffer(mWindow, &buf_handle, &stride)) {
        ALOGE("%s: could not dequeue gralloc buffer", __FUNCTION__);
        goto skipframe;
    }
    if (dev->gralloc == NULL) {
        goto skipframe;
    }
    if (0 == dev->gralloc->lock(dev->gralloc, *buf_handle,
                                GRALLOC_USAGE_SW_WRITE_MASK,
                                0, 0, dev->preview_width, dev->preview_height, &vaddr)) {
        memcpy(vaddr, frame, dev->preview_width * dev->preview_height * 3 / 2);
        ALOGV("%s: copy frame to gralloc buffer", __FUNCTION__);
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    } else {
        ALOGE("%s: could not lock gralloc buffer", __FUNCTION__);
        goto skipframe;
    }

    dev->gralloc->unlock(dev->gralloc, *buf_handle);

<<<<<<< HEAD
<<<<<<< HEAD
    if (0 != window->enqueue_buffer(window, buf_handle)) {
=======
    if (0 != mWindow->enqueue_buffer(mWindow, buf_handle)) {
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
    if (0 != mWindow->enqueue_buffer(mWindow, buf_handle)) {
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
        ALOGE("%s: could not dequeue gralloc buffer", __FUNCTION__);
        goto skipframe;
    }

skipframe:
<<<<<<< HEAD
<<<<<<< HEAD

#ifdef DUMP_PREVIEW_FRAMES
    static int frameCnt = 0;
    int written;
    if (frameCnt >= 100 && frameCnt <= 109 ) {
        char path[128];
        snprintf(path, sizeof(path), "/sdcard/%d_preview.yuv", frameCnt);
        int file_fd = open(path, O_RDWR | O_CREAT, 0666);
        ALOGI("dumping preview frame %d", frameCnt);
        if (file_fd < 0) {
            ALOGE("cannot open file:%s (error:%i)\n", path, errno);
        }
        else
        {
            ALOGV("dumping data");
            written = write(file_fd, (char *)frame,
                            dev->preview_frame_size);
            if(written < 0)
                ALOGE("error in data write");
        }
        close(file_fd);
    }
    frameCnt++;
#endif
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    ALOGV("%s---: ", __FUNCTION__);

    return;
}

<<<<<<< HEAD
<<<<<<< HEAD
/*******************************************************************
 * camera interface callback
 *******************************************************************/

static camera_memory_t *wrap_memory_data(priv_camera_device_t *dev,
                                         const sp<IMemory>& dataPtr)
{
    void *data;
    size_t size;
    ssize_t offset;
    sp<IMemoryHeap> heap;
    camera_memory_t *mem;

    ALOGV("%s+++,dev->request_memory %p", __FUNCTION__,dev->request_memory);

    if (!dev->request_memory)
        return NULL;

    heap = dataPtr->getMemory(&offset, &size);
    data = (void *)((char *)(heap->base()) + offset);

    ALOGV("%s: data: %p size: %i", __FUNCTION__, data, size);
    ALOGV(" offset: %lu", (unsigned long)offset);

    //#define DUMP_CAPTURE_JPEG
#ifdef DUMP_CAPTURE_JPEG
    static int frameCnt = 0;
    int written;
    char path[128];
    snprintf(path, sizeof(path), "/sdcard/%d_capture.jpg", frameCnt);
    int file_fd = open(path, O_RDWR | O_CREAT, 0666);
    ALOGI("dumping capture jpeg %d", frameCnt);
    if (file_fd < 0) {
        ALOGE("cannot open file:%s (error:%i)\n", path, errno);
    }
    else
    {
        ALOGV("dumping jpeg");
        written = write(file_fd, (char *)data,
                        size);
        if(written < 0)
            ALOGE("error in data write");
    }
    close(file_fd);
    frameCnt++;
#endif

    mem = dev->request_memory(-1, size, 1, dev->user);

    ALOGV(" mem:%p,mem->data%p ",  mem,mem->data);

    memcpy(mem->data, data, size);
    /*if (dev->cameraid==CAMERA_ID_FRONT)
        rotateJPEG(mem->data,size);*/

    ALOGV("%s---", __FUNCTION__);
    return mem;
}

static void wrap_notify_callback(int32_t msg_type, int32_t ext1,
                                 int32_t ext2, void* user)
{
    priv_camera_device_t* dev = NULL;

    ALOGV("%s+++: type %i user %p", __FUNCTION__, msg_type,user);
    dump_msg(__FUNCTION__, msg_type);

    if(!user)
        return;

    dev = (priv_camera_device_t*) user;

    if (dev->notify_callback)
        dev->notify_callback(msg_type, ext1, ext2, dev->user);

    ALOGV("%s---", __FUNCTION__);
}

//QiSS ME for capture
static void wrap_data_callback(int32_t msg_type, const sp<IMemory>& dataPtr,
                               void* user)
{
    camera_memory_t *data = NULL;
    priv_camera_device_t* dev = NULL;

    ALOGV("%s+++: type %i user %p", __FUNCTION__, msg_type,user);
    dump_msg(__FUNCTION__, msg_type);

    if(!user)
        return;

    dev = (priv_camera_device_t*) user;

    if (msg_type == CAMERA_MSG_RAW_IMAGE)
    {
        gCameraHals[dev->cameraid]->disableMsgType(CAMERA_MSG_RAW_IMAGE);
        return;
    }

    data = wrap_memory_data(dev, dataPtr);
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
static void wrap_data_callback(int32_t msg_type, const sp<IMemory>& dataPtr, void* user) {
    if(!user) return;

    priv_camera_device_t* dev = (priv_camera_device_t*) user;
    if (msg_type == CAMERA_MSG_RAW_IMAGE) {
        qCamera->disableMsgType(CAMERA_MSG_RAW_IMAGE);
        return;
    }

    if (dataPtr == NULL) {
        ALOGE("%s+++: received null data", __FUNCTION__);
        return;
    }

    if(msg_type == CAMERA_MSG_PREVIEW_FRAME) {
        CameraHAL_HandlePreviewData(dev, dataPtr);
    }

    camera_memory_t *data = wrap_memory_data(dev, dataPtr);
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

    if (dev->data_callback)
        dev->data_callback(msg_type, data, 0, NULL, dev->user);

<<<<<<< HEAD
<<<<<<< HEAD
    if (NULL != data) {
        data->release(data);
    }

    ALOGV("%s---", __FUNCTION__);
}

//QiSS ME for record
static void wrap_data_callback_timestamp(nsecs_t timestamp, int32_t msg_type,
                                         const sp<IMemory>& dataPtr, void* user)
{
    priv_camera_device_t* dev = NULL;
    camera_memory_t *data = NULL;

    ALOGV("%s+++: type %i user %p ts %u", __FUNCTION__, msg_type, user, timestamp);
    dump_msg(__FUNCTION__, msg_type);

    if (!user)
        return;

    dev = (priv_camera_device_t*) user;

    data = wrap_memory_data(dev, dataPtr);

    if (dev->data_timestamp_callback)
        dev->data_timestamp_callback(timestamp,msg_type, data, 0, dev->user);

    gCameraHals[dev->cameraid]->releaseRecordingFrame(dataPtr);//QiSS ME need release or record will stop

    if ( NULL != data ) {
        data->release(data);
    }

    ALOGV("%s---", __FUNCTION__);
}

/*******************************************************************
 * implementation of priv_camera_device_ops functions
 *******************************************************************/

void CameraHAL_FixupParams(android::CameraParameters &camParams, priv_camera_device_t* dev)
{
    const char *preferred_size = "640x480";

    camParams.set(android::CameraParameters::KEY_VIDEO_FRAME_FORMAT,
                  android::CameraParameters::PIXEL_FORMAT_YUV420SP);

    if (!camParams.get(CameraParameters::KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO)) {
        camParams.set(CameraParameters::KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO,
                  preferred_size);
    }

    if (dev->cameraid == CAMERA_ID_FRONT) {
        camParams.set(CameraParameters::KEY_SUPPORTED_ISO_MODES, "");
		camParams.set(CameraParameters::KEY_SUPPORTED_FOCUS_MODES,
                  CameraParameters::FOCUS_MODE_INFINITY);

    	camParams.set(CameraParameters::KEY_FOCUS_MODE,
                  CameraParameters::FOCUS_MODE_INFINITY);

    	camParams.set(CameraParameters::KEY_SUPPORTED_SCENE_MODES, "");
    	camParams.set(CameraParameters::KEY_SUPPORTED_EFFECTS, "");
    }

    if (dev->cameraid == CAMERA_ID_BACK) {
        if (!camParams.get(android::CameraParameters::KEY_MAX_NUM_FOCUS_AREAS)) {
            camParams.set(CameraParameters::KEY_MAX_NUM_FOCUS_AREAS, 1);
        }

        camParams.set(CameraParameters::KEY_MAX_ZOOM, "12");
        camParams.set(CameraParameters::KEY_ZOOM_RATIOS, "100,125,150,175,200,225,250,275,300,325,350,375,400");
        camParams.set(CameraParameters::KEY_ZOOM_SUPPORTED, CameraParameters::TRUE);

        camParams.set(CameraParameters::KEY_SUPPORTED_EFFECTS, "none,mono,negative,sepia");
        camParams.set(CameraParameters::KEY_SUPPORTED_FOCUS_MODES, "auto,infinity,normal,macro,facedetect,touchaf");
    }

    camParams.set(CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES, "30,15,7");

    camParams.set(CameraParameters::KEY_MAX_EXPOSURE_COMPENSATION, 4);
    camParams.set(CameraParameters::KEY_MIN_EXPOSURE_COMPENSATION, -4);
    camParams.set(CameraParameters::KEY_EXPOSURE_COMPENSATION_STEP, 1);

    camParams.set(CameraParameters::KEY_MAX_SATURATION, 10);
    camParams.set(CameraParameters::KEY_MAX_CONTRAST, 10);
    camParams.set(CameraParameters::KEY_MAX_SHARPNESS, 30);

    //keys for compatibility with other apps
    camParams.set("max-saturation", 10);
    camParams.set("max-contrast", 10);
    camParams.set("max-sharpness", 30);

}

int camera_set_preview_window(struct camera_device * device,
                              struct preview_stream_ops *window)
{
    int min_bufs = -1;
    int kBufferCount = 4;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++,device %p", __FUNCTION__,device);

    if(!device)
        return -EINVAL;

    dev = (priv_camera_device_t*) device;

    dev->window = window;

    if (!window) {
        ALOGI("%s---: window is NULL", __FUNCTION__);
        gCameraHals[dev->cameraid]->setOverlay(NULL);
        return 0;
    }

    if (!dev->gralloc) {
        if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID,
                          (const hw_module_t **)&(dev->gralloc))) {
            ALOGE("%s: Fail on loading gralloc HAL", __FUNCTION__);
        }
    }

    if (window->get_min_undequeued_buffer_count(window, &min_bufs)) {
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    if (data != NULL) {
        data->release(data);
    }
}

static void wrap_data_callback_timestamp(nsecs_t timestamp, int32_t msg_type, const sp<IMemory>& dataPtr, void* user) {
    if(!user)
        return;

    priv_camera_device_t* dev = (priv_camera_device_t*) user;

    camera_memory_t *data = wrap_memory_data(dev, dataPtr);

    if (dev->data_timestamp_callback)
        dev->data_timestamp_callback(timestamp, msg_type, data, 0, dev->user);

    qCamera->releaseRecordingFrame(dataPtr);

    if (data != NULL) {
        data->release(data);
    }
}

void CameraHAL_FixupParams(android::CameraParameters &camParams) {
    const char *video_sizes = "640x480,384x288,352x288,320x240,240x160,176x144";
    const char *preferred_video_size = "640x480";

#ifdef ENABLE_FLASH_AND_AUTOFOCUS
    const char *focus_mode_values = "auto,infinity,touch";
    const char *flash_mode_values = "auto,on,off,torch";

    camParams.set(CameraParameters::KEY_SUPPORTED_FOCUS_MODES, focus_mode_values);
    camParams.set(CameraParameters::KEY_SUPPORTED_FLASH_MODES, flash_mode_values);
#endif

    camParams.set(CameraParameters::KEY_VIDEO_FRAME_FORMAT, CameraParameters::PIXEL_FORMAT_YUV420SP);
    camParams.set(CameraParameters::KEY_VIDEO_SIZE, preferred_video_size);

    if (!camParams.get(CameraParameters::KEY_SUPPORTED_VIDEO_SIZES)) {
         camParams.set(CameraParameters::KEY_SUPPORTED_VIDEO_SIZES, video_sizes); }

    if (!camParams.get(CameraParameters::KEY_MAX_NUM_FOCUS_AREAS)) {
        camParams.set(CameraParameters::KEY_MAX_NUM_FOCUS_AREAS, 1); }
}

int camera_set_preview_window(struct camera_device * device, struct preview_stream_ops *window) {
    int min_bufs     = -1;
    int kBufferCount = 4;

    ALOGV("camera_set_preview_window : Window :%p\n", window);
    if (device == NULL) {
        ALOGE("camera_set_preview_window : Invalid device.\n");
        return -EINVAL;
    }
    ALOGV("camera_set_preview_window : window :%p\n", window);

    priv_camera_device_t* dev = (priv_camera_device_t*) device;
    dev->window = window;
    if(window == NULL) {
        return 0;
    }
    if (!dev->gralloc) {
        if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID, (const hw_module_t **)&(dev->gralloc))) {
            ALOGE("%s: Fail on loading gralloc HAL", __FUNCTION__);
        }
    }
    if (dev->window->get_min_undequeued_buffer_count(dev->window, &min_bufs)) {
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
        ALOGE("%s---: could not retrieve min undequeued buffer count", __FUNCTION__);
        return -1;
    }

<<<<<<< HEAD
<<<<<<< HEAD
    ALOGI("%s: bufs:%i", __FUNCTION__, min_bufs);

    if (min_bufs >= kBufferCount) {
        ALOGE("%s: min undequeued buffer count %i is too high (expecting at most %i)",
             __FUNCTION__, min_bufs, kBufferCount - 1);
    }

    ALOGI("%s: setting buffer count to %i", __FUNCTION__, kBufferCount);
    if (window->set_buffer_count(window, kBufferCount)) {
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    ALOGV("%s: bufs: %i", __FUNCTION__, min_bufs);

    if (min_bufs >= kBufferCount) {
        ALOGE("%s: min undequeued buffer count %i is too high (expecting at most %i)", __FUNCTION__, min_bufs, kBufferCount - 1);
    }

    ALOGV("%s: setting buffer count to %i", __FUNCTION__, kBufferCount);
    if (dev->window->set_buffer_count(dev->window, kBufferCount)) {
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
        ALOGE("%s---: could not set buffer count", __FUNCTION__);
        return -1;
    }

<<<<<<< HEAD
<<<<<<< HEAD
    int preview_width;
    int preview_height;

    CameraParameters params = gCameraHals[dev->cameraid]->getParameters();
    params.getPreviewSize(&preview_width, &preview_height);

    int hal_pixel_format = HAL_PIXEL_FORMAT_YCrCb_420_SP;

    const char *str_preview_format = params.getPreviewFormat();

    ALOGI("%s: preview format %s", __FUNCTION__, str_preview_format);

    //Enable panorama without camera application "hacks"
    //if (window->set_usage(window, GRALLOC_USAGE_SW_WRITE_MASK)) {
    //    ALOGE("%s---: could not set usage on gralloc buffer", __FUNCTION__);
    //    return -1;
    //}

    window->set_usage(window, GRALLOC_USAGE_PRIVATE_SYSTEM_HEAP | GRALLOC_USAGE_HW_RENDER);

    if (window->set_buffers_geometry(window, preview_width,
                                     preview_height, hal_pixel_format)) {
        ALOGE("%s---: could not set buffers geometry to %s",
             __FUNCTION__, str_preview_format);
        return -1;
    }

    dev->preview_width = preview_width;
    dev->preview_height = preview_height;

    if (dev->overlay == NULL) {
        dev->overlay =  new Overlay(wrap_set_fd_hook,
                                    wrap_set_crop_hook,
                                    wrap_queue_buffer_hook,
                                    (void *)dev);
    }
    gCameraHals[dev->cameraid]->setOverlay(dev->overlay);

    ALOGI("%s---", __FUNCTION__);
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    CameraParameters params = qCamera->getParameters();
    params.getPreviewSize(&dev->preview_width, &dev->preview_height);

    const char *str_preview_format = params.getPreviewFormat();

    ALOGV("%s: preview format %s", __FUNCTION__, str_preview_format);

    dev->window->set_usage(dev->window, GRALLOC_USAGE_PRIVATE_SYSTEM_HEAP | GRALLOC_USAGE_SW_READ_OFTEN);

    if (dev->window->set_buffers_geometry(dev->window, dev->preview_width,
                                     dev->preview_height, HAL_PIXEL_FORMAT_YCrCb_420_SP)) {
        ALOGE("%s---: could not set buffers geometry to %s", __FUNCTION__, str_preview_format);
        return -1;
    }
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    return 0;
}

void camera_set_callbacks(struct camera_device * device,
                          camera_notify_callback notify_cb,
                          camera_data_callback data_cb,
                          camera_data_timestamp_callback data_cb_timestamp,
                          camera_request_memory get_memory,
<<<<<<< HEAD
<<<<<<< HEAD
                          void *user)
{
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++,device %p", __FUNCTION__,device);

    if(!device)
        return;

    dev = (priv_camera_device_t*) device;

    dev->notify_callback = notify_cb;
    dev->data_callback = data_cb;
    dev->data_timestamp_callback = data_cb_timestamp;
    dev->request_memory = get_memory;
    dev->user = user;

    gCameraHals[dev->cameraid]->setCallbacks(wrap_notify_callback, wrap_data_callback,
                                             wrap_data_callback_timestamp, (void *)dev);

    ALOGI("%s---", __FUNCTION__);
}

void camera_enable_msg_type(struct camera_device * device, int32_t msg_type)
{
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: type %i device %p", __FUNCTION__, msg_type,device);
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
                          void *user) {
    ALOGV("%s+++, device %p", __FUNCTION__,device);

    if(!device) return;

    priv_camera_device_t* dev    = (priv_camera_device_t*) device;

    dev->notify_callback         = notify_cb;
    dev->data_callback           = data_cb;
    dev->data_timestamp_callback = data_cb_timestamp;
    dev->request_memory          = get_memory;
    dev->user                    = user;

    qCamera->setCallbacks(wrap_notify_callback, wrap_data_callback, wrap_data_callback_timestamp, (void *)dev);
}

void camera_enable_msg_type(struct camera_device * device, int32_t msg_type) {
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    if (msg_type & CAMERA_MSG_RAW_IMAGE_NOTIFY) {
        msg_type &= ~CAMERA_MSG_RAW_IMAGE_NOTIFY;
        msg_type |= CAMERA_MSG_RAW_IMAGE;
    }

<<<<<<< HEAD
<<<<<<< HEAD
    dump_msg(__FUNCTION__, msg_type);

    if(!device)
        return;

    dev = (priv_camera_device_t*) device;

    gCameraHals[dev->cameraid]->enableMsgType(msg_type);
    ALOGI("%s---", __FUNCTION__);

}

void camera_disable_msg_type(struct camera_device * device, int32_t msg_type)
{
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: type %i device %p", __FUNCTION__, msg_type,device);
    dump_msg(__FUNCTION__, msg_type);

    if(!device)
        return;

    dev = (priv_camera_device_t*) device;

    /* The camera app disables the shutter too early which leads to crash.
     * Leaving it enabled. */
    if (msg_type == CAMERA_MSG_SHUTTER)
        return;

    gCameraHals[dev->cameraid]->disableMsgType(msg_type);
    ALOGI("%s---", __FUNCTION__);

}

int camera_msg_type_enabled(struct camera_device * device, int32_t msg_type)
{
    priv_camera_device_t* dev = NULL;
    int rv = -EINVAL;

    ALOGI("%s+++: type %i device %p", __FUNCTION__, msg_type,device);

    if(!device)
        return 0;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->msgTypeEnabled(msg_type);
    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

int camera_start_preview(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->startPreview();


    if (dev->mFixFocus) {
        if (dev->cameraid == CAMERA_ID_BACK) {
            ALOGI("%s: Fix focus mode", __FUNCTION__);

            // We need to switch the focus mode once after switching from video at 720P or the camera won't work.
            int rv_fm = -EINVAL;
            CameraParameters camParams;
            camParams = gCameraHals[dev->cameraid]->getParameters();
            const char *prevFocusMode = camParams.get(android::CameraParameters::KEY_FOCUS_MODE);

            camParams.set(CameraParameters::KEY_FOCUS_MODE, CameraParameters::FOCUS_MODE_MACRO);
            rv_fm = gCameraHals[dev->cameraid]->setParameters(camParams);

            camParams.set(android::CameraParameters::KEY_FOCUS_MODE, prevFocusMode);
            rv_fm = gCameraHals[dev->cameraid]->setParameters(camParams);

            dev->mFixFocus = 0;
        }
    }

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

void camera_stop_preview(struct camera_device * device)
{
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return;

    dev = (priv_camera_device_t*) device;

    gCameraHals[dev->cameraid]->stopPreview();
    ALOGI("%s---", __FUNCTION__);
}

int camera_preview_enabled(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->previewEnabled();

    ALOGI("%s--- rv %d", __FUNCTION__,rv);

    return rv;
}

int camera_store_meta_data_in_buffers(struct camera_device * device, int enable)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    //  TODO: meta data buffer not current supported
    //rv = gCameraHals[dev->cameraid]->storeMetaDataInBuffers(enable);
    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
    //return enable ? android::INVALID_OPERATION: android::OK;
}

int camera_start_recording(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->startRecording();

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

void camera_stop_recording(struct camera_device * device)
{
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return;

    dev = (priv_camera_device_t*) device;

    gCameraHals[dev->cameraid]->stopRecording();

    dev->mFixFocus = 1;
    //QiSS ME force start preview when recording stop
    //gCameraHals[dev->cameraid]->startPreview();

    ALOGI("%s---", __FUNCTION__);
}

int camera_recording_enabled(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->recordingEnabled();

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

void camera_release_recording_frame(struct camera_device * device,
                                    const void *opaque)
{
    priv_camera_device_t* dev = NULL;
    //camera_memory_t *data = (camera_memory_t *)(&opaque);


    //ALOGI("%s+++: device %p,opaque %p,data %p", __FUNCTION__, device,opaque,data);

    if(!device)
        return;

    dev = (priv_camera_device_t*) device;
    /*
     if ( NULL != data ) {
     data->release(data);
     }
     */
    //gCameraHals[dev->cameraid]->releaseRecordingFrame(opaque);

    ALOGI("%s---", __FUNCTION__);
}

int camera_auto_focus(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->autoFocus();

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

int camera_cancel_auto_focus(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->cancelAutoFocus();

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

int camera_take_picture(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    gCameraHals[dev->cameraid]->enableMsgType(CAMERA_MSG_SHUTTER |
        CAMERA_MSG_POSTVIEW_FRAME |
        CAMERA_MSG_RAW_IMAGE |
        CAMERA_MSG_COMPRESSED_IMAGE);

    rv = gCameraHals[dev->cameraid]->takePicture();

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

int camera_cancel_picture(struct camera_device * device)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->cancelPicture();

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

int camera_set_parameters(struct camera_device * device, const char *params)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;
    CameraParameters camParams;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    String8 params_str8(params);
    camParams.unflatten(params_str8);

#ifdef DUMP_PARAMS
    camParams.dump();
#endif

    rv = gCameraHals[dev->cameraid]->setParameters(camParams);

#ifdef DUMP_PARAMS
    camParams.dump();
#endif

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

char* camera_get_parameters(struct camera_device * device)
{
    char* params = NULL;
    priv_camera_device_t* dev = NULL;
    String8 params_str8;
    CameraParameters camParams;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return NULL;

    dev = (priv_camera_device_t*) device;

    camParams = gCameraHals[dev->cameraid]->getParameters();

#ifdef DUMP_PARAMS
    camParams.dump();
#endif

    CameraHAL_FixupParams(camParams, dev);

    params_str8 = camParams.flatten();
    params = (char*) malloc(sizeof(char) * (params_str8.length()+1));
    strcpy(params, params_str8.string());

#ifdef DUMP_PARAMS
    camParams.dump();
#endif

    ALOGI("%s---", __FUNCTION__);
    return params;
}

static void camera_put_parameters(struct camera_device *device, char *parms)
{
    ALOGI("%s+++", __FUNCTION__);
    free(parms);
    ALOGI("%s---", __FUNCTION__);
}

int camera_send_command(struct camera_device * device,
                        int32_t cmd, int32_t arg1, int32_t arg2)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s: cmd %i, arg1: %i arg2: %i, device %p", __FUNCTION__,
        cmd, arg1, arg2, device);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    rv = gCameraHals[dev->cameraid]->sendCommand(cmd, arg1, arg2);

    ALOGI("%s--- rv %d", __FUNCTION__,rv);
    return rv;
}

void camera_release(struct camera_device * device)
{
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    if(!device)
        return;

    dev = (priv_camera_device_t*) device;

    gCameraHals[dev->cameraid]->release();
    ALOGI("%s---", __FUNCTION__);
}

int camera_dump(struct camera_device * device, int fd)
{
    int rv = -EINVAL;
    priv_camera_device_t* dev = NULL;
    ALOGI("%s", __FUNCTION__);

    if(!device)
        return rv;

    dev = (priv_camera_device_t*) device;

    // rv = gCameraHals[dev->cameraid]->dump(fd);
    return rv;
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    qCamera->enableMsgType(msg_type);
}

void camera_disable_msg_type(struct camera_device * device, int32_t msg_type) {
    /* The camera app disables the shutter too early which leads to crash.
     * Leaving it enabled. */
    if (msg_type == CAMERA_MSG_SHUTTER) return;

    qCamera->disableMsgType(msg_type);
}

int camera_msg_type_enabled(struct camera_device * device, int32_t msg_type) {
    return qCamera->msgTypeEnabled(msg_type);
}

int camera_start_preview(struct camera_device * device) {
    if (!qCamera->msgTypeEnabled(CAMERA_MSG_PREVIEW_FRAME)) {
        qCamera->enableMsgType(CAMERA_MSG_PREVIEW_FRAME);
    }
    return qCamera->startPreview();
}

void camera_stop_preview(struct camera_device * device) {
    if (qCamera->msgTypeEnabled(CAMERA_MSG_PREVIEW_FRAME)) {
        qCamera->disableMsgType(CAMERA_MSG_PREVIEW_FRAME);
    }
    qCamera->stopPreview();
}

int camera_preview_enabled(struct camera_device * device) {
    return qCamera->previewEnabled();
}

int camera_store_meta_data_in_buffers(struct camera_device * device, int enable) {
    return 0;
}

int camera_start_recording(struct camera_device * device) {
    return qCamera->startRecording();
}

void camera_stop_recording(struct camera_device * device) {
    qCamera->stopRecording();
}

int camera_recording_enabled(struct camera_device * device) {
    return qCamera->recordingEnabled();
}

void camera_release_recording_frame(struct camera_device * device, const void *opaque) {
    //qCamera->releaseRecordingFrame(opaque);
}

int camera_auto_focus(struct camera_device * device) {
    return qCamera->autoFocus();
}

int camera_cancel_auto_focus(struct camera_device * device) {
    return qCamera->cancelAutoFocus();
}

int camera_take_picture(struct camera_device * device) {
    return qCamera->takePicture();
}

int camera_cancel_picture(struct camera_device * device) {
    return qCamera->cancelPicture();
}

int camera_set_parameters(struct camera_device * device, const char *params) {
    CameraParameters camParams;

    String8 params_str8(params);
    camParams.unflatten(params_str8);

    return qCamera->setParameters(camParams);
}

char* camera_get_parameters(struct camera_device * device) {
    CameraParameters camParams = qCamera->getParameters();
    CameraHAL_FixupParams(camParams);

    String8 params_str8 = camParams.flatten();
    char* params = (char*) malloc(sizeof(char) * (params_str8.length()+1));
    strcpy(params, params_str8.string());

    return params;
}

static void camera_put_parameters(struct camera_device *device, char *parms) {
    free(parms);
}

int camera_send_command(struct camera_device * device, int32_t cmd, int32_t arg1, int32_t arg2) {
    return qCamera->sendCommand(cmd, arg1, arg2);
}

void camera_release(struct camera_device * device) {
    qCamera->release();
}

int camera_dump(struct camera_device * device, int fd) {
    android::Vector<android::String16> args;
    return qCamera->dump(fd, args);
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
}

extern "C" void heaptracker_free_leaked_memory(void);

<<<<<<< HEAD
<<<<<<< HEAD
int camera_device_close(hw_device_t* device)
{
    int ret = 0;
    priv_camera_device_t* dev = NULL;

    ALOGI("%s+++: device %p", __FUNCTION__, device);

    //android::Mutex::Autolock lock(gCameraDeviceLock);

    if (!device) {
        ret = -EINVAL;
        goto done;
    }

    dev = (priv_camera_device_t*) device;

    if (dev) {
        gCameraHals[dev->cameraid].clear();
        gCameraHals[dev->cameraid] = NULL;
        gCamerasOpen--;
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
int camera_device_close(hw_device_t* device) {
    int rc = -EINVAL;
    priv_camera_device_t* dev = (priv_camera_device_t*) device;
    if (dev) {
        qCamera = NULL;
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

        if (dev->base.ops) {
            free(dev->base.ops);
        }
<<<<<<< HEAD
<<<<<<< HEAD
        if (dev->overlay != NULL) {
            dev->overlay.clear();
            dev->overlay = NULL;
        }
        free(dev);
    }
done:
#ifdef HEAPTRACKER
    heaptracker_free_leaked_memory();
#endif
    ALOGI("%s--- ret %d", __FUNCTION__,ret);

    return ret;
}

/*******************************************************************
 * implementation of camera_module functions
 *******************************************************************/

/* Ugly stuff - ignore SIGFPE */
void sigfpe_handle(int s)
{
    ALOGV("Received SIGFPE. Ignoring\n");
}

/* open device handle to one of the cameras
 *
 * assume camera service will keep singleton of each camera
 * so this function will always only be called once per camera instance
 */

int camera_device_open(const hw_module_t* module, const char* name,
                       hw_device_t** device)
{
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
        free(dev);
        rc = 0;
    }

    return rc;
}

void sighandle(int s) {
    ALOGW("Segfault handled, ignoring");
}

int camera_device_open(const hw_module_t* module, const char* name, hw_device_t** device) {
    ALOGI("CameraHAL v0.3.2");
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
    int rv = 0;
    int cameraid;
    int num_cameras = 0;
    priv_camera_device_t* priv_camera_device = NULL;
    camera_device_ops_t* camera_ops = NULL;
<<<<<<< HEAD
<<<<<<< HEAD
    sp<CameraHardwareInterface> camera = NULL;

    //android::Mutex::Autolock lock(gCameraDeviceLock);

    /* add SIGFPE handler */
    signal(SIGFPE, sigfpe_handle);

    ALOGI("camera_device open+++");
=======
    signal(SIGFPE,(*sighandle));
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
    signal(SIGFPE,(*sighandle));
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

    if (name != NULL) {
        cameraid = atoi(name);

<<<<<<< HEAD
<<<<<<< HEAD
        num_cameras = camera_get_number_of_cameras();

        if(cameraid > num_cameras)
        {
            ALOGE("camera service provided cameraid out of bounds, "
                 "cameraid = %d, num supported = %d",
                 cameraid, num_cameras);
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
        num_cameras = HAL_getNumberOfCameras();

        if(cameraid > num_cameras) {
            ALOGE("camera service provided cameraid out of bounds, cameraid = %d, num supported = %d", cameraid, num_cameras);
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
            rv = -EINVAL;
            goto fail;
        }

<<<<<<< HEAD
<<<<<<< HEAD
        if(gCamerasOpen >= MAX_CAMERAS_SUPPORTED)
        {
            ALOGE("maximum number of cameras already open");
            rv = -ENOMEM;
            goto fail;
        }

        priv_camera_device = (priv_camera_device_t*)malloc(sizeof(*priv_camera_device));
        if(!priv_camera_device)
        {
=======
        priv_camera_device = (priv_camera_device_t*)malloc(sizeof(*priv_camera_device));
        if(!priv_camera_device) {
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
        priv_camera_device = (priv_camera_device_t*)malloc(sizeof(*priv_camera_device));
        if(!priv_camera_device) {
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
            ALOGE("camera_device allocation fail");
            rv = -ENOMEM;
            goto fail;
        }

        camera_ops = (camera_device_ops_t*)malloc(sizeof(*camera_ops));
<<<<<<< HEAD
<<<<<<< HEAD
        if(!camera_ops)
        {
=======
        if(!camera_ops) {
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
        if(!camera_ops) {
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
            ALOGE("camera_ops allocation fail");
            rv = -ENOMEM;
            goto fail;
        }

        memset(priv_camera_device, 0, sizeof(*priv_camera_device));
        memset(camera_ops, 0, sizeof(*camera_ops));

<<<<<<< HEAD
<<<<<<< HEAD
        priv_camera_device->base.common.tag = HARDWARE_DEVICE_TAG;
        priv_camera_device->base.common.version = 0;
        priv_camera_device->base.common.module = (hw_module_t *)(module);
        priv_camera_device->base.common.close = camera_device_close;
        priv_camera_device->base.ops = camera_ops;

        camera_ops->set_preview_window = camera_set_preview_window;
        camera_ops->set_callbacks = camera_set_callbacks;
        camera_ops->enable_msg_type = camera_enable_msg_type;
        camera_ops->disable_msg_type = camera_disable_msg_type;
        camera_ops->msg_type_enabled = camera_msg_type_enabled;
        camera_ops->start_preview = camera_start_preview;
        camera_ops->stop_preview = camera_stop_preview;
        camera_ops->preview_enabled = camera_preview_enabled;
        camera_ops->store_meta_data_in_buffers = camera_store_meta_data_in_buffers;
        camera_ops->start_recording = camera_start_recording;
        camera_ops->stop_recording = camera_stop_recording;
        camera_ops->recording_enabled = camera_recording_enabled;
        camera_ops->release_recording_frame = camera_release_recording_frame;
        camera_ops->auto_focus = camera_auto_focus;
        camera_ops->cancel_auto_focus = camera_cancel_auto_focus;
        camera_ops->take_picture = camera_take_picture;
        camera_ops->cancel_picture = camera_cancel_picture;
        camera_ops->set_parameters = camera_set_parameters;
        camera_ops->get_parameters = camera_get_parameters;
        camera_ops->put_parameters = camera_put_parameters;
        camera_ops->send_command = camera_send_command;
        camera_ops->release = camera_release;
        camera_ops->dump = camera_dump;

        *device = &priv_camera_device->base.common;

        // -------- specific stuff --------

        priv_camera_device->cameraid = cameraid;

        camera = SEC_openCameraHardware(cameraid);
        if(camera == NULL)
        {
=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
        priv_camera_device->base.common.tag     = HARDWARE_DEVICE_TAG;
        priv_camera_device->base.common.version = 0;
        priv_camera_device->base.common.module  = (hw_module_t *)(module);
        priv_camera_device->base.common.close   = camera_device_close;
        priv_camera_device->base.ops            = camera_ops;

        camera_ops->set_preview_window         = camera_set_preview_window;
        camera_ops->set_callbacks              = camera_set_callbacks;
        camera_ops->enable_msg_type            = camera_enable_msg_type;
        camera_ops->disable_msg_type           = camera_disable_msg_type;
        camera_ops->msg_type_enabled           = camera_msg_type_enabled;
        camera_ops->start_preview              = camera_start_preview;
        camera_ops->stop_preview               = camera_stop_preview;
        camera_ops->preview_enabled            = camera_preview_enabled;
        camera_ops->store_meta_data_in_buffers = camera_store_meta_data_in_buffers;
        camera_ops->start_recording            = camera_start_recording;
        camera_ops->stop_recording             = camera_stop_recording;
        camera_ops->recording_enabled          = camera_recording_enabled;
        camera_ops->release_recording_frame    = camera_release_recording_frame;
        camera_ops->auto_focus                 = camera_auto_focus;
        camera_ops->cancel_auto_focus          = camera_cancel_auto_focus;
        camera_ops->take_picture               = camera_take_picture;
        camera_ops->cancel_picture             = camera_cancel_picture;
        camera_ops->set_parameters             = camera_set_parameters;
        camera_ops->get_parameters             = camera_get_parameters;
        camera_ops->put_parameters             = camera_put_parameters;
        camera_ops->send_command               = camera_send_command;
        camera_ops->release                    = camera_release;
        camera_ops->dump                       = camera_dump;

        *device = &priv_camera_device->base.common;

        priv_camera_device->cameraid = cameraid;

        sp<CameraHardwareInterface> camera = HAL_openCameraHardware(cameraid);

        if(camera == NULL) {
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
            ALOGE("Couldn't create instance of CameraHal class");
            rv = -ENOMEM;
            goto fail;
        }

<<<<<<< HEAD
<<<<<<< HEAD
        gCameraHals[cameraid] = camera;
        gCamerasOpen++;
    }
    ALOGI("%s---ok rv %d", __FUNCTION__,rv);
=======
        qCamera = camera;
    }
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
        qCamera = camera;
    }
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

    return rv;

fail:
    if(priv_camera_device) {
        free(priv_camera_device);
        priv_camera_device = NULL;
    }
    if(camera_ops) {
        free(camera_ops);
        camera_ops = NULL;
    }
    *device = NULL;
<<<<<<< HEAD
<<<<<<< HEAD
    ALOGI("%s--- fail rv %d", __FUNCTION__,rv);
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

    return rv;
}

<<<<<<< HEAD
int camera_get_number_of_cameras(void)
{
    int num_cameras = SEC_getNumberOfCameras();
    ALOGI("%s: number:%i", __FUNCTION__, num_cameras);

    return num_cameras;
}

int camera_get_camera_info(int camera_id, struct camera_info *info)
{
    int rv = 0;

    CameraInfo cameraInfo;

    android::SEC_getCameraInfo(camera_id, &cameraInfo);

    info->facing = cameraInfo.facing;
    //info->orientation = cameraInfo.orientation;
    if(info->facing == 1) {
        info->orientation = 270;
    } else {
        info->orientation = 90;
    }

    ALOGI("%s: id:%i faceing:%i orientation: %i", __FUNCTION__,camera_id, info->facing, info->orientation);
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

    return rv;
}

<<<<<<< HEAD
extern "C" {
#include "exif/jhead.h"
}

static inline void rotateJPEG(void* src,size_t size) {
    ReadMode_t ReadMode = READ_METADATA;

    ALOGE("ResetJpgfile");
    ResetJpgfile();

    // Start with an empty image information structure.
    memset(&CameraHALImageInfo, 0, sizeof(CameraHALImageInfo));

    ALOGE("ReadJpegFile");
    ReadJpegSectionsFromBuffer((unsigned char*)src, size, ReadMode);

}

=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
int camera_get_number_of_cameras(void) {
    return HAL_getNumberOfCameras();
}

int camera_get_camera_info(int camera_id, struct camera_info *info) {
    CameraInfo cameraInfo;

    HAL_getCameraInfo(camera_id, &cameraInfo);

    info->facing = cameraInfo.facing;
    info->orientation = info->facing == 1 ? 270 : 90;

    return 0;
}
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee