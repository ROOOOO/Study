#include <stdio.h>
#include <stdlib.h>

struct list{
    int k, v;
    struct list *next, *prev;
};

struct list* init_list(int k, int v){
    struct list *elem = (struct list*)malloc(sizeof(struct list));
    elem->k = k;
    elem->v = v;
    elem->next = elem->prev = elem;
    return elem;
}

void insert(struct list *l, int k, int v){
    struct list *x = init_list(k, v), *y = l->next;
    x->next = y;
    y->prev = x;
    l->next = x;
    x->prev = l;
}

struct list* list_search(struct list *l, int k){
    struct list *x = l->next;
    while (x != l && x->k != k)
    x = x->next;
    return x;
}

int main(int argc, const char* argv[])
{
    int n, i, xor = 0, s_of_xor, max;
    scanf("%d", &n);
    max = n;
    int *a = (int*)malloc(n*sizeof(int));
    for(i = 0; i<n; i++) scanf("%d", &a[i]);
    
    struct list **array = (struct list**)malloc(max*sizeof(struct list)), *temp, *temp1;
    for(i = 0; i<max; i++) array[i] = init_list(-1, -1);
    for(i = 0; i<n; i++){
        xor^=a[i];
        temp = list_search(array[abs(xor)%max], xor);
        if(temp!=array[abs(xor)%max]) temp->v++;
        else{
            if(xor==0) insert(array[abs(xor)%max], xor, 1);
            else insert(array[abs(xor)%max], xor, 0);
        }
    }
    for (i = s_of_xor = 0; i < max; ++i){
        for (temp = array[i]->next; temp != array[i]; temp = temp->next) s_of_xor += (temp->v * (temp->v + 1))/2;
    }
    printf("%d", s_of_xor);
    for(i = 0; i<max; i++){
        temp = array[i]->next;
        for(; temp!=array[i]&&temp!=NULL; temp = temp1){
            temp1 = temp->next;
            free(temp);
        }
        free(array[i]);
    }
    free(array);
    free(a);
    return 0;
}

