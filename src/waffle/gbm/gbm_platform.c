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

#define __GBM__ 1
#define _POSIX_C_SOURCE 200112 // glib feature macro for unsetenv()

#include <stdlib.h>

#include <waffle/core/wcore_error.h>
#include <waffle/linux/linux_platform.h>

#include "gbm_config.h"
#include "gbm_context.h"
#include "gbm_display.h"
#include "gbm_platform.h"
#include "gbm_priv_egl.h"
#include "gbm_window.h"

static const struct wcore_platform_vtbl gbm_platform_wcore_vtbl;

static bool
gbm_platform_destroy(struct wcore_platform *wc_self)
{
    return false;
}

struct wcore_platform*
gbm_platform_create(void)
{
    return NULL;
}

static bool
gbm_platform_make_current(struct wcore_platform *wc_self,
                          struct wcore_display *wc_dpy,
                          struct wcore_window *wc_window,
                          struct wcore_context *wc_ctx)
{
    return false;
}

static void*
gbm_platform_get_proc_address(struct wcore_platform *wc_self,
                              const char *name)
{
    return NULL;
}

static bool
gbm_platform_dl_can_open(struct wcore_platform *wc_self,
                         int32_t waffle_dl)
{
    return false;
}

static void*
gbm_platform_dl_sym(struct wcore_platform *wc_self,
                    int32_t waffle_dl,
                    const char *name)
{
    return NULL;
}

static const struct wcore_platform_vtbl gbm_platform_wcore_vtbl = {
    .destroy = gbm_platform_destroy,
    .connect_to_display = gbm_display_connect,
    .choose_config = gbm_config_choose,
    .create_context = gbm_context_create,
    .create_window = gbm_window_create,
    .make_current = gbm_platform_make_current,
    .get_proc_address = gbm_platform_get_proc_address,
    .dl_can_open = gbm_platform_dl_can_open,
    .dl_sym = gbm_platform_dl_sym,
};
