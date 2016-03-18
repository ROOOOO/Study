#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Partition(int*a, int low, int high);
struct tasks{
    int l;
    int r;
};
struct stack{
    int top;
    int cap;
    struct tasks *tsk;
};
void initstack(int n, struct stack *s){
    s->top = 0;
    s->cap = n;
    s->tsk = (struct tasks*)malloc((n+1)*sizeof(struct tasks));
}
void push(int lb, int rb, struct stack *s){
    if(s->top == s->cap){
        //printf("Stack is full");
        return;
    }
    s->tsk[s->top].l = lb;
    s->tsk[s->top].r = rb;
    s->top++;
}
int empty(struct stack *s){
    return s->top == 0? 1 : 0;
}
void qs(int* a, int left, int right, struct stack *s){
    push(left, right, s);
    int i;
    while(empty(s)!=1){
        left = s->tsk[s->top-1].l;
        right = s->tsk[s->top-1].r;
        s->top--;
        if(left<right){
            i = Partition(a, left, right+1);
            push(left, i-1, s);
            push(i+1, right, s);
        }
    }
}
int Partition(int*a, int low, int high){
    int elem = (low+high)/2;
    int i, j, temp;
    high--;
    i = low;
    j = low;
    temp = a[high];
    a[high] = a[elem];
    a[elem] = temp;
    while (j<high){
        if (a[j] <= a[high]){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
        }
        j++;
    }
    temp = a[i];
    a[i] = a[high];
    a[high] = temp;
    return i;
}

int main(int argc, const char * argv[]) {
    int n, i;
    scanf("%d ", &n);
    int a[n];
    struct stack t;
    struct stack *s = &t;
    for(i = 0; i<n; i++) scanf("%d", &a[i]);
    initstack(2*n, s);
    qs(a, 0, n-1, s);
    for(i = 0; i<n; i++) printf("%d ", a[i]);
    free(s->tsk);
    return 0;
}

