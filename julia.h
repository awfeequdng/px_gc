#pragma once
#include <stddef.h>
#include <dtypes.h>

#include "htable.h"
#include "arraylist.h"

#define JL_STRUCT_TYPE \
    struct _jl_type_t *type;

typedef struct _jl_value_t {
    JL_STRUCT_TYPE
} jl_value_t;


// pseudo-object to track managed malloc pointers
// currently only referenced from an array's data owner field
typedef struct _jl_mallocptr_t {
    struct _jl_mallocptr_t *next;
    size_t sz;
    void *ptr;
} jl_mallocptr_t;

typedef struct {
    JL_STRUCT_TYPE
    jl_value_t *value;
} jl_weakref_t;

typedef struct _jl_type_t {
    JL_STRUCT_TYPE
} jl_type_t;

typedef struct {
    JL_STRUCT_TYPE
} jl_bits_type_t;


typedef jl_value_t *(*jl_fptr_t)(jl_value_t*, jl_value_t**, uint32_t);

#define JL_FUNC_FIELDS                          \
    jl_fptr_t fptr;                             \
    jl_value_t *env;

typedef struct {
    JL_STRUCT_TYPE
    JL_FUNC_FIELDS
    uint32_t size;
} jl_struct_type_t;


typedef struct {
    JL_STRUCT_TYPE
    JL_FUNC_FIELDS
} jl_function_t;


static inline
jl_value_t *jl_apply(jl_function_t *f, jl_value_t **args, uint32_t nargs)
{
    return f->fptr((jl_value_t*)f, args, nargs);
}


typedef struct {
    JL_STRUCT_TYPE
    size_t length;
    jl_value_t *data[1];
} jl_tuple_t;
jl_tuple_t *jl_tuple2(void *a, void *b);

#define jl_tupleref(t,i) (((jl_value_t**)(t))[2+(i)])
#define jl_tupleset(t,i,x) ((((jl_value_t**)(t))[2+(i)])=(jl_value_t*)(x))
#define jl_t0(t) jl_tupleref(t,0)
#define jl_t1(t) jl_tupleref(t,1)

#define jl_tuple_len(t)   (((jl_tuple_t*)(t))->length)
#define jl_tuple_set_len_unsafe(t,n) (((jl_tuple_t*)(t))->length=(n))

extern jl_value_t *jl_true;
extern jl_value_t *jl_false;

extern jl_bits_type_t *jl_bool_type;
extern jl_bits_type_t *jl_char_type;
extern jl_bits_type_t *jl_int8_type;
extern jl_bits_type_t *jl_uint8_type;
extern jl_bits_type_t *jl_int16_type;
extern jl_bits_type_t *jl_uint16_type;
extern jl_bits_type_t *jl_int32_type;
extern jl_bits_type_t *jl_uint32_type;
extern jl_bits_type_t *jl_int64_type;
extern jl_bits_type_t *jl_uint64_type;
extern jl_bits_type_t *jl_float32_type;
extern jl_bits_type_t *jl_float64_type;
extern jl_struct_type_t *jl_weakref_type;
extern jl_value_t *jl_nothing;
extern jl_tuple_t *jl_null;

extern jl_struct_type_t *jl_function_type;
extern jl_struct_type_t *jl_struct_kind;
extern jl_struct_type_t *jl_bits_kind;
extern jl_tuple_t *jl_tuple_type;

extern jl_value_t *jl_memory_exception;


#define jl_is_struct_type(v) jl_typeis(v,jl_struct_kind)

#define jl_typeof(v) (((jl_value_t*)(v))->type)
#define jl_typeis(v,t) (jl_typeof(v)==(jl_type_t*)(t))
#define jl_is_func(v)        (jl_typeis(v,jl_function_type) || jl_is_struct_type(v))
#define jl_is_function(v)    jl_is_func(v)
#define jl_is_tuple(v)       jl_typeis(v,jl_tuple_type)



#define JL_TRY

#define JL_CATCH
