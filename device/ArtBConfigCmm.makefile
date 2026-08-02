TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true
TARGET_CPU_SMP := true
$(call soong_config_set,art_module,source_build,true)
