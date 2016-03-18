#include <stdio.h>
#include <stdlib.h>
struct inf1{
    int elem;
    int max;
};
struct stack{
    int cap;
    int top1;
    int top2;
    struct inf1 *data;
};
int max(int a, int b){
    return a > b? a : b;
}
void init_queue(int n, struct stack* s){
    s->top1 = 0;
    s->top2 = n-1;
    s->cap = n;
    s->data = (struct inf1*)malloc((n+1)*sizeof(struct inf1));
}
int empty1(struct stack *s){
    return s->top1 == 0 ? 1:0;
}
int empty2(struct stack *s){
    return s->top2 == s->cap-1 ? 1:0;
}
int queue_empty(struct stack *s){
    return empty1(s)&&empty2(s);
}
void push1(int x, struct stack *s){
    s->data[s->top1].elem = x;
    if(s->top1>0) s->data[s->top1].max = max(s->data[s->top1-1].max, x);
    else s->data[s->top1].max = x;
    s->top1++;
}
void push2(int x, struct stack *s){
    s->data[s->top2].elem = x;
    if(s->top2<s->cap-1) s->data[s->top2].max = max(s->data[s->top2+1].max, x);
    else s->data[s->top2].max = x;
    s->top2--;
}
int pop1(struct stack *s){
    s->top1--;
    return s->data[s->top1].elem;
}
int pop2(struct stack *s){
    s->top2++;
    return s->data[s->top2].elem;
}
void enqueue(int x, struct stack *s){
    push1(x, s);
}
int dequeue(struct stack *s){
    int x;
    if(empty2(s)){
        while(!empty1(s))
        push2(pop1(s), s);
    }
    x = pop2(s);
    return x;
}
int maximum(struct stack *s){
    if((s->top1>0)&&(s->top2<s->cap-1)) return max(s->data[s->top1-1].max, s->data[s->top2+1].max);
    else if (empty2(s)!=1) return s->data[s->top2+1].max;
    else return s->data[s->top1-1].max;
}
int main(int argc, const char * argv[]) {
    struct stack t;
    struct stack *s = &t;
    int n, i, n1;
    scanf("%d", &n);
    init_queue(100000, s);
    char cmd[5];
    for(i = 0; i<n; i++){
        scanf("%s", cmd);
        if((cmd[0]=='E')&&(cmd[1]=='N')){
            scanf("%d", &n1);
            enqueue(n1, s);
        }
        if(cmd[0]=='D') printf("%d\n", dequeue(s));
        if((cmd[0]=='E')&&(cmd[1]=='M')){
            if(queue_empty(s)) printf("true\n");
            else printf("false\n");
        }
        if(cmd[0]=='M')printf("%d\n", maximum(s));
    }
    
    return 0;
}

