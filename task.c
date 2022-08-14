
#include <stdio.h>
#include "julia.h"
#include "gc.h"
#include <stdlib.h>

jl_gcframe_t *jl_pgcstack = NULL;

// record backtrace and raise an error
void jl_throw(jl_value_t *e)
{
    printf("throw %p\n", e);
    exit(-1);
}