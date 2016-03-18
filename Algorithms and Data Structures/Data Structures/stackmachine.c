#include <stdio.h>
#include <stdlib.h>
struct stack1{
    int top;
    int cap;
    int* data;
};
void reloc(struct stack1 *s){
    int a[s->cap], i;
    for(i = 0; i < s->cap; i++) a[i] = s->data[i];
    free(s->data);
    s->data = (int*)malloc(2*s->cap*sizeof(int));
    for(i = 0; i< s->cap; i++) s->data[i] = a[i];
}
int max(int a, int b){
    return a > b? a : b;
}
int min(int a, int b){
    return a < b? a : b;
}
void initstack(int n, struct stack1 *s){
    s->top = 0;
    s->cap = n;
    s->data = (int*)malloc((n+1)*sizeof(int));
}
void push(int x, struct stack1 *s){
    if(s->top == s->cap) reloc(s);
    s->data[s->top] = x;
    s->top++;
}
int empty(struct stack1 *s){
    return s->top == 0? 1 : 0;
}
int pop(struct stack1 *s){
    if(empty(s)) printf("Stack is empty");
    s->top--;
    return s->data[s->top];
}

int main(int argc, const char * argv[]) {
    int n, i, n1, tmp, tmp1;
    char cmd[10];
    scanf("%d", &n);
    struct stack1 t;
    struct stack1 *s = &t;
    initstack(n, s);
    for(i = 0; i<n; i++){
        scanf("%s", cmd);
        if(cmd[0]=='C'){
            scanf("%d", &n1);
            push(n1, s);
        }
        if(cmd[0]=='A'){
            tmp = pop(s);
            push(pop(s)+tmp, s);
        }
        if((cmd[0]=='S')&&(cmd[1]=='U')) {
            tmp = pop(s);
            push(tmp-pop(s), s);
        }
        if((cmd[0]=='M')&&(cmd[1]=='U')) {
            tmp = pop(s);
            push(pop(s)*tmp, s);
        };
        if((cmd[0]=='D')&&(cmd[1]=='I')){
            tmp = pop(s);
            push(pop(s)/tmp, s);
        };
        if((cmd[0]=='M')&&(cmd[1]=='A')){
            tmp = pop(s);
            push(max(pop(s), tmp), s);
        };
        if((cmd[0]=='M')&&(cmd[1]=='I')){
            tmp = pop(s);
            push(min(pop(s), tmp), s);
        };
        if(cmd[0]=='N') push(-pop(s), s);
        if((cmd[0]=='D')&&(cmd[1]=='U')) push(s->data[s->top-1], s);
        if((cmd[0]=='S')&&(cmd[1]=='W')) {
            tmp = pop(s);
            tmp1 = pop(s);
            push(tmp, s);
            push(tmp1, s);
        }
    }
    printf("%d", s->data[s->top-1]);
    free(s->data);
    return 0;
}

