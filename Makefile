# File: Makefile
# Author: Ragib Asif
# Email: ragibasif@tuta.io
# GitHub: https://github.com/ragibasif
# LinkedIn: https://www.linkedin.com/in/ragibasif/
# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Ragib Asif
# Version 1.0.0
#

SRC_DIR := src
BUILD_DIR := build
MAIN := $(SRC_DIR)/main.c

CC := clang
CFLAGS := -std=c23 \
		  -pedantic -Wall -Wextra -Wvla -Wshadow \
		  -Wconversion -Wfloat-equal -Wswitch -Wimplicit-fallthrough \
		  -fno-sanitize-recover -fsanitize=address -fsanitize=undefined \
		  -fno-omit-frame-pointer -fno-optimize-sibling-calls \
		  -fstack-protector-all -Wstack-protector \
		  -MMD -MP \
		  -g3 -O0 -DDEBUG=1

LDFLAGS := # -lm  -I some/path/to/library


SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET := $(BUILD_DIR)/program

.PHONY: default
default: all

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	@make clean
	@make all
	./$(TARGET)
	@make clean

.PHONY: clean
clean:
	@rm -rvf $(BUILD_DIR)

