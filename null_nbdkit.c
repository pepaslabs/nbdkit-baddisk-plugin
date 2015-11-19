/* baddisk_nbdkit.c
 * See https://github.com/pepaslabs/nbdkit-baddisk-plugin
 * Copyright (C) 2015 Jason Pepas.
 * Released under the terms of the MIT license.  See https://opensource.org/licenses/MIT
 */

// see also https://github.com/libguestfs/nbdkit/blob/master/docs/nbdkit-plugin.pod

#include <config.h>
#include <nbdkit-plugin.h> // nbdkit_error(), etc.

#define THREAD_MODEL NBDKIT_THREAD_MODEL_PARALLEL

// per-connection state (not used):
int handle;

void* baddisk_open(int readonly)
{
    return (void*)(&handle);
}

int64_t baddisk_get_size(void *passed_handle)
{
    return (int64_t)(8) * 1024 * 1024 * 1024;
}

int baddisk_pread(void *passed_handle, void *buf, uint32_t count, uint64_t offset)
{
    return -1;
}

int baddisk_pwrite(void *passed_handle, const void *buf, uint32_t count, uint64_t offset)
{
    return -1;
}

static struct nbdkit_plugin plugin = {
    .name              = "baddisk",
    .longname          = "nbdkit baddisk plugin",
    .description       = "An nbdkit plugin which fails every read and write.",
    .version           = "0.0",

    .open              = baddisk_open,
    .get_size          = baddisk_get_size,

    .pread             = baddisk_pread,
    .pwrite            = baddisk_pwrite
};

NBDKIT_REGISTER_PLUGIN(plugin)
