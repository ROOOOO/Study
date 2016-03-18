#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void delete(struct list *x){
    struct list *y = x->prev, *z = x->next;
    y->next = z;
    z->prev = y;
    free(x);
}

int main(int argc, const char * argv[]) {
    int n, m, i, k, v;
    scanf("%d", &n);
    scanf("%d", &m);
    char cmd[10];
    struct list **array = (struct list**)malloc(m*sizeof(struct list)), *temp, *temp1;
    for(i = 0; i<m; i++) array[i] = init_list(-1, 0);
    for(i = 0; i<n; i++){
        scanf("%s", cmd);
        if(cmd[1] == 'S'){
            scanf("%d", &k);
            scanf("%d", &v);
            temp = list_search(array[k%m], k);
            if(temp!=array[k%m]){
                if(v==0) delete(temp);
                else temp->v = v;
            }
            else{
                if(v==0) continue;
                else insert(array[k%m], k, v);
            }
        }
        if(cmd[1] == 'T'){
            scanf("%d", &k);
            temp = list_search(array[k%m], k);
            if(temp==array[k%m]) printf("0\n");
            else printf("%d\n", temp->v);
        }
    }
    for(i = 0; i<m; i++){
        temp = array[i]->next;
        for(; temp!=array[i]&&temp!=NULL; temp = temp1){
            temp1 = temp->next;
            free(temp);
        }
        free(array[i]);
    }
    free(array);
    return 0;
}