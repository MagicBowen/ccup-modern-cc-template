#ifndef __STATUS__H__
#define __STATUS__H__

#include "hiccup/hiccup.h"
#include <stdint.h>

HICCUP_BEGIN

using Status = uint32_t;

enum : Status
{
    HICCUP_SUCCESS = 0,
    HICCUP_FAILURE = 0x80000000,
};

constexpr inline bool status_failed(Status status)
{
    return status != HICCUP_SUCCESS;
}

HICCUP_END

#endif