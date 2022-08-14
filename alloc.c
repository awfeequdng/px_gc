#include "julia.h"
#include "newobj_internal.h"

#include <stdarg.h>

jl_tuple_t *jl_tuple(size_t n, ...)
{
    va_list args;
    size_t i;
    if (n == 0) return jl_null;
    va_start(args, n);
    jl_tuple_t *jv = (jl_tuple_t*)newobj((jl_type_t*)jl_tuple_type, n+1);
    jl_tuple_set_len_unsafe(jv, n);
    for(i=0; i < n; i++) {
        jl_tupleset(jv, i, va_arg(args, jl_value_t*));
    }
    va_end(args);
    return jv;
}

jl_tuple_t *jl_tuple1(void *a)
{
    jl_tuple_t *t = (jl_tuple_t*)alloc_3w();
    t->type = (jl_type_t*)jl_tuple_type;
    jl_tuple_set_len_unsafe(t, 1);
    jl_tupleset(t, 0, a);
    return t;
}

jl_tuple_t *jl_tuple2(void *a, void *b)
{
    jl_tuple_t *t = (jl_tuple_t*)alloc_4w();
    t->type = (jl_type_t*)jl_tuple_type;
    jl_tuple_set_len_unsafe(t, 2);
    jl_tupleset(t, 0, a);
    jl_tupleset(t, 1, b);
    return t;
}

jl_tuple_t *jl_alloc_tuple_uninit(size_t n)
{
    if (n == 0) return jl_null;
    jl_tuple_t *jv = (jl_tuple_t*)newobj((jl_type_t*)jl_tuple_type, n+1);
    jl_tuple_set_len_unsafe(jv, n);
    return jv;
}

jl_tuple_t *jl_alloc_tuple(size_t n)
{
    if (n == 0) return jl_null;
    jl_tuple_t *jv = jl_alloc_tuple_uninit(n);
    size_t i;
    for(i=0; i < n; i++) {
        jl_tupleset(jv, i, NULL);
    }
    return jv;
}

jl_tuple_t *jl_tuple_append(jl_tuple_t *a, jl_tuple_t *b)
{
    jl_tuple_t *c = jl_alloc_tuple_uninit(jl_tuple_len(a) + jl_tuple_len(b));
    size_t i=0, j;
    for(j=0; j < jl_tuple_len(a); j++) {
        jl_tupleset(c, i, jl_tupleref(a,j));
        i++;
    }
    for(j=0; j < jl_tuple_len(b); j++) {
        jl_tupleset(c, i, jl_tupleref(b,j));
        i++;
    }
    return c;
}

jl_tuple_t *jl_tuple_fill(size_t n, jl_value_t *v)
{
    if (n==0) return jl_null;
    jl_tuple_t *tup = jl_alloc_tuple_uninit(n);
    size_t i;
    for(i=0; i < n; i++) {
        jl_tupleset(tup, i, v);
    }
    return tup;
}


void jl_unmark_symbols(void) {
    // unmark_symbols_(symtab);
}