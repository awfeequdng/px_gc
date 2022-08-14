#include "julia.h"


jl_value_t *jl_true;
jl_value_t *jl_false;

jl_bits_type_t *jl_bool_type;
jl_bits_type_t *jl_char_type;
jl_bits_type_t *jl_int8_type;
jl_bits_type_t *jl_uint8_type;
jl_bits_type_t *jl_int16_type;
jl_bits_type_t *jl_uint16_type;
jl_bits_type_t *jl_int32_type;
jl_bits_type_t *jl_uint32_type;
jl_bits_type_t *jl_int64_type;
jl_bits_type_t *jl_uint64_type;
jl_bits_type_t *jl_float32_type;
jl_bits_type_t *jl_float64_type;
jl_struct_type_t *jl_weakref_type;
jl_value_t *jl_nothing;
jl_tuple_t *jl_null;

jl_struct_type_t *jl_function_type;
jl_struct_type_t *jl_struct_kind;
jl_struct_type_t *jl_bits_kind;
jl_tuple_t *jl_tuple_type;

jl_value_t *jl_memory_exception;