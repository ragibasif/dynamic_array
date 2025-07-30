/*
 * File: dynamic_array.h
 * Author: Ragib Asif
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdlib.h>

struct dynamic_array {
    int   *buffer;
    size_t size;
    size_t capacity;
};

extern void da_init(struct dynamic_array *da);
extern void da_push(struct dynamic_array *da, int value);
extern void da_pop(struct dynamic_array *da);
extern void da_print(struct dynamic_array *da);
extern void da_cleanup(struct dynamic_array *da);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DYNAMIC_ARRAY_H_
