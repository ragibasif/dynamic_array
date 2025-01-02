/*
 * File: main.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 * Description:
 *   Implementation file that provides functionality described in example.h.
 *   Include detailed description of what this module does.
 *
 * Notes:
 *   - Any important implementation details or assumptions
 *   - Known limitations or edge cases
 *   - Performance considerations if applicable
 *
 */

/* ============================================================================
 * Includes
 * ============================================================================
 */

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================================
 * Private Macros and Constants
 * ============================================================================
 */

#define BUFFER_SIZE 256

/* ============================================================================
 * Entry Point
 * ============================================================================
 */

int main( int argc, char **argv ) {
    (void)argc; /* Suppress unused parameter warning */
    (void)argv;

    fprintf( stdout, "%s\n\n", PROGRAM_NAME );
    fprintf( stdout, "Written by: %s\n\n", PROGRAM_AUTHOR );
    fprintf( stdout, "Program version: %u.%u.%u\n\n",
             VERSION_GET_MAJOR( PROGRAM_VERSION_NUM ),
             VERSION_GET_MINOR( PROGRAM_VERSION_NUM ),
             VERSION_GET_PATCH( PROGRAM_VERSION_NUM ) );

    return EXIT_SUCCESS;
}
