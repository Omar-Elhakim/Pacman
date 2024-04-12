#include "glinkedlist.h"
#include <stdbool.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct gqueue_t gqueue_t;

gqueue_t *create_queue(void (*add_data)(node_t *, void *data));

int16_t enqueue(gqueue_t *queue, void *data);
int16_t dequeue(gqueue_t *queue);
size_t  queue_length(gqueue_t *queue);

void *queue_front(gqueue_t *queue);
void *queue_back(gqueue_t *queue);
bool  queue_is_empty(gqueue_t *queue);
bool  in_queue(gqueue_t *heystack, void *needle,
               bool (*search_fun)(node_t *node, void *data));

linked_list_t *queue_list(gqueue_t *queue);

void destroy_queue(gqueue_t **queue);

#endif // !QUEUE_H
