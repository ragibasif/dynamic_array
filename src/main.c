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

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main( [[maybe_unused]] int argc, [[maybe_unused]] char **argv ) {
    struct dynamic_array *da;
    da = dynamic_array_create();
    for ( int i = 0; i < 10; i++ ) { dynamic_array_push( da, i ); }
    dynamic_array_print( da );
    dynamic_array_destroy( da );
    return EXIT_SUCCESS;
}
