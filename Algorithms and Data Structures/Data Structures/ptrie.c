#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bor{
    int v, prefix;
    struct bor *parent, **archs;
};

struct bor* init_trie(int k){
    int i;
    struct bor *trie_el;
    trie_el = (struct bor*)malloc(k*sizeof(struct bor));
    trie_el->archs = (struct bor**)malloc(26*sizeof(struct bor*));
    for(i = 0; i < 26; i++){
        trie_el->archs[i] = NULL;
    }
    trie_el->parent = NULL;
    trie_el->v = 0;
    trie_el->prefix = 0;
    return trie_el;
}

void insert(struct bor *trie, char *string){
    int i, dl = (int)strlen(string);
    struct bor *x, *y, *z;
    for(i = 0, x = trie; i < dl;y->prefix++, x = y, i++){
        y = x->archs[string[i]-97];
        if(!y) break;
    }
    for(;i < dl;z->parent = x, x = z, z->prefix++, i++){
        z = init_trie(1);
        x->archs[string[i]-97] = z;
    }
    x->v++;
    if(x->v > 1) for(x->v = 0; x->parent != NULL; x = x->parent) x->prefix--;
}

void delete(struct bor *trie, char *string){
    int i, dl = (int)strlen(string);
    struct bor *x, *y;
    for(i = 0, x = trie; i < dl; i++, y->prefix--, x = y){
        y = x->archs[string[i]-97];
        if(!y) break;
    }
}

int prefix(struct bor *trie, char *string){
    int i, len = (int)strlen(string);
    struct bor *temp;
    for(i = 0, temp = trie; i < len;temp = temp->archs[string[i]-97], i++) if (!temp->archs[string[i]-97]) return 0;
    return temp->prefix;
}

void free_all(struct bor *trie){
    int i;
    for(i = 0; i < 26; i++) if(trie->archs[i] != NULL) free_all(trie->archs[i]);
    free(trie->archs);
    free(trie);
}

int main(int argc, const char * argv[]){
    int i, n;
    
    scanf("%d", &n);
    char cmd[10], *string = (char*)malloc(100000*sizeof(char));
    struct bor *trie= init_trie(1);
    for(i = 0; i < n; i++){
        scanf("%s", cmd);
        if(cmd[0] == 'I'){
            scanf("%s", string);
            insert(trie, string);
        }
        else if(cmd[0] == 'P'){
            scanf("%s", string);
            printf("%d\n", prefix(trie, string));
        }
        else if(cmd[0]=='D'){
            scanf("%s", string);
            delete(trie, string);
        }
    }
    free(string);
    free_all(trie);
    return 0;
}