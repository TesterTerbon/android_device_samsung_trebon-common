# Copyright (C) 2013 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# 
#
#
# This file sets variables that control the way modules are built
# thorughout the system. It should not be used to conditionally
# disable makefiles (the proper mechanism to control what gets
# included in a build is to use PRODUCT_PACKAGES in a product
# definition file).
#

# WARNING: This line must come *before* including the proprietary
# variant, so that it gets overwritten by the parent (which goes
# against the traditional rules of inheritance).

# Vendor stuff
include vendor/samsung/trebon/BoardConfigVendor.mk


# create the folder /usr to prevent the build from failing
$(shell mkdir -p $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/)

## Platform
TARGET_BOOTLOADER_BOARD_NAME := trebon
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_ARCH_LOWMEM := true
TARGET_BOARD_PLATFORM := msm7x27a
TARGET_BOARD_PLATFORM_GPU := qcom-adreno200
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_VARIANT := cortex-a5
TARGET_SPECIFIC_HEADER_PATH := device/samsung/trebon/include
TARGET_RUNNING_WITHOUT_SYNC_FRAMEWORK := true
ARCH_ARM_HAVE_TLS_REGISTER := true

TARGET_GLOBAL_CFLAGS += -mtune=cortex-a5 -mfpu=neon -mfloat-abi=softfp
TARGET_GLOBAL_CPPFLAGS += -mtune=cortex-a5 -mfpu=neon -mfloat-abi=softfp

## Allow compatibility with older recoveries
SKIP_SET_METADATA := true

## Video
TARGET_QCOM_MEDIA_VARIANT := caf
TARGET_ENABLE_QC_AV_ENHANCEMENTS := true

## Audio
TARGET_QCOM_AUDIO_VARIANT := caf
BOARD_USES_LEGACY_ALSA_AUDIO := true
COMMON_GLOBAL_CFLAGS += -DQCOM_DIRECTTRACK -DNO_TUNNELED_SOURCE
COMMON_GLOBAL_CFLAGS += -DQCOM_ENHANCED_AUDIO
BOARD_HAVE_SAMSUNG_AUDIO := true
BOARD_USES_QCOM_AUDIO_RESETALL := true
BOARD_USES_QCOM_AUDIO_VOIPMUTE := true

# qcom
COMMON_GLOBAL_CFLAGS += -DQCOM_BSP
TARGET_USE_QCOM_BIONIC_OPTIMIZATION := true

# Use retire fence from MDP driver
TARGET_DISPLAY_USE_RETIRE_FENCE := true

# Power HAL
TARGET_PROVIDES_POWERHAL := true

# Lights HAL
TARGET_PROVIDES_LIBLIGHT := true

# healthd HAL
BOARD_HAL_STATIC_LIBRARIES := libhealthd.qcom


## FM Radio
BOARD_HAVE_QCOM_FM := true
COMMON_GLOBAL_CFLAGS += -DQCOM_FM_ENABLED

## Camera
#TARGET_DISABLE_ARM_PIE := true
COMMON_GLOBAL_CFLAGS += -DBINDER_COMPAT -DNEEDS_VECTORIMPL_SYMBOLS -DSAMSUNG_CAMERA_LEGACY
USE_CAMERA_STUB := true
USE_DEVICE_SPECIFIC_CAMERA := true
BOARD_USES_QCOM_LEGACY_CAM_PARAMS := true
BOARD_USES_LEGACY_OVERLAY := true
BOARD_QCOM_VOIP_ENABLED := true
COMMON_GLOBAL_CFLAGS += -DQCOM_DIRECTTRACK -DNO_TUNNELED_SOURCE

## EGL, graphics
COMMON_GLOBAL_CFLAGS += -DNEW_ION_API
COMMON_GLOBAL_CFLAGS += -DFORCE_SCREENSHOT_CPU_PATH
USE_OPENGL_RENDERER := true
TARGET_QCOM_DISPLAY_VARIANT := caf
TARGET_DOESNT_USE_FENCE_SYNC := true
BOARD_ALLOW_EGL_HIBERNATION := true
BOARD_ADRENO_DECIDE_TEXTURE_TARGET := true
BOARD_EGL_CFG := device/samsung/trebon/prebuilt/lib/egl/egl.cfg
TARGET_NO_HW_VSYNC := false
TARGET_USES_C2D_COMPOSITION := true

## Qcom hardwae
BOARD_USES_QCOM_HARDWARE := true
COMMON_GLOBAL_CFLAGS += -DQCOM_HARDWARE

## ION
TARGET_USES_ION := true

## Qualcomm BSP
TARGET_USES_QCOM_BSP := true
COMMON_GLOBAL_CFLAGS += -DQCOM_BSP

## GPS
BOARD_USES_QCOM_LIBRPC := true
BOARD_USES_QCOM_GPS := true
BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE := msm7x27a
BOARD_VENDOR_QCOM_GPS_LOC_API_AMSS_VERSION := 50000

## Webkit
ENABLE_WEBGL := true
TARGET_FORCE_CPU_UPLOAD := true

# Sensors
BOARD_USE_LEGACY_SENSORS_FUSION := false

## Bluetooth
BOARD_HAVE_BLUETOOTH := device/samsung/trebon/bluetooth

## Wi-Fi
BOARD_WLAN_DEVICE := ath6kl
WPA_SUPPLICANT_VERSION := VER_0_8_X
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_ath6kl
BOARD_HOSTAPD_DRIVER := NL80211
BOARD_HOSTAPD_PRIVATE_LIB := lib_driver_cmd_ath6kl
WIFI_EXT_MODULE_NAME := "cfg80211"
WIFI_EXT_MODULE_PATH := "/system/lib/modules/cfg80211.ko"
WIFI_DRIVER_MODULE_AP_ARG := "suspend_mode=3 wow_mode=2 ath6kl_p2p=1 recovery_enable=1"
WIFI_DRIVER_MODULE_NAME := "ath6kl_sdio"
WIFI_DRIVER_MODULE_PATH := "/system/lib/modules/ath6kl_sdio.ko"
WIFI_DRIVER_MODULE_ARG := "suspend_mode=3 wow_mode=2 ath6kl_p2p=1 recovery_enable=1"

## RIL
BOARD_USES_LEGACY_RIL := true
BOARD_RIL_CLASS := ../../../device/samsung/trebon/ril/

## Vold
BOARD_VOLD_EMMC_SHARES_DEV_MAJOR := true
BOARD_VOLD_MAX_PARTITIONS := 24

## UMS
TARGET_USE_CUSTOM_LUN_FILE_PATH := /sys/devices/platform/msm_hsusb/gadget/lun%d/file
BOARD_UMS_LUNFILE := "/sys/devices/platform/msm_hsusb/gadget/lun%d/file"

## Samsung has weird framebuffer
TARGET_NO_INITLOGO := true

## Bootanimation
TARGET_BOOTANIMATION_PRELOAD := true
TARGET_BOOTANIMATION_TEXTURE_CACHE := true
TARGET_BOOTANIMATION_USE_RGB565 := true

## Charging mode
BOARD_LPM_BOOT_ARGUMENT_NAME := androidboot.boot_pause
BOARD_LPM_BOOT_ARGUMENT_VALUE := batt
BOARD_CHARGER_RES := device/samsung/trebon/res/charger

## Use device specific modules
TARGET_PROVIDES_LIBLIGHTS := true
TARGET_PROVIDES_LIBAUDIO := true

## Recovery
DEVICE_RESOLUTION := 320x480
RECOVERY_GRAPHICS_USE_LINELENGTH := true
TW_BRIGHTNESS_PATH := "/sys/class/leds/lcd-backlight/brightness"
TW_DEFAULT_EXTERNAL_STORAGE := false
TW_EXTERNAL_STORAGE_PATH := "/external_sd"
TW_EXTERNAL_STORAGE_MOUNT_POINT := "external_sd"
TW_INTERNAL_STORAGE_PATH := "/sdcard"
TW_INTERNAL_STORAGE_MOUNT_POINT := "sdcard"
TARGET_RECOVERY_INITRC := device/samsung/trebon/recovery/init.recovery.rc
TARGET_RECOVERY_FSTAB := device/samsung/trebon/rootdir/fstab.qcom
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../device/samsung/trebon/recovery/recovery_keys.c
TARGET_RECOVERY_PIXEL_FORMAT := RGBX_8888
TARGET_USERIMAGES_USE_EXT4 := true
BOARD_HAS_SDCARD_INTERNAL := true
BOARD_HAS_DOWNLOAD_MODE := true
BOARD_USES_MMCUTILS := true
BOARD_HAS_NO_MISC_PARTITION := true
BOARD_FLASH_BLOCK_SIZE := 131072

## Filesystem
BOARD_DATA_DEVICE := /dev/block/mmcblk0p18
BOARD_DATA_FILESYSTEM := ext4
BOARD_DATA_FILESYSTEM_OPTIONS := rw
BOARD_SYSTEM_DEVICE := /dev/block/mmcblk0p16
BOARD_SYSTEM_FILESYSTEM := ext4
BOARD_SYSTEM_FILESYSTEM_OPTIONS := rw
BOARD_CACHE_DEVICE := /dev/block/mmcblk0p17
BOARD_CACHE_FILESYSTEM := ext4
BOARD_CACHE_FILESYSTEM_OPTIONS := rw

## Partition sizes
BOARD_BOOTIMAGE_PARTITION_SIZE := 12582912
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 12582912
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 524288000
BOARD_USERDATAIMAGE_PARTITION_SIZE := 979369984

# SELinux
BOARD_SEPOLICY_DIRS += \
    device/samsung/trebon/sepolicy

BOARD_SEPOLICY_UNION += \
    file_contexts \
    property_contexts \
    bridge.te \
    camera.te \
    device.te \
    dhcp.te \
    domain.te \
    drmserver.te \
    file.te \
    geomagneticd.te \
    healthd.te \
    init.te \
    mac_update.te \
    mediaserver.te \
    rild.te \
    rmt.te \
    surfaceflinger.te \
    system.te \
    tee.te \
    ueventd.te \
    wpa_supplicant.te

# Hardware tunables
BOARD_HARDWARE_CLASS := device/samsung/trebon/cmhw/

## Kernel bootloader etc.
TARGET_NO_BOOTLOADER := true
TARGET_NO_RADIOIMAGE := true
BOARD_KERNEL_BASE := 0x00200000
BOARD_KERNEL_PAGESIZE := 4096
TARGET_KERNEL_SOURCE := kernel/samsung/msm7x27a
TARGET_KERNEL_CONFIG := trebon_defconfig

## Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/samsung/trebon/bluetooth
BOARD_BLUEDROID_VENDOR_CONF := device/samsung/trebon/bluetooth/vnd_trebon.txt
## OTA assert
TARGET_OTA_ASSERT_DEVICE := trebon,GT-S7500
