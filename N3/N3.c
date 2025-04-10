#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct {

    TYPE *value;
    int code;

} output_t;

typedef struct {

    TYPE* head;
    unsigned int size;
} stat_arr_t;

typedef struct {

    stat_arr_t* array;
    unsigned int size;
    unsigned int capacity;

} dyn_arr_t;

static unsigned int basic_size = 8; 

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

dyn_arr_t* init_da(unsigned int size) {

    dyn_arr_t* arr = (dyn_arr_t*)malloc(sizeof(dyn_arr_t));

    if (arr == NULL) {

        return NULL;
    }

    arr->array = init_sa(size);

    if (arr->array == NULL) {

        free(arr);

        return NULL;
    }

    arr->size = 0;
    arr->array->size = 0;   
    arr->capacity = size;

    return arr;
}

dyn_arr_t* basic_init_da(void) {

    return init_da(basic_size);
}

output_t get_da(dyn_arr_t* arr, unsigned int pos) {

    output_t out;

    if (arr == NULL || pos >= arr->size) {

        out.code = 1;
        out.value = NULL;
    }
    else {

        out = get_sa(arr->array, pos);
    }

    return out; 
}

output_t set_da(dyn_arr_t* arr, unsigned int pos, TYPE* val) {

    output_t out;

    if (arr == NULL || pos >= arr->size || val == NULL) {

        out.code = 1;
        out.value = NULL;
        return out;
    }

    out = set_sa(arr->array, pos, val);

    return out;
}

unsigned int size_da(dyn_arr_t* arr) {

    if (arr == NULL) {

        return 0;
    }

    return arr->size;
}

int is_empty_da(dyn_arr_t* arr) {

    if (arr == NULL || arr->size == 0) {

        return true;
    }
    else {

        return false;
    }
}

void push_back_da(dyn_arr_t* arr, TYPE* val) {

    if (arr == NULL || val == NULL) {

        return;
    }

    if (arr->size >= arr->capacity) {

        unsigned int newcapacity = arr->capacity * 2;

        TYPE* newhead = (TYPE*)realloc(arr->array->head, sizeof(TYPE) * newcapacity);

        if (newhead != NULL) {

            arr->array->head = newhead;
            arr->capacity = newcapacity;
        }
    }

    *(arr->array->head + arr->size) = *val;
    arr->size++;
    arr->array->size = arr->size;
}

output_t pop_back_da(dyn_arr_t* arr) {

    output_t out;

    if (arr == NULL || arr->size == 0) {

        out.code = 1;
        out.value = NULL;
    }
    else {

        out = get_sa(arr->array, arr->size - 1);

        arr->size--;
        arr->array->size = arr->size;

        if (arr->capacity > basic_size && arr->size < arr->capacity / 4) {

            arr->capacity /= 2;
            unsigned int newcapacity = arr->capacity / 2;

            TYPE* newhead = (TYPE*)realloc(arr->array->head, sizeof(TYPE) * newcapacity);

            if (newhead != NULL) {

                arr->array->head = newhead;
                arr->capacity = newcapacity;
            }
        }
    }

    return out;
}

void finalize_da(dyn_arr_t* arr) {

    if (arr != NULL) {

        finalize_sa(arr->array);

        free(arr);
    }
}