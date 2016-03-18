#include <stdio.h>
#include <stdlib.h>
struct queue{
    int* data;
    int head;
    int tail;
    int cap;
    int count;
};

void initqueue(int n, struct queue* q){
    q->data = (int*)malloc(n*sizeof(int));
    q->cap = n;
    q->count = 0;
    q->head = 0;
    q->tail = 0;
}

void relocation(struct queue* q){
    int a[q->cap], i;
    for (i = 0; i < q->cap; i++) a[i] = q->data[i];
    free(q->data);
    q->data = (int*)malloc(2*q->cap*sizeof(int));
    for(i = 0; i<2*q->cap; i++) q->data[i] = 666;
    if (q->tail>q->head){
        for (i = 0; i < q->cap; i++) q->data[i] = a[i];
    }
    else{
        for(i = 0; i<q->tail; i++) q->data[i] = a[i];
        for(i = q->head; i<=q->cap-1; i++) q->data[i+q->cap] = a[i];
        q->head +=q->cap;
    }
    q->cap = 2*q->cap;
}

int empty(struct queue* q){
    return q->count == 0? 1 : 0;
}

void enqueue(int x, struct queue* q){
    if(q->count==q->cap) relocation(q);
    q->data[q->tail] = x;
    q->tail++;
    if(q->tail == q->cap) q->tail = 0;
    q->count++;
}

int dequeue(struct queue* q){
    int x = q->data[q->head];
    q->head++;
    if(q->head == q->cap) q->head = 0;
    q->count--;
    printf("%d\n", x);
    return x;
}
int main(int argc, const char * argv[]) {
    int n, i, n1;
    scanf("%d", &n);
    char cmd[5];
    struct queue que;
    struct queue* q = &que;
    initqueue(4, q);
    for(i = 0; i<n; i++){
        scanf("%s", cmd);
        if((cmd[0]=='E')&&(cmd[1]=='N')){
            scanf("%d", &n1);
            enqueue(n1, q);
        }
        if(cmd[0]=='D'){
            n1 = dequeue(q);
        }
        if((cmd[0]=='E')&&(cmd[1]=='M')){
            if(empty(q)) printf("true\n");
            else printf("false\n");
        }
    }
    free(q->data);
    return 0;
}

