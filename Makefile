# File: Makefile
# Author: Ragib Asif
# Email: ragibasif@tuta.io
# GitHub: https://github.com/ragibasif
# LinkedIn: https://www.linkedin.com/in/ragibasif/
# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Ragib Asif
# Version 1.0.0
#

# Gets the Operating system name
OS := $(shell uname -s)

# Default shell
SHELL := bash


BINARY := program
BINDIR := bin
SRCDIR := src
LOGDIR := log
LIBDIR := lib
TESTDIR := test

CC := clang
CFLAGS := -std=c23 -O1 -g3 -DDEBUG=1 -pedantic -Wall -Wextra -Wvla -Wshadow -Wconversion -Wfloat-equal -Wswitch -Wimplicit-fallthrough -fno-sanitize-recover -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls -fstack-protector-all -Wstack-protector
DBG := lldb
LDFLAGS := # -lm  -I some/path/to/library

TEST_LIBS := #-l cmocka -L /usr/lib
TEST_BINARY := $(BINARY)_test_runner

SRCS := $(notdir $(basename $(wildcard $(SRCDIR)/*.c)))
OBJS :=$(patsubst %,$(LIBDIR)/%.o,$(SRCS))

.PHONY: default all clean help run check debug tests

default: all

# Rule for link and generate the binary file
all: $(OBJS)
	@echo "[LD] Linking...";
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(CFLAGS) $(LDFLAGS)

# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.c
	@echo "[CC] Compiling...";
	$(CC) -c $^ -o $@ $(CFLAGS) $(LDFLAGS)

# Compile tests and run the test binary
tests:
	@echo "make tests"
	@echo "[CC] Compiling..."
	$(CC) $(TESTDIR)/main.c -o $(BINDIR)/$(TEST_BINARY) $(CFLAGS) $(LDFLAGS) $(TEST_LIBS)
	@which ldconfig && ldconfig -C /tmp/ld.so.cache || true # caching the library linking
	@echo " Running $@: "
	./$(BINDIR)/$(TEST_BINARY)

clean:
	@echo "make clean"
	@rm -rvf $(BINDIR)/* $(LIBDIR)/* $(LOGDIR)/*

check:
	@echo "make check"
	@which $(CC) > /dev/null && echo "SUCCESS: $(CC) is installed" || echo "ERROR: $(CC) not found, please install $(CC)"
	@which $(DBG) > /dev/null && echo "SUCCESS: $(DBG) is installed" || echo "ERROR: $(DBG) not found, please install $(DBG)"

debug:
	@echo "make debug"
	@make clean
	@make all
	@$(DBG) ./$(BINDIR)/$(BINARY)

run:
	@echo "make run"
	@make clean
	@make all
	@./$(BINDIR)/$(BINARY)
	@make clean

help:
	@echo "make help"
	@echo "Makefile for building program"
	@echo "Usage:"
	@echo "  make             - Compiles and generates binary file program"
	@echo "  make all         - build program"
	@echo "  make check       - dependency check for compiler and debugger"
	@echo "  make tests       - Compiles and run tests binary file"
	@echo "  make clean       - remove binary files"
	@echo "  make debug       - run program with the debugger"
	@echo "  make run         - run program"
	@echo "  make help        - Prints a help message with target rules"
