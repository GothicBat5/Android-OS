
cvd_host_packages := $(HOST_OUT)/cvd-host_package
ifeq ($(HOST_CROSS_OS)_$(HOST_CROSS_ARCH),linux_bionic_arm64)
  cvd_host_packages += $(OUT_DIR)/host/$(HOST_CROSS_OS)-$(HOST_CROSS_ARCH)/cvd-host_package
  
endif
cvd_host_dir_stamps := $(addsuffix .stamp,$(cvd_host_packages))
cvd_host_tarballs := $(addsuffix .tar.gz,$(cvd_host_packages))
.PHONY: hosttar

hosttar: $(cvd_host_tarballs)
# Build this by default when a developer types make.
# Skip the tarballs by default as it is time consuming.

droidcore: $(cvd_host_dir_stamps)
# Dist
# Note that only the last package is dist'ed. It would be from x86 in case of cf_x86_phone,
# and from arm64 in case of cf_arm64_phone.

$(call dist-for-goals, dist_files,$(word $(words $(cvd_host_tarballs)), $(cvd_host_tarballs)))

cvd_host_dir_stamps :=
cvd_host_packages :=
cvd_host_tarballs :=


bin_path := $(HOST_OUT_EXECUTABLES)

ifeq ($(HOST_CROSS_OS)_$(HOST_CROSS_ARCH),linux_bionic_arm64)
  bin_path := $(OUT_DIR)/host/$(HOST_CROSS_OS)-$(HOST_CROSS_ARCH)/bin
  
endif
cvd_bin := $(bin_path)/cvd
fetcher_bin := $(bin_path)/fetch_cvd
.PHONY: host_fetcher
host_fetcher: $(fetcher_bin)

# Build this by default when a developer types make
droidcore: $(cvd_bin) $(fetcher_bin)

# Build and store them on the build server.

$(call dist-for-goals, dist_files, $(cvd_bin))
$(call dist-for-goals, dist_files, $(fetcher_bin))

bin_path :=
cvd_bin :=
fetcher_bin :=

$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,.idc,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,default-permissions.xml,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,libnfc-nci.conf,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,fstab.postinstall,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,ueventd.rc,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,wpa_supplicant.conf,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,hals.conf,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,device_state_configuration.xml,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,task_profiles.json,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,p2p_supplicant.conf,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,wpa_supplicant.conf,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,wpa_supplicant_overlay.conf,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,wpa_supplicant.rc,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,init.cutf_cvm.rc,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,bt_vhci_forwarder.rc,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,fstab.cf.f2fs.hctr2,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,fstab.cf.f2fs.cts,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,fstab.cf.ext4.hctr2,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,fstab.cf.ext4.cts,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,init.rc,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish,audio_policy.conf,SPDX-license-identifier-Apache-2.0,notice,build/soong/licenses/LICENSE,))
$(eval $(call declare-copy-files-license-metadata,device/google/cuttlefish/shared/config,pci.ids,SPDX-license-identifier-BSD-3-Clause,notice,device/google/cuttlefish/shared/config/LICENSE_BSD,))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,privapp-permissions-cuttlefish.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,media_profiles_V1_0.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,media_codecs_performance.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,cuttlefish_excluded_hardware.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,media_codecs.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,media_codecs_google_video.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,car_audio_configuration.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,audio_policy_configuration.xml))
$(eval $(call declare-1p-copy-files,device/google/cuttlefish,preinstalled-packages-product-car-cuttlefish.xml))
$(eval $(call declare-1p-copy-files,hardware/google/camera/devices,.json))
ifneq ($(filter vsoc_arm vsoc_arm64 vsoc_riscv64 vsoc_x86 vsoc_x86_64, $(TARGET_BOARD_PLATFORM)),)
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/fetcher.mk
include $(CLEAR_VARS)
include $(LOCAL_PATH)/host_package.mk

endif
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))


PRODUCT_MAKEFILES := \
	aosp_cf_arm_minidroid:$(LOCAL_DIR)/vsoc_arm_minidroid/aosp_cf.mk \
	aosp_cf_arm64_auto:$(LOCAL_DIR)/vsoc_arm64_only/auto/aosp_cf.mk \
	aosp_cf_arm64_phone:$(LOCAL_DIR)/vsoc_arm64/phone/aosp_cf.mk \
	aosp_cf_arm64_phone_fullmte:$(LOCAL_DIR)/vsoc_arm64_only/phone/aosp_cf_fullmte.mk \
	aosp_cf_arm64_phone_hwasan:$(LOCAL_DIR)/vsoc_arm64/phone/aosp_cf_hwasan.mk \
	aosp_cf_arm64_only_phone:$(LOCAL_DIR)/vsoc_arm64_only/phone/aosp_cf.mk \
	aosp_cf_arm64_only_phone_hwasan:$(LOCAL_DIR)/vsoc_arm64_only/phone/aosp_cf_hwasan.mk \
	aosp_cf_arm64_minidroid:$(LOCAL_DIR)/vsoc_arm64_minidroid/aosp_cf.mk \
	aosp_cf_arm64_slim:$(LOCAL_DIR)/vsoc_arm64_only/slim/aosp_cf.mk \
	aosp_cf_riscv64_minidroid:$(LOCAL_DIR)/vsoc_riscv64_minidroid/aosp_cf.mk \
	aosp_cf_riscv64_slim:$(LOCAL_DIR)/vsoc_riscv64/slim/aosp_cf.mk \
	aosp_cf_riscv64_wear:$(LOCAL_DIR)/vsoc_riscv64/wear/aosp_cf.mk \
	aosp_cf_riscv64_phone:$(LOCAL_DIR)/vsoc_riscv64/phone/aosp_cf.mk \
	aosp_cf_x86_64_auto:$(LOCAL_DIR)/vsoc_x86_64_only/auto/aosp_cf.mk \
	aosp_cf_x86_64_auto_md:$(LOCAL_DIR)/vsoc_x86_64_only/auto_md/aosp_cf.mk \
	aosp_cf_x86_64_auto_mdnd:$(LOCAL_DIR)/vsoc_x86_64_only/auto_mdnd/aosp_cf.mk \
	aosp_cf_x86_64_auto_portrait:$(LOCAL_DIR)/vsoc_x86_64_only/auto_portrait/aosp_cf.mk \
	aosp_cf_x86_64_pc:$(LOCAL_DIR)/vsoc_x86_64_only/pc/aosp_cf.mk \
	aosp_cf_x86_64_phone:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf.mk \
	aosp_cf_x86_64_phone_vendor:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf_vendor.mk \
	aosp_cf_x86_64_ssi:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf_ssi.mk \
	aosp_cf_x86_64_tv:$(LOCAL_DIR)/vsoc_x86_64/tv/aosp_cf.mk \
	aosp_cf_x86_64_foldable:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf_foldable.mk \
	aosp_cf_x86_64_minidroid:$(LOCAL_DIR)/vsoc_x86_64_minidroid/aosp_cf.mk \
	aosp_cf_x86_64_only_phone:$(LOCAL_DIR)/vsoc_x86_64_only/phone/aosp_cf.mk \
	aosp_cf_x86_64_only_phone_hsum:$(LOCAL_DIR)/vsoc_x86_64_only/phone/aosp_cf_hsum.mk \
	aosp_cf_x86_64_slim:$(LOCAL_DIR)/vsoc_x86_64_only/slim/aosp_cf.mk \
	aosp_cf_x86_64_wear:$(LOCAL_DIR)/vsoc_x86_64_only/wear/aosp_cf.mk \
	aosp_cf_x86_pasan:$(LOCAL_DIR)/vsoc_x86/pasan/aosp_cf.mk \
	aosp_cf_x86_phone:$(LOCAL_DIR)/vsoc_x86/phone/aosp_cf.mk \
	aosp_cf_x86_only_phone:$(LOCAL_DIR)/vsoc_x86_only/phone/aosp_cf.mk \
	aosp_cf_x86_go_phone:$(LOCAL_DIR)/vsoc_x86/go/aosp_cf.mk \
	aosp_cf_x86_tv:$(LOCAL_DIR)/vsoc_x86/tv/aosp_cf.mk \
	aosp_cf_x86_wear:$(LOCAL_DIR)/vsoc_x86/wear/aosp_cf.mk \
  
COMMON_LUNCH_CHOICES := \
	aosp_cf_arm64_auto-userdebug \
	aosp_cf_arm64_phone-userdebug \
	aosp_cf_x86_64_only_phone_hsum-userdebug \
	aosp_cf_x86_64_pc-userdebug \
	aosp_cf_x86_64_phone-userdebug \
	aosp_cf_x86_64_foldable-userdebug \
	aosp_cf_x86_64_auto-userdebug \
	aosp_cf_x86_64_auto_mdnd-userdebug \
	aosp_cf_x86_phone-userdebug \
	aosp_cf_x86_tv-userdebug \
	aosp_cf_x86_64_tv-userdebug
  
