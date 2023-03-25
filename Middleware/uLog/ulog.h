/*
 * uLog: lightweight logging for embedded systems
 *
 * MIT License
 *
 * Copyright (c) 2023 Chung-Yi YANG <cyyang023@gmail.com>
 * Copyright (c) 2019 R. Dunbar Poor <rdpoor@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef ULOG_H_
#define ULOG_H_

// ULOG function enable. If you don't want to use, comment the following macro.
#define ULOG_ENABLED

// ULOG color enable. If you don't want to use, comment the following macro.
#define ULOG_COLOR_ENABLE

#include "ulog_color.h"

typedef enum {
    ULOG_ASSERT_LEVEL = 0,
    ULOG_ERROR_LEVEL,
    ULOG_WARN_LEVEL,
    ULOG_INFO_LEVEL,
    ULOG_DEBUG_LEVEL,
    ULOG_VERBOSE_LEVEL,
    ULOG_ALWAYS_LEVEL
} ulog_level_t;

#ifdef ULOG_ENABLED
#define ULOG_INIT()          ulog_init()
#define ULOG_SUBSCRIBE(a, b) ulog_subscribe(a, b)
#define ULOG_UNSUBSCRIBE(a)  ulog_unsubscribe(a)
#define ULOG_LEVEL_NAME(a)   ulog_level_name(a)
#define ULOG(...)            ulog_message(__VA_ARGS__)
#define ULOG_ASSERT(...)     ulog_message(ULOG_ASSERT_LEVEL, __VA_ARGS__)
#define ULOG_ERROR(...)      ulog_message(ULOG_ERROR_LEVEL, __VA_ARGS__)
#define ULOG_WARN(...)       ulog_message(ULOG_WARN_LEVEL, __VA_ARGS__)
#define ULOG_INFO(...)       ulog_message(ULOG_INFO_LEVEL, __VA_ARGS__)
#define ULOG_DEBUG(...)      ulog_message(ULOG_DEBUG_LEVEL, __VA_ARGS__)
#define ULOG_VERBOSE(...)    ulog_message(ULOG_VERBOSE_LEVEL, __VA_ARGS__)
#define ULOG_ALWAYS(...)    ulog_message(ULOG_ALWAYS_LEVEL, __VA_ARGS__)
#else
// uLog vanishes when disabled at compile time...
#define ULOG_INIT() \
    do {            \
    } while (0)
#define ULOG_SUBSCRIBE(a, b) \
    do {                     \
    } while (0)
#define ULOG_UNSUBSCRIBE(a) \
    do {                    \
    } while (0)
#define ULOG_LEVEL_NAME(a) \
    do {                   \
    } while (0)
#define ULOG(s, f, ...) \
    do {                \
    } while (0)
#define ULOG_ASSERT(f, ...) \
    do {                    \
    } while (0)
#define ULOG_ERROR(f, ...) \
    do {                   \
    } while (0)
#define ULOG_WARN(f, ...) \
    do {                  \
    } while (0)
#define ULOG_INFO(f, ...) \
    do {                  \
    } while (0)
#define ULOG_DEBUG(f, ...) \
    do {                   \
    } while (0)
#define ULOG_VERBOSE(f, ...) \
    do {                     \
    } while (0)
#define ULOG_ALWAYS(f, ...) \
    do {                     \
    } while (0)
#endif

typedef enum {
    ULOG_ERR_NONE = 0,
    ULOG_ERR_SUBSCRIBERS_EXCEEDED,
    ULOG_ERR_NOT_SUBSCRIBED,
} ulog_err_t;

// define the maximum number of concurrent subscribers
#ifndef ULOG_MAX_SUBSCRIBERS
#define ULOG_MAX_SUBSCRIBERS 6
#endif

// maximum length of formatted log message
#ifndef ULOG_MAX_MESSAGE_LENGTH
#define ULOG_MAX_MESSAGE_LENGTH 120
#endif

// prototype for uLog subscribers.
typedef void (*ulog_function_t)(ulog_level_t severity, char *msg);

void ulog_init(void);
ulog_err_t ulog_subscribe(ulog_function_t fn, ulog_level_t threshold);
ulog_err_t ulog_unsubscribe(ulog_function_t fn);
const char *ulog_level_name(ulog_level_t level);
void ulog_message(ulog_level_t severity, const char *fmt, ...);

// user defined ulog_function_t manager
void console_logger(ulog_level_t severity, char *msg);

#endif /* ULOG_H_ */
