SRC_DIR := src
TEST_DIR := tests
BUILD_DIR := build

CC := clang
CFLAGS := -std=c23 \
		  -pedantic -Wall -Wextra -Wvla -Wshadow \
		  -Wno-unused-parameter -Wwrite-strings -Wstrict-prototypes \
		  -Wredundant-decls -Wnested-externs \
		  -Wmissing-include-dirs \
		  -Wconversion -Wfloat-equal -Wswitch -Wimplicit-fallthrough \
		  -fno-sanitize-recover -fsanitize=address -fsanitize=undefined \
		  -fno-omit-frame-pointer -fno-optimize-sibling-calls \
		  -fstack-protector-all -Wstack-protector \
		  -MMD -MP

CFLAGS_DEBUG := -g3 -O0 -DDEBUG=1
CFLAGS_TEST := -DTEST=1
LDFLAGS :=

DEBUGGER := lldb

SOURCES := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.c)

OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SOURCES))

TARGET := $(BUILD_DIR)/program
TEST_TARGET := $(BUILD_DIR)/test

DEPS := $(OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: default all test run debug clean

.PHONY: default
default: all

.PHONY: all
all: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	@$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -o $@ $(OBJECTS) $(LDFLAGS)

.PHONY: test
test: $(BUILD_DIR) $(OBJECTS) $(TEST_OBJECTS)
	@$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_TEST) -o $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS) $(LDFLAGS)
	@./$(TEST_TARGET)
	@make clean

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_TEST) -c $< -o $@

.PHONY: run
run:
	@make clean
	@make all
	@./$(TARGET)
	@make clean

.PHONY: debug
debug: $(BUILD_DIR) $(OBJECTS) $(TEST_OBJECTS)
	@$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_TEST) -o $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS) $(LDFLAGS)
	@$(DEBUGGER) ./$(TEST_TARGET)


.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

-include $(DEPS)


# debugger
# run — start the program
# break main — set a breakpoint
# continue — resume execution
# step / next — step through code
# print var — inspect variables
# quit — exit debugger
