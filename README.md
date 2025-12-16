# Dynamic Array

**Dynamic Array** is a pure C library that provides a resizable array implementation.
It dynamically allocates and manages memory, automatically expanding capacity as
needed. Perfect for learning data structures, building C projects, or comparing
dynamic array implementations across languages.

- Inspired by C++ STL `std::vector`
- Educational purpose: learn how vectors work under the hood
- Not recommended for production without additional error handling

## Features

- **Automatic Memory Management** — Array automatically expands when capacity is exceeded
- **Safety Checks** — Built-in assertions and memory sanitizers catch errors during development
- **Rich API** — Over 20 functions for manipulation, searching, and iteration
- **Zero-Copy Operations** — Efficient element access via pointers
- **Rotation Support** — In-place rotation operations with optimization
- **Search Optimization** — Transposition search for frequently accessed elements
- **Modern Compilation** — C23 standard with strict warnings enabled

## Building

### Prerequisites

- `clang` (or any C23-compliant compiler)
- `make`
- `lldb` (for debugging, optional)

### Quick Start

```bash
# Build the project
make all

# Run tests
make test

# Run with debug output
make debug

# Clean build artifacts
make clean
```

### Build Targets

| Command      | Purpose                                      |
| ------------ | -------------------------------------------- |
| `make all`   | Compile the main program (debug mode)        |
| `make test`  | Compile and run the comprehensive test suite |
| `make run`   | Clean, compile, run, and cleanup             |
| `make debug` | Launch interactive debugger with tests       |
| `make clean` | Remove all build artifacts                   |

## Project Structure

```
.
├── src/
│   ├── dynamic_array.h       # Public API header
│   └── dynamic_array.c       # Implementation
├── tests/
│   └── main.c                # Comprehensive test suite
├── build/                    # Build artifacts (generated)
├── Makefile                  # Build configuration
└── README.md                 # This file
```

## API Reference

### Core Operations

#### `struct dynamic_array *dynamic_array_create(void)`

Allocates and initializes a new dynamic array with default capacity (8 elements).

```c
struct dynamic_array *da = dynamic_array_create();
```

#### `void dynamic_array_init(struct dynamic_array *da)`

Initializes an existing dynamic array struct. Useful for stack-allocated arrays.

```c
struct dynamic_array da;
dynamic_array_init(&da);
```

#### `void dynamic_array_destroy(struct dynamic_array *da)`

Frees all memory associated with the array and the array structure itself.

```c
dynamic_array_destroy(da);
```

#### `void dynamic_array_clear(struct dynamic_array *da)`

Resets the array to empty state, reallocating to default capacity.

```c
dynamic_array_clear(da);
```

### Adding and Removing Elements

#### `void dynamic_array_push(struct dynamic_array *da, const int value)`

Appends a value to the end. Automatically expands if needed.

```c
dynamic_array_push(da, 42);
dynamic_array_push(da, -17);
```

#### `int dynamic_array_pop(struct dynamic_array *da)`

Removes and returns the last element. Asserts if array is empty.

```c
int last = dynamic_array_pop(da);
```

#### `void dynamic_array_insert(struct dynamic_array *da, const size_t index, const int value)`

Inserts a value at the specified index, shifting subsequent elements right. **O(n) time complexity.**

```c
dynamic_array_insert(da, 2, 100);  // Insert 100 at index 2
```

#### `int dynamic_array_remove(struct dynamic_array *da, const size_t index)`

Removes and returns the element at the specified index, shifting subsequent elements left. **O(n) time complexity.**

```c
int removed = dynamic_array_remove(da, 2);
```

### Accessing Elements

#### `int dynamic_array_get(const struct dynamic_array *da, const size_t index)`

Returns the element at the specified index.

```c
int value = dynamic_array_get(da, 5);
```

#### `void dynamic_array_set(const struct dynamic_array *da, const size_t index, const int value)`

Sets the element at the specified index.

```c
dynamic_array_set(da, 5, 999);
```

#### `int dynamic_array_front(const struct dynamic_array *da)`

Returns the first element. Asserts if array is empty.

```c
int first = dynamic_array_front(da);
```

#### `int dynamic_array_back(const struct dynamic_array *da)`

Returns the last element. Asserts if array is empty.

```c
int last = dynamic_array_back(da);
```

### Queries

#### `size_t dynamic_array_size(const struct dynamic_array *da)`

Returns the current number of elements.

```c
size_t count = dynamic_array_size(da);
```

#### `size_t dynamic_array_capacity(const struct dynamic_array *da)`

Returns the current allocated capacity.

```c
size_t cap = dynamic_array_capacity(da);
```

#### `bool dynamic_array_empty(const struct dynamic_array *da)`

Returns true if the array contains no elements.

```c
if (dynamic_array_empty(da)) {
    printf("Array is empty\n");
}
```

### Searching

#### `int dynamic_array_find(const struct dynamic_array *da, const int value)`

Returns the index of the first occurrence of the value, or -1 if not found. **O(n) time complexity.**

```c
int index = dynamic_array_find(da, 42);
if (index != -1) {
    printf("Found at index %d\n", index);
}
```

#### `int dynamic_array_find_transposition(struct dynamic_array *da, int value)`

Searches for a value and moves it one position toward the front (self-optimizing). Useful for frequently accessed elements. **O(n) time complexity.**

```c
int index = dynamic_array_find_transposition(da, frequently_used_value);
```

### Bulk Operations

#### `void dynamic_array_fill(struct dynamic_array *da, const int value)`

Sets all elements to the specified value.

```c
dynamic_array_fill(da, 0);  // Fill with zeros
```

#### `void dynamic_array_print(const struct dynamic_array *da)`

Prints all elements to stdout, space-separated.

```c
dynamic_array_print(da);  // Output: 1 2 3 4 5
```

### Memory Management

#### `void dynamic_array_expand(struct dynamic_array *da)`

Manually doubles the array's capacity. Called automatically by push/insert operations.

```c
dynamic_array_expand(da);
```

### Rotation Operations

All rotation operations are **O(n) time complexity.**

#### `void dynamic_array_rotate_right(struct dynamic_array *da)`

Rotates all elements one position to the right. Last element wraps to front.

```c
// [1, 2, 3, 4, 5] → [5, 1, 2, 3, 4]
dynamic_array_rotate_right(da);
```

#### `void dynamic_array_rotate_left(struct dynamic_array *da)`

Rotates all elements one position to the left. First element wraps to back.

```c
// [1, 2, 3, 4, 5] → [2, 3, 4, 5, 1]
dynamic_array_rotate_left(da);
```

#### `void dynamic_array_rotate_right_n(struct dynamic_array *da, int count)`

Rotates right by n positions. Optimized to avoid redundant rotations.

```c
dynamic_array_rotate_right_n(da, 3);  // Rotate right 3 times
```

#### `void dynamic_array_rotate_left_n(struct dynamic_array *da, int count)`

Rotates left by n positions. Optimized to avoid redundant rotations.

```c
dynamic_array_rotate_left_n(da, 3);  // Rotate left 3 times
```

## Usage Example

```c
#include "dynamic_array.h"
#include <stdio.h>

int main(void) {
    // Create and populate
    struct dynamic_array *da = dynamic_array_create();

    for (int i = 1; i <= 5; i++) {
        dynamic_array_push(da, i * 10);
    }

    // Access elements
    printf("First: %d\n", dynamic_array_front(da));
    printf("Last: %d\n", dynamic_array_back(da));
    printf("Size: %zu\n", dynamic_array_size(da));

    // Search
    int idx = dynamic_array_find(da, 30);
    if (idx != -1) {
        printf("Found 30 at index %d\n", idx);
    }

    // Modify
    dynamic_array_set(da, 2, 999);

    // Print all
    printf("Array contents: ");
    dynamic_array_print(da);

    // Rotate
    dynamic_array_rotate_left(da);
    printf("After left rotation: ");
    dynamic_array_print(da);

    // Cleanup
    dynamic_array_destroy(da);

    return 0;
}
```

## Compilation Features

The Makefile is configured with comprehensive safety and debugging features:

### Compiler Flags

- **Standard**: C23 with pedantic mode enabled
- **Warnings**: Extensive warnings including:
  - Implicit fallthrough detection
  - Shadow variable detection
  - Write string protection
  - Stack protector
- **Sanitizers**: Address and undefined behavior sanitizers catch memory errors at runtime
- **Debug Info**: Full debug symbols with frame pointers preserved

### Debug Macros

Control compilation behavior with `-DFLAG=1`:

- `-DDEBUG=1` — Enable debug assertions and verbose output
- `-DTEST=1` — Enable test-specific code paths
- `-DINTERNAL=1` — Enable internal diagnostic code

## Testing

The project includes a comprehensive test suite with 40+ tests covering:

- **Core Operations** — Create, init, destroy, clear
- **Push/Pop** — Single/multiple operations, capacity expansion
- **Access Patterns** — Get, set, front, back
- **Searching** — Finding elements, handling duplicates
- **Transformations** — Rotate operations, filling, transposition search
- **Edge Cases** — Negative values, INT_MAX/INT_MIN, large arrays (1000+ elements)
- **Stress Testing** — High-capacity arrays, repeated operations

Run tests with:

```bash
make test
```

Example output:

```
Running Dynamic Array Test Suite
================================

Creation and Initialization:
✓ create returns non-NULL pointer
✓ new array has size 0
✓ new array has default capacity 8
...

================================
Tests passed: 40/40
```

## Debugging

### Interactive Debugging

Launch the test suite in the debugger:

```bash
make debug
```

### Common LLDB Commands

```lldb
break main                    # Set breakpoint at main
break dynamic_array_push      # Break on function
continue                      # Resume execution
step                         # Step into functions
next                         # Step over functions
print da->size               # Inspect variables
print *da->buffer@10         # Print array of 10 elements
backtrace                    # View call stack
quit                         # Exit debugger
```

## Known Limitations and TODO Items

### Current Limitations

- **Fixed Integer Type** — Currently only supports `int` elements (see TODO: "Convert hard coded int type to generic")
- **No Bounds Checking in Release** — Bounds checks are assertions (compile-time removed)
- **Pop on Empty** — Undefined behavior in release mode (caught in debug)

### Planned Improvements

- [ ] Add `reserve(size_t n)` — Pre-allocate capacity without changing size
- [ ] Add `shrink_to_fit()` — Reduce capacity to match actual size
- [ ] Convert to generic type support (macro-based or templates)
- [ ] Add comprehensive error codes and error handling for release mode
- [ ] Add runtime bounds checking (not assertion-based)
- [ ] Add helper validation functions for indices, sizes, pointers
- [ ] Add detailed usage documentation and code examples

## Performance Characteristics

| Operation | Time Complexity | Space Complexity |
| --------- | --------------- | ---------------- |
| Push      | O(1) amortized  | O(n) total       |
| Pop       | O(1)            | —                |
| Get/Set   | O(1)            | —                |
| Find      | O(n)            | O(1)             |
| Insert    | O(n)            | —                |
| Remove    | O(n)            | —                |
| Rotate    | O(n)            | O(1)             |
| Expand    | O(n)            | —                |

## Memory Safety

The implementation includes multiple layers of memory safety:

1. **Address Sanitizer** — Detects buffer overflows, use-after-free
2. **Undefined Behavior Sanitizer** — Catches undefined behaviors
3. **Assertions** — Development-time bounds checking
4. **Stack Protection** — Detects stack buffer overflows
5. **Frame Pointers** — Full stack traces for debugging

## Contributing

When modifying this code:

1. Maintain the strict compiler flags
2. Add tests for any new functionality
3. Ensure all tests pass: `make test`
4. Run through the debugger for complex changes: `make debug`

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
