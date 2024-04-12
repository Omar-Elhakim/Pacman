#include <stdlib.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node_t          node_t;
typedef struct linked_list_t   linked_list_t;
typedef struct list_iterator_t list_iterator_t;

linked_list_t   *create_list(void (*allocate_data)(node_t *, void *data));
list_iterator_t *create_list_iterator(linked_list_t *list);

node_t *list_head(linked_list_t *list);
node_t *list_tail(linked_list_t *list);
node_t *next(list_iterator_t *iterator);
node_t *prev(list_iterator_t *iterator);
node_t *itr_begin(list_iterator_t *iterator);
node_t *itr_end(list_iterator_t *iterator);

int16_t push_front(linked_list_t *list, void *data);
int16_t push_back(linked_list_t *list, void *data);
int16_t pop_front(linked_list_t *list);
int16_t pop_back(linked_list_t *list);

void  node_set_data(node_t *node, void *data);
void *node_data(node_t *node);
void *peak_front(linked_list_t *list);
void *peak_back(linked_list_t *list);
void  clear_list(linked_list_t *list);
void  destroy_list(linked_list_t **list);
void  itr_set_from(list_iterator_t *iterator, node_t *from);
void  itr_set_begin(list_iterator_t *iterator, node_t *begin_node);
void  itr_set_end(list_iterator_t *iterator, node_t *end_node);

linked_list_t *itr_list(list_iterator_t *iterator);

int16_t dump_list(linked_list_t *list, void (*print_data)(void *));
int16_t reverse_dump_list(linked_list_t *list, void (*print_data)(void *));

#endif // LINKED_LIST_H
