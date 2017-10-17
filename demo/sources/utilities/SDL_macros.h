#pragma once

#include "logging.h"


/// Checks if the specified expression is < -1, and if so logs an SDL error and
/// returns a specified value.
#define SDL_CHECK(EXPRESSION, ERROR_RETURN_VALUE)           \
        if (EXPRESSION < 0)                                 \
        {                                                   \
            log_SDL_error(__FILE__, __LINE__, __func__);    \
            return ERROR_RETURN_VALUE; \
        }
/// Checks if the specified expression is null, and if so logs an SDL error and
/// returns a specified value.
#define SDL_CHECK_NULL(EXPRESSION, ERROR_RETURN_VALUE)      \
        if (EXPRESSION == nullptr)                          \
        {                                                   \
            log_SDL_error(__FILE__, __LINE__, __func__);    \
            return ERROR_RETURN_VALUE;                      \
        }
