#include <stdio.h>
#include <stdlib.h>

#define TYPE int

typedef struct {

    TYPE *value;
    int code;

} output_t;

typedef struct {

    TYPE* head;
    unsigned int size;
} stat_arr_t;
        
stat_arr_t *init_sa(unsigned int size) {

    stat_arr_t* arr = (stat_arr_t*)malloc(sizeof(stat_arr_t));

    if (arr == NULL) {

        return NULL;
    }

    arr->head = (TYPE*)malloc(sizeof(TYPE) * size);

    if (arr->head == NULL) {

        free(arr);
        return NULL;
    }

    arr->size = size;

    return arr;
}

output_t get_sa(stat_arr_t* arr, unsigned int pos) {
    
    output_t out;

    if (arr == NULL || arr->head == NULL || pos >= arr->size) {

        out.code = 1;
        out.value = NULL;
    }
    else {

        out.code = 0;
        out.value = arr->head + pos;
    }

    return out;
}

output_t set_sa(stat_arr_t* arr, unsigned int pos, TYPE* val) {

    output_t out;

    out.value = NULL;

    if (arr == NULL || arr->head == NULL || val == NULL || pos >= arr->size) {

        out.code = 1;
    }
    else {

        out.code = 0;

        *(arr->head + pos) = *val;  
    }

    return out;
}

unsigned int size_sa(stat_arr_t* arr) {

    if (arr != NULL) {

        return arr->size;
    }

    return 0;
}

void finalize_sa(stat_arr_t* arr) {

    if (arr != NULL) {

        if (arr->head != NULL) {

            free(arr->head);
        }

        free(arr);
    }
}