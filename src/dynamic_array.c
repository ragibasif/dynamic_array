// FIX: Add error handling for release mode
// FIX: Add bounds checking in release mode (assertions compile out)
// TODO: Add documentation
// TODO: Add shrink_to_fit() - Reduce capacity to match size.
// TODO: Add reserve() - Ensures at least `n` capacity without changing size.
// TODO: Add usage examples
// FIX: add error codes
// TODO: Add helper functions for index, size, pointer validations
// FIX: Convert hard coded int type to generic

#include "dynamic_array.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 8

// Debug macro - disabled by default, can be enabled with -DDEBUG=1
#ifndef DEBUG
#define DEBUG 0
#endif

// Test macro - disabled by default, can be enabled with -DTEST=1
#ifndef TEST
#define TEST 0
#endif

static int euclidean_division( const int a, const int b );

struct dynamic_array *dynamic_array_create( void ) {
    struct dynamic_array *da;
    da = malloc( sizeof *da );
    assert( da != NULL );
    dynamic_array_init( da );
    return da;
}

void dynamic_array_init( struct dynamic_array *da ) {
    da->size     = 0;
    da->capacity = DEFAULT_CAPACITY;
    da->buffer   = malloc( sizeof *da->buffer * da->capacity );
    assert( da->buffer != NULL );
}

void dynamic_array_clear( struct dynamic_array *da ) {
    assert( da != NULL );
    if ( da->buffer ) {
        free( da->buffer );
        dynamic_array_init( da );
    }
}

void dynamic_array_destroy( struct dynamic_array *da ) {
    assert( da != NULL );
    dynamic_array_clear( da );
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

void dynamic_array_push( struct dynamic_array *da, const int value ) {
    if ( da->size + 1 >= da->capacity ) { dynamic_array_expand( da ); }
    da->buffer[da->size++] = value;
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

int dynamic_array_find( const struct dynamic_array *da, const int value ) {
    assert( da != NULL );
    for ( size_t i = 0; i < da->size; i++ ) {
        if ( da->buffer[i] == value ) { return (int)i; }
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
                        const int value ) {
    assert( da != NULL );
    assert( index < da->size );
    da->buffer[index] = value;
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
                           const int value ) {
    assert( index <= da->size );
    if ( da->size + 1 >= da->capacity ) { dynamic_array_expand( da ); }
    for ( size_t i = da->size; i > index; i-- ) {
        da->buffer[i] = da->buffer[i - 1];
    }
    da->buffer[index] = value;
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

int dynamic_array_find_transposition( struct dynamic_array *da, int value ) {
    // every time the value is found, swap it one position to the left
    // frequently searched for value is gradually moved to the front to
    // reduce search time
    int position = dynamic_array_find( da, value );
    if ( position > 0 ) {
        int temp_value           = da->buffer[position];
        da->buffer[position]     = da->buffer[position - 1];
        da->buffer[position - 1] = temp_value;
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
    for ( size_t i = da->size - 1; i > 0; i-- ) {
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
    for ( size_t i = 0; i < da->size - 1; i++ ) {
        da->buffer[i] = da->buffer[i + 1];
    }
    da->buffer[da->size - 1] = first;
}

void dynamic_array_rotate_right_n( struct dynamic_array *da, int count ) {
    // get the mod so as not to do redundant operations
    int rotations = euclidean_division( count, da->size );
    for ( size_t i = 0; i < rotations; i++ ) {
        dynamic_array_rotate_right( da );
    }
}

void dynamic_array_rotate_left_n( struct dynamic_array *da, int count ) {
    // get the mod so as not to do redundant operations
    int rotations = euclidean_division( count, da->size );
    for ( size_t i = 0; i < rotations; i++ ) {
        dynamic_array_rotate_left( da );
    }
}

void dynamic_array_fill( struct dynamic_array *da, const int value ) {
    assert( da != NULL );
    assert( da->size > 0 );
    for ( size_t i = 0; i < da->size; i++ ) { da->buffer[i] = value; }
}

bool dynamic_array_empty( const struct dynamic_array *da ) {
    assert( da != NULL );
    return da->size == 0;
}

// https://en.wikipedia.org/wiki/Euclidean_division
// a = bq + r and 0 <= r < |b|
// euclidean modulo == euclidean division
// In C/C++, a % b always returns results with the sign of a
// Mathematically, modulo is always non-negative
// % -> remainder operator in C
// % -> already behaves like Euclidean modulo for unsigned integers
// returns between [0,n-1], (same behavior of the modulo operator in python)
int euclidean_division( const int a, const int b ) {
    if ( b == 0 ) { // b == 0 is Undefined Behavior/Division by zero error
        return 0;
    }
    if ( a == INT_MIN && b == -1 ) {
        return 0; // mathematically 0 but UB because of overflow
    }
    long long r = a % b;
    if ( r < 0 ) { r += abs( b ); }
    return r;
}
