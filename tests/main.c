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
 */

#include "../src/dynamic_array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test counters
int tests_run    = 0;
int tests_passed = 0;

// Helper macro for assertions
#define TEST_ASSERT( condition, message )                                      \
    do {                                                                       \
        tests_run++;                                                           \
        if ( condition ) {                                                     \
            tests_passed++;                                                    \
            printf( "✓ %s\n", message );                                       \
        } else {                                                               \
            printf( "✗ %s\n", message );                                       \
        }                                                                      \
    } while ( 0 )

// ============================================================================
// Creation and Initialization Tests
// ============================================================================

void test_create_and_init() {
    struct dynamic_array *da = dynamic_array_create();
    TEST_ASSERT( da != NULL, "create returns non-NULL pointer" );
    TEST_ASSERT( da->size == 0, "new array has size 0" );
    TEST_ASSERT( da->capacity == 8, "new array has default capacity 8" );
    TEST_ASSERT( da->buffer != NULL, "new array has allocated buffer" );
    dynamic_array_destroy( da );
}

void test_init_on_existing() {
    struct dynamic_array da;
    dynamic_array_init( &da );
    TEST_ASSERT( da.size == 0, "init sets size to 0" );
    TEST_ASSERT( da.capacity == 8, "init sets capacity to 8" );
    TEST_ASSERT( da.buffer != NULL, "init allocates buffer" );
    dynamic_array_clear( &da );
}

// ============================================================================
// Push and Pop Tests
// ============================================================================

void test_push_single() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 42 );
    TEST_ASSERT( da->size == 1, "push increases size" );
    TEST_ASSERT( da->buffer[0] == 42, "push stores value correctly" );
    dynamic_array_destroy( da );
}

void test_push_multiple() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 0; i < 5; i++ ) { dynamic_array_push( da, i ); }
    TEST_ASSERT( da->size == 5, "push multiple increases size correctly" );
    for ( int i = 0; i < 5; i++ ) {
        TEST_ASSERT( da->buffer[i] == i, "push stores values in order" );
    }
    dynamic_array_destroy( da );
}

void test_push_expansion() {
    struct dynamic_array *da               = dynamic_array_create();
    size_t                initial_capacity = da->capacity;

    // Push beyond initial capacity
    for ( int i = 0; i < 20; i++ ) { dynamic_array_push( da, i ); }

    TEST_ASSERT( da->size == 20, "push beyond capacity stores all values" );
    TEST_ASSERT( da->capacity > initial_capacity,
                 "capacity expands when needed" );
    TEST_ASSERT( da->capacity == 32, "capacity doubles correctly" );

    dynamic_array_destroy( da );
}

void test_pop_single() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 100 );
    int val = dynamic_array_pop( da );
    TEST_ASSERT( val == 100, "pop returns correct value" );
    TEST_ASSERT( da->size == 0, "pop decreases size" );
    dynamic_array_destroy( da );
}

void test_pop_multiple() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 1; i <= 5; i++ ) { dynamic_array_push( da, i ); }

    for ( int i = 5; i >= 1; i-- ) {
        int val = dynamic_array_pop( da );
        TEST_ASSERT( val == i, "pop returns values in LIFO order" );
    }

    TEST_ASSERT( da->size == 0, "pop all leaves size at 0" );
    dynamic_array_destroy( da );
}

// ============================================================================
// Size and Capacity Tests
// ============================================================================

void test_size_capacity_queries() {
    struct dynamic_array *da = dynamic_array_create();
    TEST_ASSERT( dynamic_array_size( da ) == 0, "size query works on empty" );
    TEST_ASSERT( dynamic_array_capacity( da ) == 8, "capacity query works" );

    for ( int i = 0; i < 3; i++ ) { dynamic_array_push( da, i ); }

    TEST_ASSERT( dynamic_array_size( da ) == 3,
                 "size reflects pushed elements" );
    TEST_ASSERT( dynamic_array_capacity( da ) == 8, "capacity unchanged" );

    dynamic_array_destroy( da );
}

void test_empty() {
    struct dynamic_array *da = dynamic_array_create();
    TEST_ASSERT( dynamic_array_empty( da ) == true,
                 "empty returns true for new array" );

    dynamic_array_push( da, 1 );
    TEST_ASSERT( dynamic_array_empty( da ) == false,
                 "empty returns false after push" );

    dynamic_array_pop( da );
    TEST_ASSERT( dynamic_array_empty( da ) == true,
                 "empty returns true after pop" );

    dynamic_array_destroy( da );
}

// ============================================================================
// Get and Set Tests
// ============================================================================

void test_get() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 10 );
    dynamic_array_push( da, 20 );
    dynamic_array_push( da, 30 );

    TEST_ASSERT( dynamic_array_get( da, 0 ) == 10, "get index 0" );
    TEST_ASSERT( dynamic_array_get( da, 1 ) == 20, "get index 1" );
    TEST_ASSERT( dynamic_array_get( da, 2 ) == 30, "get index 2" );

    dynamic_array_destroy( da );
}

void test_set() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 5 );
    dynamic_array_push( da, 6 );

    dynamic_array_set( da, 0, 100 );
    dynamic_array_set( da, 1, 200 );

    TEST_ASSERT( dynamic_array_get( da, 0 ) == 100, "set index 0" );
    TEST_ASSERT( dynamic_array_get( da, 1 ) == 200, "set index 1" );

    dynamic_array_destroy( da );
}

// ============================================================================
// Front and Back Tests
// ============================================================================

void test_front_back() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 1 );
    dynamic_array_push( da, 2 );
    dynamic_array_push( da, 3 );

    TEST_ASSERT( dynamic_array_front( da ) == 1,
                 "front returns first element" );
    TEST_ASSERT( dynamic_array_back( da ) == 3, "back returns last element" );

    dynamic_array_destroy( da );
}

void test_front_back_single() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 42 );

    TEST_ASSERT( dynamic_array_front( da ) == 42,
                 "front equals back with single element" );
    TEST_ASSERT( dynamic_array_back( da ) == 42,
                 "back equals front with single element" );

    dynamic_array_destroy( da );
}

// ============================================================================
// Find Tests
// ============================================================================

void test_find_existing() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 0; i < 5; i++ ) { dynamic_array_push( da, i * 10 ); }

    TEST_ASSERT( dynamic_array_find( da, 0 ) == 0, "find first element" );
    TEST_ASSERT( dynamic_array_find( da, 20 ) == 2, "find middle element" );
    TEST_ASSERT( dynamic_array_find( da, 40 ) == 4, "find last element" );

    dynamic_array_destroy( da );
}

void test_find_not_found() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 5 );
    dynamic_array_push( da, 10 );

    TEST_ASSERT( dynamic_array_find( da, 999 ) == -1,
                 "find returns -1 for missing value" );

    dynamic_array_destroy( da );
}

void test_find_duplicates() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 1 );
    dynamic_array_push( da, 2 );
    dynamic_array_push( da, 1 );
    dynamic_array_push( da, 3 );

    TEST_ASSERT( dynamic_array_find( da, 1 ) == 0,
                 "find returns first occurrence" );

    dynamic_array_destroy( da );
}

// ============================================================================
// Fill Tests
// ============================================================================

void test_fill() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 0; i < 5; i++ ) { dynamic_array_push( da, i ); }

    dynamic_array_fill( da, 7 );

    for ( int i = 0; i < 5; i++ ) {
        TEST_ASSERT( da->buffer[i] == 7, "fill sets all elements to value" );
    }

    dynamic_array_destroy( da );
}

// ============================================================================
// Rotation Tests
// ============================================================================

void test_rotate_right() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 1; i <= 5; i++ ) { dynamic_array_push( da, i ); }

    dynamic_array_rotate_right( da );

    TEST_ASSERT( da->buffer[0] == 5, "rotate_right moves last to front" );
    TEST_ASSERT( da->buffer[1] == 1, "rotate_right shifts elements right" );
    TEST_ASSERT( da->buffer[4] == 4, "rotate_right maintains order" );

    dynamic_array_destroy( da );
}

void test_rotate_left() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 1; i <= 5; i++ ) { dynamic_array_push( da, i ); }

    dynamic_array_rotate_left( da );

    TEST_ASSERT( da->buffer[0] == 2, "rotate_left moves first to back" );
    TEST_ASSERT( da->buffer[3] == 5, "rotate_left shifts elements left" );
    TEST_ASSERT( da->buffer[4] == 1, "rotate_left moves first element to end" );

    dynamic_array_destroy( da );
}

void test_rotate_right_n() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 1; i <= 5; i++ ) { dynamic_array_push( da, i ); }

    dynamic_array_rotate_right_n( da, 2 );

    TEST_ASSERT( da->buffer[0] == 4, "rotate_right_n(2) rotates twice" );
    TEST_ASSERT( da->buffer[1] == 5, "rotate_right_n maintains order" );
    TEST_ASSERT( da->buffer[2] == 1, "rotate_right_n wraps correctly" );

    dynamic_array_destroy( da );
}

void test_rotate_left_n() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 1; i <= 5; i++ ) { dynamic_array_push( da, i ); }

    dynamic_array_rotate_left_n( da, 2 );

    TEST_ASSERT( da->buffer[0] == 3, "rotate_left_n(2) rotates twice" );
    TEST_ASSERT( da->buffer[3] == 1, "rotate_left_n wraps correctly" );
    TEST_ASSERT( da->buffer[4] == 2, "rotate_left_n maintains order" );

    dynamic_array_destroy( da );
}

void test_rotate_wrap_around() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 1; i <= 5; i++ ) { dynamic_array_push( da, i ); }

    // Rotating by size should return to original
    dynamic_array_rotate_right_n( da, 5 );

    TEST_ASSERT( da->buffer[0] == 1,
                 "rotate by full size returns to original" );
    TEST_ASSERT( da->buffer[4] == 5,
                 "rotate by full size preserves all elements" );

    dynamic_array_destroy( da );
}

// ============================================================================
// Clear and Destroy Tests
// ============================================================================

void test_clear() {
    struct dynamic_array *da = dynamic_array_create();
    for ( int i = 0; i < 10; i++ ) { dynamic_array_push( da, i ); }

    dynamic_array_clear( da );

    TEST_ASSERT( da->size == 0, "clear resets size" );
    TEST_ASSERT( da->capacity == 8, "clear resets capacity to default" );
    TEST_ASSERT( da->buffer != NULL, "clear reallocates buffer" );

    dynamic_array_clear( da );
}

// ============================================================================
// Edge Cases and Stress Tests
// ============================================================================

void test_negative_values() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, -100 );
    dynamic_array_push( da, -50 );
    dynamic_array_push( da, 0 );

    TEST_ASSERT( dynamic_array_get( da, 0 ) == -100,
                 "handles negative values" );
    TEST_ASSERT( dynamic_array_find( da, -50 ) == 1, "finds negative values" );

    dynamic_array_destroy( da );
}

void test_large_values() {
    struct dynamic_array *da = dynamic_array_create();
    dynamic_array_push( da, 2147483647 );  // INT_MAX
    dynamic_array_push( da, -2147483648 ); // INT_MIN

    TEST_ASSERT( dynamic_array_get( da, 0 ) == 2147483647, "handles INT_MAX" );
    TEST_ASSERT( dynamic_array_get( da, 1 ) == -2147483648, "handles INT_MIN" );

    dynamic_array_destroy( da );
}

void test_large_array() {
    struct dynamic_array *da    = dynamic_array_create();
    const int             COUNT = 1000;

    for ( int i = 0; i < COUNT; i++ ) { dynamic_array_push( da, i ); }

    TEST_ASSERT( da->size == COUNT, "handles large array" );
    TEST_ASSERT( dynamic_array_get( da, 0 ) == 0, "large array first element" );
    TEST_ASSERT( dynamic_array_get( da, COUNT - 1 ) == COUNT - 1,
                 "large array last element" );

    dynamic_array_destroy( da );
}

void test_expand() {
    struct dynamic_array *da       = dynamic_array_create();
    size_t                capacity = da->capacity;

    dynamic_array_expand( da );
    TEST_ASSERT( da->capacity == capacity * 2, "expand doubles capacity" );
    TEST_ASSERT( da->size == 0, "expand doesn't change size" );

    dynamic_array_destroy( da );
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main( void ) {
    printf( "Running Dynamic Array Test Suite\n" );
    printf( "================================\n\n" );

    printf( "Creation and Initialization:\n" );
    test_create_and_init();
    test_init_on_existing();

    printf( "\nPush and Pop:\n" );
    test_push_single();
    test_push_multiple();
    test_push_expansion();
    test_pop_single();
    test_pop_multiple();

    printf( "\nSize and Capacity:\n" );
    test_size_capacity_queries();
    test_empty();

    printf( "\nGet and Set:\n" );
    test_get();
    test_set();

    printf( "\nFront and Back:\n" );
    test_front_back();
    test_front_back_single();

    printf( "\nFind:\n" );
    test_find_existing();
    test_find_not_found();
    test_find_duplicates();

    printf( "\nFill:\n" );
    test_fill();

    printf( "\nRotation:\n" );
    test_rotate_right();
    test_rotate_left();
    test_rotate_right_n();
    test_rotate_left_n();
    test_rotate_wrap_around();

    printf( "\nClear and Destroy:\n" );
    test_clear();

    printf( "\nEdge Cases and Stress:\n" );
    test_negative_values();
    test_large_values();
    test_large_array();
    test_expand();

    printf( "\n================================\n" );
    printf( "Tests passed: %d/%d\n", tests_passed, tests_run );

    return ( tests_passed == tests_run ) ? EXIT_SUCCESS : EXIT_FAILURE;
}
