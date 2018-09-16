// Copyright 2012 Intel Corporation
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <stdlib.h>

#include "wcore_error.h"

#include "wegl_config.h"
#include "wegl_context.h"
#include "wegl_platform.h"
#include "wegl_util.h"

#include "swegl_display.h"
#include "swegl_platform.h"
#include "swegl_window.h"

static const struct wcore_platform_vtbl swegl_platform_vtbl;

static bool
swegl_platform_destroy(struct wcore_platform *wc_self)
{
    struct swegl_platform *self = swegl_platform(wegl_platform(wc_self));
    bool ok = true;

    if (!self)
        return true;

    ok &= wegl_platform_teardown(&self->wegl);
    free(self);
    return ok;
}

struct wcore_platform*
swegl_platform_create(void)
{
    bool ok = true;

    struct swegl_platform *self = wcore_calloc(sizeof(*self));
    if (self == NULL)
        return NULL;

    ok = wegl_platform_init(&self->wegl, EGL_PLATFORM_ANDROID_KHR);
    if (!ok)
        goto fail;

    self->wegl.egl_surface_type_mask = EGL_WINDOW_BIT;

    self->wegl.wcore.vtbl = &swegl_platform_vtbl;
    return &self->wegl.wcore;

fail:
    swegl_platform_destroy(&self->wegl.wcore);
    return NULL;
}

static bool
swegl_dl_can_open(struct wcore_platform *wc_self, int32_t waffle_dl)
{
    return false;
}

static void*
swegl_dl_sym(struct wcore_platform *wc_self,
          int32_t waffle_dl, const char *name)
{
    return false;
}

static const struct wcore_platform_vtbl swegl_platform_vtbl = {
    .destroy = swegl_platform_destroy,

    .make_current = wegl_make_current,
    .get_proc_address = wegl_get_proc_address,

    .dl_can_open = swegl_dl_can_open,
    .dl_sym = swegl_dl_sym,

    .display = {
        .connect = swegl_display_connect,
        .destroy = swegl_display_destroy,
        .supports_context_api = wegl_display_supports_context_api,
        .get_native = NULL, // unsupported by platform
    },

    .config = {
        .choose = wegl_config_choose,
        .destroy = wegl_config_destroy,
        .get_native = NULL, // unsupported by platform
    },

    .context = {
        .create = wegl_context_create,
        .destroy = wegl_context_destroy,
        .get_native = NULL, // unsupported by platform
    },

    .window = {
        .create = swegl_window_create,
        .destroy = swegl_window_destroy,
        .show = swegl_window_show,
        .swap_buffers = wegl_surface_swap_buffers,
        .get_native = NULL, // unsupported by platform
    },
};
