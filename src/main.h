/*
 * File: main.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 * Description:
 *   Brief description of what this header file provides.
 *   Include its purpose and main functionality.
 *
 * Notes:
 *   - Any important implementation notes or caveats
 *   - Dependencies or requirements
 *   - Known limitations or future improvements
 *
 */

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#define PROGRAM_NAME    "Dynamic Array"
#define PROGRAM_VERSION "1.0.0"
#define PROGRAM_AUTHOR  "Ragib Asif (ragibasif@tuta.io)"

// Version: Major.Minor.Patch (1 byte each: MMMM MMMM | NNNN NNNN | PPPP PPPP)
#define PROGRAM_VERSION_MAJOR 1
#define PROGRAM_VERSION_MINOR 0
#define PROGRAM_VERSION_PATCH 0

#define PROGRAM_VERSION_NUM                                                    \
    ( ( PROGRAM_VERSION_MAJOR << 16 ) | ( PROGRAM_VERSION_MINOR << 8 ) |       \
      PROGRAM_VERSION_PATCH )

// Bit masking macros to extract version components
#define VERSION_GET_MAJOR( v ) ( ( v >> 16 ) & 0xFF )
#define VERSION_GET_MINOR( v ) ( ( v >> 8 ) & 0xFF )
#define VERSION_GET_PATCH( v ) ( v & 0xFF )

/* Debug macro - disabled by default, can be enabled with -DDEBUG=1 */
#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG
#define TRACE( fmt, ... )                                                      \
    do {                                                                       \
        fprintf( stderr, "[TRACE] %s:%d in %s(): " fmt "\n", __FILE__,         \
                 __LINE__, __func__, ##__VA_ARGS__ );                          \
        fflush( stderr );                                                      \
    } while ( 0 )
#else
#define TRACE( fmt, ... )                                                      \
    do { (void)0; } while ( 0 )
#endif

#ifdef __cplusplus
}
#endif

#endif // MAIN_H
