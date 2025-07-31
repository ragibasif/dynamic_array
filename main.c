/*
 * File: main.c
 * Author: Ragib Asif
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "dynamic_array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void test_stack_allocation(void) {
    puts(__func__);
    struct dynamic_array da;
    da_init(&da);
    assert(da.size == 0);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE);
    da_cleanup(&da);
    assert(da.size == 0);
    assert(da.capacity == 0);
    assert(!da.buffer);
}

static void test_heap_allocation(void) {
    puts(__func__);
    struct dynamic_array *da = malloc(sizeof *da);
    da_init(da);
    assert(da->size == 0);
    assert(da->capacity == DEFAULT_CAPACITY_SIZE);
    da_cleanup(da);
    assert(da->size == 0);
    assert(da->capacity == 0);
    assert(!da->buffer);
    free(da);
    da = NULL;
}

static void test_push(void) {
    puts(__func__);
    struct dynamic_array da;
    da_init(&da);
    assert(da.size == 0);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE);

    da_push(&da, 0xff);
    assert(da.buffer[0] == 0xff);
    assert(da.size == 1);
    da_push(&da, 0x00);
    assert(da.buffer[1] == 0x00);
    assert(da.size == 2);
    da_push(&da, 0x2f);
    assert(da.buffer[2] == 0x2f);
    assert(da.size == 3);
    da_push(&da, 0x9a);
    assert(da.buffer[3] == 0x9a);
    assert(da.size == 4);
    da_push(&da, 0x10);
    assert(da.buffer[4] == 0x10);
    assert(da.size == 5);
    da_push(&da, 0x6b);
    assert(da.buffer[5] == 0x6b);
    assert(da.size == 6);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE);

    da_cleanup(&da);
    assert(da.size == 0);
    assert(da.capacity == 0);
    assert(!da.buffer);
}

static void test_pop(void) {

    puts(__func__);
    struct dynamic_array da;
    da_init(&da);
    assert(da.size == 0);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE);

    da_push(&da, 0xff);
    assert(da.buffer[0] == 0xff);
    assert(da.size == 1);
    da_push(&da, 0x00);
    assert(da.buffer[1] == 0x00);
    assert(da.size == 2);
    da_push(&da, 0x2f);
    assert(da.buffer[2] == 0x2f);
    assert(da.size == 3);
    da_push(&da, 0x9a);
    assert(da.buffer[3] == 0x9a);
    assert(da.size == 4);
    da_push(&da, 0x10);
    assert(da.buffer[4] == 0x10);
    assert(da.size == 5);
    da_push(&da, 0x6b);
    assert(da.buffer[5] == 0x6b);
    assert(da.size == 6);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE);

    da_pop(&da);
    assert(da.size == 5);
    da_pop(&da);
    assert(da.size == 4);
    da_pop(&da);
    assert(da.size == 3);
    da_pop(&da);
    assert(da.size == 2);
    da_pop(&da);
    assert(da.size == 1);
    da_pop(&da);
    assert(da.size == 0);

    assert(da.capacity == DEFAULT_CAPACITY_SIZE);

    da_cleanup(&da);
    assert(da.size == 0);
    assert(da.capacity == 0);
    assert(!da.buffer);
}

static void test_array_expansion(void) {

    puts(__func__);
    struct dynamic_array da;
    da_init(&da);
    assert(da.size == 0);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE);

    for (size_t i = 0; i < DEFAULT_CAPACITY_SIZE * 4; i++) {
        da_push(&da, 1 < i);
    }

    assert(da.capacity != DEFAULT_CAPACITY_SIZE);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE * 4);

    for (size_t i = 0; i < DEFAULT_CAPACITY_SIZE * 4; i++) {
        da_pop(&da);
    }
    assert(da.capacity != DEFAULT_CAPACITY_SIZE);
    assert(da.capacity == DEFAULT_CAPACITY_SIZE * 4);

    da_cleanup(&da);
    assert(da.size == 0);
    assert(da.capacity == 0);
    assert(!da.buffer);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

    test_stack_allocation();
    test_heap_allocation();
    test_push();
    test_pop();
    test_array_expansion();

    return EXIT_SUCCESS;
}
