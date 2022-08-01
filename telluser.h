#ifndef _TELLUSER_H_
#define _TELLUSER_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct telluser {
    char          type;
    char const   *key;
    char          msg[1];
};

__attribute__((weak))
struct telluser *telluser_new(char const *_key, char _type, char const *_fmt, va_list _va) {
    
    va_list va;
    va_copy(va, _va);
    size_t l = vsnprintf(NULL, 0, _fmt, va);
    va_end(va);

    struct telluser *out = malloc(sizeof(struct telluser)+l);
    if (!out) return NULL;

    out->type = _type;
    out->key  = _key;
    vsprintf(out->msg, _fmt, _va);
    
    return out;
}

__attribute__((weak)) struct telluser *__telluser_l[20]  = {0};
__attribute__((weak)) size_t           __telluser_l_p    = {0};
__attribute__((weak)) bool             __telluser_inited = false;

__attribute__((weak))
void telluser_cleanup(void) {
    for (size_t i=0; i<20; i++) {
        if (__telluser_l[i]) {
            free(__telluser_l[i]);
        }
    }
}

__attribute__((weak))
void telluser(char const *_key, char _type, char const *_fmt, ...) {
    struct telluser **n = __telluser_l + __telluser_l_p; va_list va;
    if (!__telluser_inited) {
        __telluser_inited = true;
        atexit(telluser_cleanup);
    }
    if (*n) {
        free(*n);
        *n = NULL;
    }
    va_start(va, _fmt);
    *n = telluser_new(_key, _type, _fmt, va);
    va_end(va);
    if (*n) {
        __telluser_l_p = (__telluser_l_p + 1) % 20;
    }
}

__attribute__((weak))
char telluser_chk_type (char const *_key) {
    struct telluser **L = __telluser_l;
    for (size_t c = 0, p = __telluser_l_p; c < 20; p = (p+1)%20, c++) {
        if (L[p] && !strcmp(L[p]->key, _key)) {
            return L[p]->type;
        }
    }
    return '\0';
}

__attribute__((weak))
bool telluser_pop_key (char const *_key, struct telluser **_m) {
    struct telluser **L = __telluser_l;
    for (size_t c = 0, p = __telluser_l_p; c < 20; p = (p+1)%20, c++) {
        if (L[p] && !strcmp(L[p]->key, _key)) {
            *_m = L[p];
            L[p] = NULL;
            return true;
        }
    }
    return false;
}

__attribute__((weak))
void telluser_pop_fp (char _type, FILE *_fp, const char *_opt_nl) {
    struct telluser **L = __telluser_l;
    for (size_t c = 0, p = __telluser_l_p; c < 20; p = (p+1)%20, c++) {
        if (L[p] && L[p]->type == _type) {
            fputs(L[p]->msg, _fp);
            if (_opt_nl) fputs(_opt_nl, _fp);
            free(L[p]);
            L[p] = NULL;
        }
    }
}

#endif
