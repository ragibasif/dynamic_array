/*
 * File: dynamic_array.h
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

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Includes
 * ============================================================================
 */

#include <stddef.h>
#include <stdint.h>

/* ============================================================================
 * Macros and Constants
 * ============================================================================
 */

/* Version: Major.Minor.Patch (1 byte each: MMMM MMMM | NNNN NNNN | PPPP PPPP)
 */
#define DYNAMIC_ARRAY_VERSION_MAJOR 1
#define DYNAMIC_ARRAY_VERSION_MINOR 0
#define DYNAMIC_ARRAY_VERSION_PATCH 0

#define DYNAMIC_ARRAY_VERSION_NUM                                              \
    ( ( DYNAMIC_ARRAY_VERSION_MAJOR << 16 ) |                                  \
      ( DYNAMIC_ARRAY_VERSION_MINOR << 8 ) | DYNAMIC_ARRAY_VERSION_PATCH )

/* Bit masking macros to extract version components */
#define VERSION_GET_MAJOR( v ) ( ( v >> 16 ) & 0xFF )
#define VERSION_GET_MINOR( v ) ( ( v >> 8 ) & 0xFF )
#define VERSION_GET_PATCH( v ) ( v & 0xFF )

/* ============================================================================
 * Type Definitions
 * ============================================================================
 */

struct dynamic_array;

/* ============================================================================
 * Function Declarations
 * ============================================================================
 */

struct dynamic_array *dynamic_array_create( void );
void                  dynamic_array_destroy( struct dynamic_array *da );
void   dynamic_array_push( struct dynamic_array *da, const int data );
int    dynamic_array_pop( struct dynamic_array *da );
size_t dynamic_array_size( const struct dynamic_array *da );
size_t dynamic_array_capacity( const struct dynamic_array *da );
void   dynamic_array_fill( struct dynamic_array *da, const int data );
void   dynamic_array_expand( struct dynamic_array *da );
void   dynamic_array_rotate_right( struct dynamic_array *da );
void   dynamic_array_rotate_left( struct dynamic_array *da );
void   dynamic_array_rotate_right_n( struct dynamic_array *da, const int data );
void   dynamic_array_rotate_left_n( struct dynamic_array *da, const int data );
int    dynamic_array_get( const struct dynamic_array *da, const size_t index );
void   dynamic_array_set( const struct dynamic_array *da, const size_t index,
                          const int data );
void   dynamic_array_print( const struct dynamic_array *da );
void   dynamic_array_clear( struct dynamic_array *da );
int    dynamic_array_find( const struct dynamic_array *da, const int data );
int    dynamic_array_front( const struct dynamic_array *da );
int    dynamic_array_back( const struct dynamic_array *da );

#ifdef __cplusplus
}
#endif

#endif // DYNAMIC_ARRAY_H
