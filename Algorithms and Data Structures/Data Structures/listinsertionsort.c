#include <stdio.h>
#include <stdlib.h>

struct Elem{
    struct Elem *prev, *next;
    int v;
};

struct Elem* init_elem(){
    struct Elem *list;
    list = (struct Elem*)malloc(sizeof(struct Elem));
    list->prev = list;
    list->next = list;
    return list;
}

void insert(struct Elem *x, struct Elem *y){
    struct Elem *z;
    z = x->next;
    x->next = y;
    y->prev = x;
    y->next = z;
    z->prev = y;
}

void delete(struct Elem *x){
    struct Elem *y, *z;
    z = x->next;
    y = x->prev;
    y->next = z;
    z->prev = y;
    x->prev = NULL;
    x->next = NULL;
}
int list_empty(struct Elem *list){
    return list->next==list? 1:0;
}
void insertionSort(struct Elem *list){
    struct Elem *i, *j;
    for (i = list->next; i != list; i = i->next){
        for (j = i->prev; j != list && j->v > i->v; j = j->prev);
        delete(i);
        insert(j, i);
    }
}

int main(int argv, const char* argc[]){
    int n, i;
    scanf("%d", &n);
    struct Elem *list = init_elem(), *new, *elem;
    for (i = 0; i < n; ++i)
    {
        new = init_elem();
        scanf("%d", &new->v);
        insert(list->prev, new);
    }
    insertionSort(list);
    for (elem = list->next->next; elem != list; elem = elem->next){
        printf("%d ", elem->prev->v);
        free(elem->prev);
    }
    printf("%d\n", elem->prev->v);
    free(elem->prev);
    free(list);
    return 0;
}