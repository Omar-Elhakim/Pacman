#include "glinkedlist.h"
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif // cpp

typedef struct stack_t      stack_t;
typedef struct ArrayStack_t ArrayStack_t;

stack_t      *create_stack(void (*_allocate_data)(node_t *, void *data));
ArrayStack_t *create_ArrayStack(size_t element_size,
                                void   (*_allocate_data)(void *data));

int16_t stack_push(stack_t *stack, void *data);
void    stack_pop(stack_t *stack);
void   *stack_peak(stack_t *stack);
bool    stack_is_empty(stack_t *stack);

int16_t ArrayStack_push(ArrayStack_t *stack, void *data);
void    ArrayStack_pop(ArrayStack_t *stack);
void   *ArrayStack_peak(ArrayStack_t *stack);
bool    ArrayStack_is_empty(ArrayStack_t *stack);

void destroy_stack(stack_t **stack);
void clear_stack(stack_t *stack);

void destroy_ArrayStack(ArrayStack_t **stack);
void clear_ArrayStack(ArrayStack_t *stack);

#ifdef __cplusplus
}
#endif // cpp
#endif // !STACK_H
