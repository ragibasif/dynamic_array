#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct dynamic_array {
    int   *buffer;
    size_t size;
    size_t capacity;
};

extern struct dynamic_array *dynamic_array_create( void );
extern void                  dynamic_array_init( struct dynamic_array *da );
extern void                  dynamic_array_clear( struct dynamic_array *da );
extern void                  dynamic_array_destroy( struct dynamic_array *da );
extern void   dynamic_array_push( struct dynamic_array *da, const int value );
extern int    dynamic_array_pop( struct dynamic_array *da );
extern size_t dynamic_array_size( const struct dynamic_array *da );
extern size_t dynamic_array_capacity( const struct dynamic_array *da );
extern bool   dynamic_array_empty( const struct dynamic_array *da );
extern void   dynamic_array_fill( struct dynamic_array *da, const int value );
extern void   dynamic_array_expand( struct dynamic_array *da );
extern void   dynamic_array_rotate_right( struct dynamic_array *da );
extern void   dynamic_array_rotate_left( struct dynamic_array *da );
extern void   dynamic_array_rotate_right_n( struct dynamic_array *da,
                                            const int             value );
extern void   dynamic_array_rotate_left_n( struct dynamic_array *da,
                                           const int             value );
extern int    dynamic_array_get( const struct dynamic_array *da,
                                 const size_t                index );
extern void   dynamic_array_set( const struct dynamic_array *da,
                                 const size_t index, const int value );
extern void   dynamic_array_print( const struct dynamic_array *da );
extern int    dynamic_array_find( const struct dynamic_array *da,
                                  const int                   value );
extern int    dynamic_array_front( const struct dynamic_array *da );
extern int    dynamic_array_back( const struct dynamic_array *da );

#ifdef __cplusplus
}
#endif

#endif // DYNAMIC_ARRAY_H
