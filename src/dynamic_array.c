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

// FIX: Add error handling for release mode
// FIX: Add bounds checking in release mode (assertions compile out)
// TODO: Add documentation
// TODO: Add shrink_to_fit()
// TODO: Add reserve()
// TODO: Add usage examples
// FIX: add error codes
// TODO: Add helper functions for index, size, pointer validations
// FIX: Convert hard coded int type to generic

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

int dynamic_array_front( const struct dynamic_array *da ) {
    assert( da != NULL );
    assert( da->size > 0 );
    return da->buffer[0];
}

int dynamic_array_back( const struct dynamic_array *da ) {
    assert( da != NULL );
    assert( da->size > 0 );
    return da->buffer[da->size - 1];
}

// time: O(N)
void dynamic_array_insert( struct dynamic_array *da, const size_t index,
                           const int data ) {
    assert( index < da->size );
    if ( da->size + 1 >= da->capacity ) { dynamic_array_expand( da ); }
    for ( size_t i = da->size; i > index; i-- ) {
        da->buffer[i] = da->buffer[i - 1];
    }
    da->buffer[index] = data;
    da->size++;
}

int dynamic_array_remove( struct dynamic_array *da, const size_t index ) {
    assert( index < da->size && da->size > 0 );
    int item = da->buffer[index];
    for ( size_t i = index; i < da->size - 1; i++ ) {
        da->buffer[i] = da->buffer[i + 1];
    }
    da->size--;
    return item;
}

void dynamic_array_clear( struct dynamic_array *da ) {
    assert( da != NULL );
    if ( da->size > 0 ) {
        memset( da->buffer, 0, sizeof *da->buffer * da->capacity );
        da->size = 0;
    }
}

int dynamic_array_find_transposition( struct dynamic_array *da, int data ) {
    // every time the data is found, swap it one position to the left
    // frequently searched for data is gradually moved to the front to
    // reduce search time
    int position = dynamic_array_find( da, data );
    if ( position > 0 ) {
        int temp_data            = da->buffer[position];
        da->buffer[position]     = da->buffer[position - 1];
        da->buffer[position - 1] = temp_data;
        position--;
    }
    return position;
}

// time: O(N)
void dynamic_array_rotate_right( struct dynamic_array *da ) {
    // retrieve the last element
    // shift all elements to the right
    // set first element to previously saved last element
    int last = da->buffer[da->size - 1];
    for ( int i = da->size - 1; i > 0; i-- ) {
        da->buffer[i] = da->buffer[i - 1];
    }
    da->buffer[0] = last;
}

// time: O(N)
void dynamic_array_rotate_left( struct dynamic_array *da ) {
    // retrieve the first element
    // shift all elements to the left
    // set last element to previously saved first element
    int first = da->buffer[0];
    for ( int i = 0; i < da->size - 1; i++ ) {
        da->buffer[i] = da->buffer[i + 1];
    }
    da->buffer[da->size - 1] = first;
}

void dynamic_array_rotate_right_n( struct dynamic_array *da, int count ) {
    // get the mod so as not to do redundant operations
    int rotations = ( da->size + ( count % da->size ) ) % da->size;
    for ( int i = 0; i < rotations; i++ ) { dynamic_array_rotate_right( da ); }
}

void dynamic_array_rotate_left_n( struct dynamic_array *da, int count ) {
    // get the mod so as not to do redundant operations
    int rotations = ( da->size + ( count % da->size ) ) % da->size;
    for ( int i = 0; i < rotations; i++ ) { dynamic_array_rotate_left( da ); }
}

/* ============================================================================
 * Private Function Implementations
 * ============================================================================
 */
