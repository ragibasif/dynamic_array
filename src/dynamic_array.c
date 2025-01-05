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

void dynamic_array_expand( struct dynamic_array *da ) {
    assert( da != NULL );
    assert( ( sizeof *da->buffer * ( da->capacity << 1 ) ) < SIZE_MAX );
    da->capacity <<= 1; // capacity is doubled through bit shifting
    int *buffer = realloc( da->buffer, sizeof *da->buffer * da->capacity );
    assert( buffer != NULL );
    da->buffer = buffer;
}

void dynamic_array_push( struct dynamic_array *da, const int data ) {
    if ( da->size + 1 >= da->capacity ) { dynamic_array_expand( da ); }
    da->buffer[da->size++] = data;
}

int dynamic_array_pop( struct dynamic_array *da ) {
    // FIX: undefined behavior on empty array in non-debug mode
    assert( da->size > 0 );
    return da->buffer[--da->size];
}

void dynamic_array_print( const struct dynamic_array *da ) {
    assert( da != NULL );
    for ( size_t i = 0; i < da->size; i++ ) { printf( "%d ", da->buffer[i] ); }
    putchar( '\n' );
}

int dynamic_array_find( const struct dynamic_array *da, const int data ) {
    assert( da != NULL );

    for ( size_t i = 0; i < da->size; i++ ) {
        if ( da->buffer[i] == data ) { return (int)i; }
    }
    return -1;
}

// FIX: These functions should validate non-NULL inputs at runtime
int dynamic_array_get( const struct dynamic_array *da, const size_t index ) {
    assert( da != NULL );
    assert( index < da->size );
    return da->buffer[index];
}

void dynamic_array_set( const struct dynamic_array *da, const size_t index,
                        const int data ) {
    assert( da != NULL );
    assert( index < da->size );
    da->buffer[index] = data;
}

/* ============================================================================
 * Private Function Implementations
 * ============================================================================
 */
