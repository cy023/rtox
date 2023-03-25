/*
 * uLog: lightweight logging for embedded systems
 *
 * MIT License
 *
 * Copyright (c) 2023 Chung-Yi YANG <cyyang023@gmail.com>
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

#ifndef ULOG_PORT_H
#define ULOG_PORT_H

#include "ulog.h"

#ifdef ULOG_COLOR_ENABLE
/**
 * CSI(Control Sequence Introducer/Initiator)
 * sign more information on https://en.wikipedia.org/wiki/ANSI_escape_code
 */
#define CSI_START "\033["
#define CSI_END   "\033[0m"

/* Front color */
#define F_BLACK   "30;"
#define F_RED     "31;"
#define F_GREEN   "32;"
#define F_YELLOW  "33;"
#define F_BLUE    "34;"
#define F_MAGENTA "35;"
#define F_CYAN    "36;"
#define F_WHITE   "37;"

/* Background color */
#define B_NULL
#define B_BLACK   "40;"
#define B_RED     "41;"
#define B_GREEN   "42;"
#define B_YELLOW  "43;"
#define B_BLUE    "44;"
#define B_MAGENTA "45;"
#define B_CYAN    "46;"
#define B_WHITE   "47;"

/* Fonts style */
#define S_BOLD      "1m"
#define S_UNDERLINE "4m"
#define S_BLINK     "5m"
#define S_NORMAL    "22m"

/* output log default color definition: [front color] + [background color] +
 * [show style] */
#ifndef ULOG_COLOR_ASSERT
#define ULOG_COLOR_ASSERT (CSI_START F_MAGENTA B_NULL S_NORMAL)
#endif

#ifndef ULOG_COLOR_ERROR
#define ULOG_COLOR_ERROR (CSI_START F_RED B_NULL S_NORMAL)
#endif

#ifndef ULOG_COLOR_WARN
#define ULOG_COLOR_WARN (CSI_START F_YELLOW B_NULL S_NORMAL)
#endif

#ifndef ULOG_COLOR_INFO
#define ULOG_COLOR_INFO (CSI_START F_CYAN B_NULL S_NORMAL)
#endif

#ifndef ULOG_COLOR_DEBUG
#define ULOG_COLOR_DEBUG (CSI_START F_GREEN B_NULL S_NORMAL)
#endif

#ifndef ULOG_COLOR_VERBOSE
#define ULOG_COLOR_VERBOSE (CSI_START F_BLUE B_NULL S_NORMAL)
#endif

#ifndef ULOG_COLOR_ALWAYS
#define ULOG_COLOR_ALWAYS (CSI_START B_BLACK B_NULL S_NORMAL)
#endif

#endif /* ULOG_COLOR_ENABLE */

#endif /* ULOG_PORT_H */