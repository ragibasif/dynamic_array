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

#include "dynamic_array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv ) {
    (void)argc; /* Suppress unused parameter warning */
    (void)argv;

    struct dynamic_array *da = dynamic_array_create();
    assert( da != NULL );

    for ( int i = 0; i < 10; i++ ) { dynamic_array_push( da, ( i + 1 ) << 1 ); }

    dynamic_array_print( da );

    dynamic_array_destroy( da );
    da = NULL;

    return EXIT_SUCCESS;
}
