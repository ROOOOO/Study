#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
struct skip_list{
    int k;
    int *span;
    char *v;
    struct skip_list** next;
};
struct skip_list* init_skip_list(int m){
    int i;
    struct skip_list *l = (struct skip_list*)malloc(sizeof(struct skip_list));
    l->v = (char*)malloc(100*sizeof(char));
    l->span = (int*)malloc(m*sizeof(int));
    l->next = (struct skip_list**)malloc(m*sizeof(struct skip_list));
    for(i = 0; i<m; i++) l->next[i] = NULL;
    return l;
}
void skip(struct skip_list* l, int m, int k, struct skip_list **p, int *rnk){
    struct skip_list *x = l;
    int i;
    for(i = m-1; i>=0; i--){
        if(i==m-1) rnk[i] = 0;
        else rnk[i] = rnk[i+1];
        while(x->next[i]!=NULL && k > x->next[i]->k){
            rnk[i]+=x->span[i];
            x = x->next[i];
        }
        p[i] = x;
    }
}

void insert(struct skip_list *l, int m, int k, struct skip_list **p, int *rnk){
    struct skip_list *x = init_skip_list(m);
    srand((unsigned int) time(NULL));
    int i, r = rand()%m*2;
    x->k = k;
    scanf("%s", x->v);
    skip(l, m, x->k, p, rnk);
    for(i = 0; i<m && (r&1)==0; i++, r/=2){
        x->next[i] = p[i]->next[i];
        p[i]->next[i] = x;
        x->span[i] = p[i]->span[i]-(rnk[0] - rnk[i]);
        p[i]->span[i] = rnk[0]-rnk[i]+1;
        
    }
    for(;i<m;i++){
        x->next[i] = NULL;
        p[i]->span[i]++;
    }
}
struct skip_list* succ(struct skip_list* x){
    return x->next[0];
}
void delete(struct skip_list* l, int m, int k, struct skip_list **p, int *rnk){
    int i;
    skip(l, m, k, p, rnk);
    struct skip_list *x = succ(p[0]);
    for(i = 0; i<m; i++){
        if (p[i]->next[i] == x){
            p[i]->span[i] += x->span[i] - 1;
            p[i]->next[i] = x->next[i];
        }
        else p[i]->span[i]--;
    }
    free(x->next);
    free(x->span);
    free(x->v);
    free(x);
}
char* look_up(struct skip_list *l, int m, int k, struct skip_list **p, int *rnk){
    skip(l, m, k, p, rnk);
    return succ(p[0])->v;
}

int what_rank(struct skip_list *l, int m, int k)
{
    int i, rang;
    struct skip_list *x;
    for (i = m - 1, x = l, rang = 0; i >= 0; --i)
    while (x->next[i] != NULL && k > x->next[i]->k)
    {
        rang += x->span[i];
        x = x->next[i];
    }
    return rang;
}
int main(int argc, const char * argv[]) {
    int n, m, i, k, *rnk;
    scanf("%d", &n);
    m = log2(n);
    char cmd[10];
    struct skip_list *l = init_skip_list(m), *help_free = l, **p;
    p = (struct skip_list**)malloc(m*sizeof(struct skip_list*));
    rnk = (int*)malloc(m*sizeof(int));
    for(i = 0; i<n; i++){
        scanf("%s", cmd);
        if(cmd[0]=='I'){
            scanf("%d", &k);
            insert(l, m, k, p, rnk);
        }
        if(cmd[0]=='L'){
            scanf("%d", &k);
            printf("%s\n", look_up(l, m, k, p, rnk));
        }
        if(cmd[0]=='D'){
            scanf("%d", &k);
            delete(l, m, k, p, rnk);
        }
        if(cmd[0]=='R'){
            scanf("%d", &k);
            printf("%d\n", what_rank(l, m, k));
        }
    }
    while(l!=NULL){
        help_free = l->next[0];
        free(l->next);
        free(l->v);
        free(l->span);
        free(l);
        l = help_free;
    }
    free(rnk);
    free(p);
    return 0;
}

