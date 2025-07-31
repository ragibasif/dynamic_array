/*
 * File: dynamic_array.c
 * Author: Ragib Asif
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "dynamic_array.h"

#include <stdbool.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Dynamic Array Internals Declarations
////////////////////////////////////////////////////////////////////////////////

static bool da_index_in_bounds_check_internal(struct dynamic_array *da,
                                              size_t                index);
static void da_expand_capacity_internal(struct dynamic_array *da);

static void da_alloc_check_internal(void *buffer, const size_t size,
                                    const char *file, const int line,
                                    const char *func);

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dynamic Array API Definitions
////////////////////////////////////////////////////////////////////////////////

void da_init(struct dynamic_array *da) {
    da->size     = 0;
    da->capacity = DEFAULT_CAPACITY_SIZE;
    da->buffer   = malloc(sizeof *da->buffer * da->capacity);
    da_alloc_check_internal(da->buffer, sizeof *da->buffer * da->capacity,
                            __FILE__, __LINE__, __func__);
}

void da_push(struct dynamic_array *da, int value) {
    if (da->size == da->capacity) {
        da_expand_capacity_internal(da);
    }
    da->buffer[da->size++] = value;
}

void da_pop(struct dynamic_array *da) {
    if (!(da->size > 0)) {
        return;
    }
    da->size--;
}

void da_print(struct dynamic_array *da) {
    if (!(da->size > 0)) {
        return;
    }
    for (size_t i = 0; i < da->size; i++) {
        printf("%d ", da->buffer[i]);
    }
    putchar('\n');
}

void da_cleanup(struct dynamic_array *da) {
    if (da->buffer) {
        free(da->buffer);
        da->buffer = NULL;
    }
    da->size     = 0;
    da->capacity = 0;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dynamic Array Internals Definitions
////////////////////////////////////////////////////////////////////////////////

static bool da_index_in_bounds_check_internal(struct dynamic_array *da,
                                              size_t                index) {
    if (index >= 0 && index < da->size) {
        return true;
    }
    fprintf(stderr, "Index Out Of Bounds Error: %zu is out of bounds of %zu.\n",
            index, da->size);
    return false;
}

static void da_expand_capacity_internal(struct dynamic_array *da) {
    da->capacity *= CAPACITY_GROWTH_FACTOR;
    int *buffer = realloc(da->buffer, sizeof *da->buffer * da->capacity);
    da_alloc_check_internal(buffer, sizeof *da->buffer * da->capacity, __FILE__,
                            __LINE__, __func__);
    da->buffer = buffer;
}

static void da_alloc_check_internal(void *buffer, const size_t size,
                                    const char *file, const int line,
                                    const char *func) {
    if (!buffer) {
        fprintf(stderr,
                "[%s:%u:(%s)] Memory allocation error. Failed to allocate %lu "
                "bytes to memory address %p.\n",
                file, line, func, size, (void *)buffer);
        exit(EXIT_FAILURE);
    }
}

////////////////////////////////////////////////////////////////////////////////
