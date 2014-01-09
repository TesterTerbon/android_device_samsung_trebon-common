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

## Specify phone tech before including full_phone
$(call inherit-product, vendor/cm/config/gsm.mk)

## Inherit common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

## Inherit device files
$(call inherit-product, device/samsung/trebon/full_trebon.mk)

PRODUCT_RELEASE_NAME := trebon

CM_BUILDTYPE := dev_tester_android_readone
CM_NUMERICAL_VERSION := 0.1


## Setup device configuration
PRODUCT_NAME := cm_trebon
PRODUCT_BRAND := samsung
PRODUCT_MANUFACTURER := samsung
PRODUCT_MODEL := GT-S7500
PRODUCT_RELEASE_NAME := GT-S7500
PRODUCT_DEVICE := trebon

## Bootanimation
TARGET_SCREEN_HEIGHT := 480
TARGET_SCREEN_WIDTH := 320

PRODUCT_BUILD_PROP_OVERRIDES += BUILD_FINGERPRINT=samsung/GT-S7500/GT-S7500:2.3.6/GINGERBREAD/XXKQN:user/release-keys PRIVATE_BUILD_DESC="GT-S7500-user 2.3.6 GINGERBREAD XXKQN release-keys"

