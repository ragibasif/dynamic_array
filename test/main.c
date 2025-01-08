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
 *   Include detailed description of what this module does.
 *
 * Notes:
 *   - Any important implementation details or assumptions
 *   - Known limitations or edge cases
 *   - Performance considerations if applicable
 *
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ============================================================================
   TEST UTILITIES
   ============================================================================
 */

#define TEST_PASSED 1
#define TEST_FAILED 0

static int tests_run    = 0;
static int tests_passed = 0;

#define assert_equal( a, b, msg )                                              \
    do {                                                                       \
        if ( ( a ) != ( b ) ) {                                                \
            fprintf( stderr, "FAIL: %s (expected %zu, got %zu)\n", msg,        \
                     (size_t)( b ), (size_t)( a ) );                           \
            return TEST_FAILED;                                                \
        }                                                                      \
    } while ( 0 )

#define assert_true( cond, msg )                                               \
    do {                                                                       \
        if ( !( cond ) ) {                                                     \
            fprintf( stderr, "FAIL: %s\n", msg );                              \
            return TEST_FAILED;                                                \
        }                                                                      \
    } while ( 0 )

#define assert_not_null( ptr, msg )                                            \
    do {                                                                       \
        if ( ( ptr ) == NULL ) {                                               \
            fprintf( stderr, "FAIL: %s (expected non-NULL)\n", msg );          \
            return TEST_FAILED;                                                \
        }                                                                      \
    } while ( 0 )

#define assert_within( a, b, tolerance, msg )                                  \
    do {                                                                       \
        if ( ( a ) < ( b ) - ( tolerance ) ||                                  \
             ( a ) > ( b ) + ( tolerance ) ) {                                 \
            fprintf( stderr, "FAIL: %s (expected ~%zu, got %zu)\n", msg,       \
                     (size_t)( b ), (size_t)( a ) );                           \
            return TEST_FAILED;                                                \
        }                                                                      \
    } while ( 0 )

#define RUN_TEST( test_func )                                                  \
    do {                                                                       \
        tests_run++;                                                           \
        if ( test_func() ) {                                                   \
            tests_passed++;                                                    \
            printf( "✓ %s\n", #test_func );                                    \
        }                                                                      \
    } while ( 0 )

/* ============================================================================
   BENCHMARK UTILITIES
   ============================================================================
 */

struct benchmark {
    const char *name;
    double      time_ms;
    size_t      ops;
};

double get_time_ms( void ) {
    struct timespec ts;
    clock_gettime( CLOCK_MONOTONIC, &ts );
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;
}

void print_bench_result( struct benchmark result ) {
    double ops_per_sec = ( result.ops / result.time_ms ) * 1000.0;
    printf( "  %-45s: %10.3f ms (%12.0f ops/sec)\n", result.name,
            result.time_ms, ops_per_sec );
}

int main( void ) { return EXIT_SUCCESS; }
