#include <stdio.h>
#include <stdlib.h>

typedef struct {

    int val;
} a_t;

typedef struct {

    int val;
} b_t;

typedef struct {

    int val;
} c_t;

int plus_basic(a_t *a, b_t *b) {

    return a->val + b->val;
}

void plus_intermediate(a_t* a, b_t *b, c_t *c){

    c->val = a->val + b->val;
}

c_t *plus_advanced(a_t *a, b_t *b){

    c_t *c = (c_t*)malloc(sizeof(c_t));

    if(c == NULL){

        return NULL;
    }

    c->val = a->val + b->val;

    return c;
}