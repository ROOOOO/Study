#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Elem{
    struct Elem *next;
    char *v;
};

struct Elem *init_elem(){
    struct Elem *list;
    list = (struct Elem*)malloc(sizeof(struct Elem));
    list->v = (char*)malloc(100*sizeof(char));
    list->next = NULL;
    return list;
}
int compare(struct Elem* a, struct Elem* b);
void insert(struct Elem *x/*kuda*/, struct Elem *y){
    struct Elem *z;
    z = x->next;
    x->next = y;
    y->next = z;
}

void delete(struct Elem *x){
    struct Elem *y;
    y = x->next;
    x->next = y->next;
    y->next = NULL;
}
int list_empty(struct Elem *list){
    return list->next==list? 1:0;
}
void bubble_sort(struct Elem *list){
    struct Elem *i, *j, *temp, *temp1;
    for(i = list->next; i->next!=NULL; i = i->next){
        for(j = list; j->next->next!=NULL; j = j->next){
            if(compare(j->next, j->next->next)){
                temp = j->next;
                temp1 = j->next->next;
                temp->next = temp1->next;
                j->next = temp1;
                temp1->next = temp;
            }
        }
    }
}
int compare(struct Elem* a, struct Elem* b){
    return (int)strlen(a->v)>(int)strlen(b->v)? 1:0;
}
int main(int argv, const char* argc[]){
    int  count = 0, i, len;
    char *s = (char*)malloc(100*sizeof(char));
    fgets(s, 100, stdin);
    len = (int)strlen(s);
    s[len-1] = '\0';
    struct Elem *list = init_elem(), *new, *elem;
    elem = list;
    new = init_elem();
    for(i = 0; i<len; i++){
        if(s[i]!=' '&&s[i]!='\0'){
            new->v[count] = s[i];
            count++;
        }
        else{
            new->v[count] = '\0';
            insert(elem, new);
            elem = new;
            new = init_elem();
            count = 0;
        }
        if(s[i]==' '){
            while(s[i]==' ') i++;
            i--;
        }
    }
    bubble_sort(list);
    for (elem = list->next; elem != NULL; elem = list->next){
        printf("%s ", elem->v);
        free(list->v);
        free(list);
        list = elem;
    }
    free(list->v);
    free(list);
    free(new->v);
    free(new);
    free(s);
    return 0;
}