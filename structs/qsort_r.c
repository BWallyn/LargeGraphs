#include <stdlib.h>

#include "qsort_r.h"

static _Thread_local struct
{
    int (*compar)(const void *, const void *, void *);
    void *arg;
} state;

static int compar_wrapper(const void *a, const void *b)
{
    return state.compar(a, b, state.arg);
}

/* Follow the upcoming POSIX prototype, coming from GNU/libc.
 * Note that this differs from the BSD prototype. */

void qsort_r(void *base, size_t nmemb, size_t size,
             int (*compar)(const void *, const void *, void *),
             void *arg)
{
    int (*saved_compar)(const void *, const void *, void *) = state.compar;
    void *saved_arg = state.arg;

    state.compar = compar;
    state.arg = arg;

    qsort(base, nmemb, size, compar_wrapper);

    /* Restore state for nested reentrant calls */
    state.compar = saved_compar;
    state.arg = saved_arg;
}
