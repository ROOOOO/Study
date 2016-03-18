#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct t_elem{
    int k, count;
    char *v;
    struct t_elem *parent;
    struct t_elem *kid_l, *kid_r;
};
struct t_elem* init_elem(){
    struct t_elem *elem = (struct t_elem*)malloc(sizeof(struct t_elem));
    elem->v = (char*)malloc(100*sizeof(char));
    elem->count = 1;
    elem->parent = elem->kid_l = elem->kid_r = NULL;
    return elem;
}
void free_tree(struct t_elem *t);
struct t_elem* insert(struct t_elem *t, int k){
    struct t_elem *y = init_elem(), *x = t;
    y->k = k;
    scanf("%s", y->v);
    if(t==NULL) t = y;
    else{
        while(1){
            x->count++;
            if(k<x->k){
                if(x->kid_l==NULL){
                    x->kid_l = y;
                    y->parent = x;
                    break;
                }
                x = x->kid_l;
            }
            else{
                if(x->kid_r==NULL){
                    x->kid_r = y;
                    y->parent = x;
                    break;
                }
                x = x->kid_r;
            }
        }
    }
    return t;
}
struct t_elem* replace_node(struct t_elem* t, struct t_elem* x, struct t_elem* y){
    struct t_elem* p;
    if(x==t) t = y;
    else{
        p = x->parent;
        if(y!=NULL) y->parent = p;
        if(p->kid_l==x) p->kid_l = y;
        else p->kid_r = y;
    }
    return t;
}
struct t_elem* descend(struct t_elem *t, int k){
    struct t_elem *x = t;
    while(x!=NULL && x->k!=k){
        x->count--;
        if(k<x->k) x = x->kid_l;
        else x = x->kid_r;
    }
    return x;
}
struct t_elem* minimum(struct t_elem* t){
    struct t_elem *x;
    if(t==NULL) x = NULL;
    else{
        x = t;
        while (x->kid_l!=NULL) x = x->kid_l;
    }
    return x;
}
struct t_elem* delete(struct t_elem *t, int k){
    struct t_elem *x = descend(t, k), *y, *temp;
    if(x->kid_l==NULL && x->kid_r==NULL) t = replace_node(t, x, NULL);
    else if(x->kid_l==NULL) t = replace_node(t, x, x->kid_r);
    else if(x->kid_r==NULL) t = replace_node(t, x, x->kid_l);
    else{
        y = minimum(x->kid_r);
        for(temp = y->parent; temp != x; temp = temp->parent)
        temp->count--;
        t = replace_node(t, y, y->kid_r);
        x->kid_l->parent = y;
        y->kid_l = x->kid_l;
        if(x->kid_r!=NULL) x->kid_r->parent = y;
        y->kid_r = x->kid_r;
        t = replace_node(t, x, y);
        y->count = x->count-1;
    }
    free(x->v);
    free(x);
    return t;
}
void free_tree(struct t_elem *t){
    struct t_elem *y;
    if (t != NULL)
    {
        free_tree(t->kid_l);
        y = t->kid_r;
        free(t->v);
        free(t);
        free_tree(y);
    }
}
char* search(struct t_elem *t, int k){
    int r;
    if(t->kid_l!=NULL) r = t->kid_l->count+1;
    else r = 1;
    if (k == r)
    return t->v;
    else if (k < r)
    return search(t->kid_l, k);
    else
    return search(t->kid_r, k - r);
}
char* lookup(struct t_elem* t, int k){
    struct t_elem* x = t;
    while(x!=NULL && x->k!=k){
        if(k<x->k) x = x->kid_l;
        else x = x->kid_r;
    }
    return x->v;
}
int main(int argc, const char * argv[]) {
    int n, i, k;
    scanf("%d", &n);
    char cmd[10];
    struct t_elem *t = NULL;
    for(i = 0; i<n; i++){
        scanf("%s", cmd);
        if (cmd[0]=='I'){
            scanf("%d", &k);
            t = insert(t, k);
        }
        else if (cmd[0]=='L'){
            scanf("%d", &k);
            printf("%s\n", lookup(t, k));
        }
        else if (cmd[0]=='D'){
            scanf("%d", &k);
            t = delete(t, k);
        }
        else if (cmd[0]=='S'){
            scanf("%d", &k);
            printf("%s\n", search(t, k+1));
        }
    }
    free_tree(t);
    return 0;
}

