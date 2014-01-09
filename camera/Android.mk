<<<<<<< HEAD
<<<<<<< HEAD
$(shell mkdir -p $(OUT)/obj/SHARED_LIBRARIES/libcamera_intermediates/)
$(shell touch $(OUT)/obj/SHARED_LIBRARIES/libcamera_intermediates/export_includes)
$(shell mkdir -p $(OUT)/obj/SHARED_LIBRARIES/libseccameraadaptor_intermediates/)
$(shell touch $(OUT)/obj/SHARED_LIBRARIES/libseccameraadaptor_intermediates/export_includes)
#$(shell mkdir -p $(OUT)/obj/SHARED_LIBRARIES/camera.msm7x30_intermediates/)
#$(shell touch $(OUT)/obj/SHARED_LIBRARIES/camera.msm7x30_intermediates/export_includes)

=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

<<<<<<< HEAD
<<<<<<< HEAD
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE := camera.$(TARGET_BOARD_PLATFORM)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := cameraHAL.cpp \
	exif/exif.c \
	exif/gpsinfo.c \
	exif/iptc.c \
	exif/jhead.c \
	exif/jpgfile.c \
	exif/makernote.c
                

LOCAL_C_INCLUDES := frameworks/av/include
LOCAL_C_INCLUDES += frameworks/native/include

ifeq ($(TARGET_QCOM_DISPLAY_VARIANT),caf)
LOCAL_C_INCLUDES += hardware/qcom/display-caf/libgralloc
else
LOCAL_C_INCLUDES += hardware/qcom/display-legacy/libgralloc
endif

LOCAL_SHARED_LIBRARIES := liblog libutils libcutils libbinder
LOCAL_SHARED_LIBRARIES += libui libhardware libcamera_client
LOCAL_SHARED_LIBRARIES += libseccameraadaptor
LOCAL_PRELINK_MODULE := false

<<<<<<< HEAD

# hack for prebuilt
$(shell mkdir -p $(OUT)/obj/SHARED_LIBRARIES/libcamera_intermediates/)
$(shell touch $(OUT)/obj/SHARED_LIBRARIES/libcamera_intermediates/export_includes)
$(shell mkdir -p $(OUT)/obj/SHARED_LIBRARIES/libseccameraadaptor_intermediates/)
$(shell touch $(OUT)/obj/SHARED_LIBRARIES/libseccameraadaptor_intermediates/export_includes)
=======
LOCAL_LDFLAGS          += -Lvendor/samsung/trebon/proprietary/lib -lcamera
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee

include $(BUILD_SHARED_LIBRARY)


=======
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
ifeq ($(TARGET_BOOTLOADER_BOARD_NAME),trebon)
  LOCAL_CFLAGS += -DENABLE_FLASH_AND_AUTOFOCUS
endif

LOCAL_CFLAGS           += -O3
LOCAL_MODULE_PATH      := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE           := camera.$(TARGET_BOARD_PLATFORM)

LOCAL_MODULE_TAGS      := optional

LOCAL_SRC_FILES        := cameraHAL.cpp
LOCAL_C_INCLUDES       := $(TOP)/frameworks/base/include
LOCAL_C_INCLUDES       += hardware/qcom/display-legacy/libgralloc

LOCAL_SHARED_LIBRARIES := liblog libutils libcutils
LOCAL_SHARED_LIBRARIES += libui libhardware libcamera_client

LOCAL_LDFLAGS          += -Lvendor/samsung/trebon/proprietary/lib -lcamera

include $(BUILD_SHARED_LIBRARY)
<<<<<<< HEAD
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
=======
>>>>>>> 43f6096a538d97b412d68dbb18e1b2fd3bdbdcee
