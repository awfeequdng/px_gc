#pragma once

#include "julia.h"
#include "dtypes.h"

#define BVOFFS 2
#define GC_PAGE_SZ (1536*sizeof(void*))     //bytes


typedef struct _gcpage_t {
    char data[GC_PAGE_SZ];
    union {
        struct _gcpage_t *next;
        char _pad[8];
    };
} gcpage_t;

typedef struct _gcval_t {
    union {
        struct _gcval_t *next;
        uptrint_t flags;
        uptrint_t data0;    // overlapped
        uptrint_t marked:1;
    };
} gcval_t;

typedef struct _pool_t {
    size_t osize;
    gcpage_t *pages;
    gcval_t *freelist;
} pool_t;

typedef struct _bigval_t {
    struct _bigval_t *next;
    size_t sz;
    union {
        uptrint_t flags;
        uptrint_t marked:1;
        char _data[1];
    };
} bigval_t;

#define gc_marked(o)  (((gcval_t*)(o))->marked)
#define gc_setmark(o) (((gcval_t*)(o))->marked=1)
#define gc_val_buf(o) ((gcval_t*)(((void**)(o))-1))
#define gc_setmark_buf(o) gc_setmark(gc_val_buf(o))




typedef struct _jl_gcframe_t {
    size_t nroots;
    struct _jl_gcframe_t *prev;
    // actual roots go here
} jl_gcframe_t;

// NOTE: it is the caller's responsibility to make sure arguments are
// rooted. foo(f(), g()) will not work, and foo can't do anything about it,
// so the caller must do
// jl_value_t *x=NULL, *y=NULL; JL_GC_PUSH(&x, &y);
// x = f(); y = g(); foo(x, y)

extern jl_gcframe_t *jl_pgcstack;

#define JL_GC_PUSH(...)                                                   \
  void *__gc_stkf[] = {(void*)((VA_NARG(__VA_ARGS__)<<1)|1), jl_pgcstack, \
                       __VA_ARGS__};                                      \
  jl_pgcstack = (jl_gcframe_t*)__gc_stkf;

#define JL_GC_PUSHARGS(rts_var,n)                               \
  rts_var = ((jl_value_t**)alloca(((n)+2)*sizeof(jl_value_t*)))+2;    \
  ((void**)rts_var)[-2] = (void*)(((size_t)n)<<1);              \
  ((void**)rts_var)[-1] = jl_pgcstack;                          \
  jl_pgcstack = (jl_gcframe_t*)&(((void**)rts_var)[-2])

#define JL_GC_POP() (jl_pgcstack = jl_pgcstack->prev)

void jl_gc_init(void);
void jl_gc_setmark(jl_value_t *v);
void jl_gc_enable(void);
void jl_gc_disable(void);
int jl_gc_is_enabled(void);
void jl_gc_ephemeral_on(void);
void jl_gc_ephemeral_off(void);
void jl_gc_collect(void);
void jl_gc_preserve(jl_value_t *v);
void jl_gc_unpreserve(void);
int jl_gc_n_preserved_values(void);
void jl_gc_add_finalizer(jl_value_t *v, jl_function_t *f);
jl_weakref_t *jl_gc_new_weakref(jl_value_t *value);
jl_mallocptr_t *jl_gc_acquire_buffer(void *b, size_t sz);
jl_mallocptr_t *jl_gc_managed_malloc(size_t sz);
void *alloc_2w(void);
void *alloc_3w(void);
void *alloc_4w(void);



void jl_gc_init(void);