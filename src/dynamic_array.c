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

#include "dynamic_array.h"

#include "dbg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================================
 * Private Macros and Constants
 * ============================================================================
 */

#define DEFAULT_CAPACITY 8

/* Debug macro - disabled by default, can be enabled with -DDEBUG=1 */
#ifndef DEBUG
#define DEBUG 0
#endif

/* ============================================================================
 * Private Type Definitions
 * ============================================================================
 */

struct dynamic_array {
    int   *buffer;
    size_t size;
    size_t capacity;
};

/* ============================================================================
 * Private Function Declarations
 * ============================================================================
 */

/* ============================================================================
 * Public Function Implementations
 * ============================================================================
 */

struct dynamic_array *dynamic_array_create( void ) {
    struct dynamic_array *da;

    da = malloc( sizeof *da );
    assert( da != NULL );

    da->buffer = malloc( sizeof *da->buffer * DEFAULT_CAPACITY );
    assert( da->buffer != NULL );
    memset( da->buffer, 0, sizeof *da->buffer * DEFAULT_CAPACITY );

    da->size     = 0;
    da->capacity = DEFAULT_CAPACITY;

    return da;
}

void dynamic_array_destroy( struct dynamic_array *da ) {
    assert( da != NULL );

    da->size     = 0;
    da->capacity = 0;
    free( da->buffer );
    da->buffer = NULL;
    free( da );
    da = NULL;
}

size_t dynamic_array_size( const struct dynamic_array *da ) {
    assert( da != NULL );
    return da->size;
}

size_t dynamic_array_capacity( const struct dynamic_array *da ) {
    assert( da != NULL );
    return da->capacity;
}

/* ============================================================================
 * Private Function Implementations
 * ============================================================================
 */
