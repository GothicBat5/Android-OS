#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hardware/hardware.h>
#include <hardware/boot_control.h>
#include "bootctrl.h"

#define BOOTCTRL_METADATA_FILE  "/dev/block/by-name/misc"
#define SLOT_SUFFIX_STR "androidboot.slot_suffix="
#define COMMAND_LINE_SIZE 2048

static int bootctrl_read_metadata(boot_ctrl_t *bctrl)
{
    int fd, err;
    ssize_t sz, size;
    char *buf = (char *)bctrl;
    fd = open(BOOTCTRL_METADATA_FILE, O_RDONLY);
  
    if (fd < 0) 
    {
        err = errno;
        fprintf(stderr, "Error opening metadata file: %s\n", strerror(errno));
        return -err;
    }
    if (lseek(fd, OFFSETOF_SLOT_SUFFIX, SEEK_SET) < 0) 
    {
        err = errno;
        fprintf(stderr, "Error seeking to metadata offset: %s\n", strerror(errno));
        close(fd);
        return -err;
    }
  
    size = sizeof(boot_ctrl_t);
    do {
        sz = read(fd, buf, size);
        if (sz == 0) {
            break;
        } 
        else if (sz < 0) 
        {
            if (errno == EINTR) 
            {
                continue;
            }
            err = -errno;
            fprintf(stderr, "Error reading metadata file\n");
            close(fd);
            return err;
        }
        size -= sz;
        buf += sz;
    } 
      while(size > 0);
    close(fd);
  
    if (bctrl->magic != BOOTCTRL_MAGIC) 
    {
        fprintf(stderr, "metadata is not initialised or corrupted.\n");
        return -EIO;
    }
    return 0;
}
static int bootctrl_write_metadata(boot_ctrl_t *bctrl)
{
    int fd, err;
    ssize_t sz, size;
    char *buf = (char *)bctrl;
    fd = open(BOOTCTRL_METADATA_FILE, O_RDWR);
  
    if (fd < 0) {
        err = errno;
        fprintf(stderr, "Error opening metadata file: %s\n", strerror(errno));
        return -err;
    }
    if (lseek(fd, OFFSETOF_SLOT_SUFFIX, SEEK_SET) < 0) {
        err = errno;
        fprintf(stderr, "Error seeking to metadata offset: %s\n", strerror(errno));
        close(fd);
        return -err;
    }
    size = sizeof(boot_ctrl_t);
  
    do {
        sz = write(fd, buf, size);
        if (sz == 0) {
            break;
        } 
        else if (sz < 0) {
            if (errno == EINTR) {
                continue;
            }
            err = -errno;
            fprintf(stderr, "Error Writing metadata file\n");
            close(fd);
            return err;
        }
        size -= sz;
        buf += sz;
    } while(size > 0);
    close(fd);
    return 0;
}
void bootctrl_init(boot_control_module_t *module __unused)
{
    /* Nothing to init */
}
unsigned bootctrl_get_number_slots(boot_control_module_t *module __unused)
{
    /* This is A/B system, so it will be always 2. */
    return 2;
}
int bootctrl_get_active_slot()
{
    int fd, err, slot;
    ssize_t size = COMMAND_LINE_SIZE, sz;
    off_t off;
    char *buf, *ptr;
    char *str;
    fd = open("/proc/cmdline", O_RDONLY);
  
    if (fd < 0) {
        err = -errno;
        fprintf(stderr, "error reading commandline\n");
        return err;
    }
    ptr = buf = malloc(size);
  
    if (!buf) 
    {
        err = -errno;
        fprintf(stderr, "Error allocating memory\n");
        close(fd);
        return err;
    }
    do {
        sz = read(fd, buf, size);
        if (sz == 0) {
            break;
        } 
        else if (sz < 0) {
            if (errno == EINTR) {
                continue;
            }
            err = -errno;
            fprintf(stderr, "Error reading file\n");
            free(ptr);
            close(fd);
            return err;
        }
        size -= sz;
        buf += sz;
    }
      while(size > 0);
    str = strstr((char *)ptr, SLOT_SUFFIX_STR);
  
    if (!str) 
    {
        err = -EIO;
        fprintf(stderr, "cannot find %s in kernel commandline.\n", SLOT_SUFFIX_STR);
        free(ptr);
        close(fd);
        return err;
    }
    str += sizeof(SLOT_SUFFIX_STR);
    slot = (*str == 'a') ? 0 : 1;
    free(ptr);
    close(fd);
    return slot;
}
unsigned bootctrl_get_current_slot(boot_control_module_t *module __unused)
{
    int ret;
    boot_ctrl_t metadata;
    ret = bootctrl_read_metadata(&metadata);
    if (ret < 0) {
	/* anything larger than 2 will be considered as error. */
        return (unsigned)ret;
    }
    return bootctrl_get_active_slot();
}
int bootctrl_mark_boot_successful(boot_control_module_t *module __unused)
{
    int ret, slot;
    boot_ctrl_t metadata;
    slot_metadata_t *slotp;
    ret = bootctrl_read_metadata(&metadata);
    if (ret < 0) {
        return ret;
    }

    slot = bootctrl_get_active_slot();
    if (slot < 0) {
        return slot;
    }
    slotp = &metadata.slot_info[slot];
    slotp->successful_boot = 1;
    slotp->tries_remaining = 0;
    return bootctrl_write_metadata(&metadata);
}
int bootctrl_set_active_boot_slot(boot_control_module_t *module __unused,
    unsigned slot)
{
    int ret, slot2;
    boot_ctrl_t metadata;
    slot_metadata_t *slotp;
    if (slot >= 2) {
        fprintf(stderr, "Wrong Slot value %u\n", slot);
        return -EINVAL;
    }
    ret = bootctrl_read_metadata(&metadata);
    if (ret < 0) {
        return ret;
    }

    slotp = &metadata.slot_info[slot];
    slotp->successful_boot = 0;
    slotp->priority = 15;
    slotp->tries_remaining = 7;
    slot2 = (slot == 0) ? 1 : 0;
    slotp = &metadata.slot_info[slot2];
  
    if (slotp->priority >= 15) 
    {
        slotp->priority = 14;
    }
    ret = bootctrl_write_metadata(&metadata);
    if (ret < 0) 
    {
        return ret;
    }
    return 0;
}
int bootctrl_set_slot_as_unbootable(boot_control_module_t *module __unused,
    unsigned slot)
{
    int ret;
    boot_ctrl_t metadata;
  
    slot_metadata_t *slotp;
  
    if (slot >= 2) 
    {
        fprintf(stderr, "Wrong Slot value %u\n", slot);
        return -EINVAL;
    }
    ret = bootctrl_read_metadata(&metadata);
  
    if (ret < 0) 
    {
        return ret;
    }

    slotp = &metadata.slot_info[slot];
    slotp->successful_boot = 0;
    slotp->priority = 0;
    slotp->tries_remaining = 0;
    ret = bootctrl_write_metadata(&metadata);
    if (ret < 0) {
        return ret;
    }
    return 0;
}
int bootctrl_is_slot_bootable(boot_control_module_t *module __unused,
	unsigned slot)
{
    int ret;
    boot_ctrl_t metadata;
    if (slot >= 2) {
        fprintf(stderr, "Wrong Slot value %u\n", slot);
        return -EINVAL;
    }
    ret = bootctrl_read_metadata(&metadata);
    if (ret < 0) {
        return ret;
    }
    return (metadata.slot_info[slot].priority != 0);
}
const char *bootctrl_get_suffix(boot_control_module_t *module __unused,
    unsigned slot)
{
    static const char* suffix[2] = {BOOTCTRL_SUFFIX_A, BOOTCTRL_SUFFIX_B};
    if (slot >= 2)
        return NULL;
    return suffix[slot];
}
static int bootctrl_open(const hw_module_t *module, const char *id __unused,
    hw_device_t **device __unused)
{
    /* Nothing to do currently */
    return 0;
}
static struct hw_module_methods_t bootctrl_methods = {
    .open  = bootctrl_open,
};
/* Boot Control Module implementation */
boot_control_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = BOOT_CONTROL_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = BOOT_CONTROL_HARDWARE_MODULE_ID,
        .name = "boot_control HAL",
        .author = "Intel Corporation",
        .methods = &bootctrl_methods,
    },
    .init = bootctrl_init,
    .getNumberSlots = bootctrl_get_number_slots,
    .getCurrentSlot = bootctrl_get_current_slot,
    .markBootSuccessful = bootctrl_mark_boot_successful,
    .setActiveBootSlot = bootctrl_set_active_boot_slot,
    .setSlotAsUnbootable = bootctrl_set_slot_as_unbootable,
    .isSlotBootable = bootctrl_is_slot_bootable,
    .getSuffix = bootctrl_get_suffix,
};
