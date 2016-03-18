#include <stdio.h>
#include <stdlib.h>
struct data{
    int t1, t2;
};
struct queue_ptr{
    struct data *heap;
    int count;
    int cap;
};
void heapify(struct queue_ptr *q, int k, int n);
void init_queue(struct queue_ptr *q, int n){
    q->heap = (struct data*)malloc(n*sizeof(struct data));
    q->count = 0;
    q->cap = n;
}
void swap(struct queue_ptr *q, int a, int b){
    struct data temp = q->heap[a];
    q->heap[a] = q->heap[b];
    q->heap[b] = temp;
}
void insert(struct queue_ptr *q, struct data x){
    int i = q->count;
    q->count++;
    q->heap[i] = x;
    while((i>0)&&(q->heap[(i-1)/2].t2 > q->heap[i].t2)){
        /*temp_e = q->heap[(i-1)/2].elem;
         temp_p = q->heap[(i-1)/2].ptr;*/
        swap(q, (i-1)/2, i);
        i = (i-1)/2;
    }
}
struct data extract(struct queue_ptr *q){
    struct data x = q->heap[0];
    q->count--;
    if(q->count != 0){
        q->heap[0] = q->heap[q->count];
        heapify(q, 0, q->count);
    }
    return x;
}
int pass(struct queue_ptr *q, int n, int time){
    int i;
    if(q->count != 0){
        for(i = 0; i<q->count; i++){
            if(q->heap[i].t1>time+n) continue;
            /* else if(q->heap[i].t1>time){
             q->heap[i].t2 = q->heap[i].t2 = q->heap[i].t2 - (n-(q->heap[i].t1-time));
             if(q->heap[i].t2<0) q->heap[i].t2 = 0;
             }
             */else{
                 q->heap[i].t2 -=n;
                 if(q->heap[i].t2<0) q->heap[i].t2 = 0;
             }
            //else q->heap[i].t2-=n;
        }
    }
    heapify(q, 0, q->count);
    time+=n;
    return time;
}
void heapify(struct queue_ptr *q, int i, int n)
{
    int l;
    int r = i;
    while(1)
    {
        l = 2 * i + 1;
        if ((l < n) && (q->heap[l].t2 < q->heap[r].t2)) r = l;
        l++;
        if ((l < n) && (q->heap[l].t2 < q->heap[r].t2)) r = l;
        if (r == i) break;
        swap(q, i, r);
        i = r;
    }
}
int maximum(struct queue_ptr *q){
    return q->heap[0].t2;
}
int minimum(int a, int b){
    return a>b? b : a;
}
int main(int argc, const char * argv[]) {
    
    int i, j, current_time = 0, cp, num, count = 0;
    struct queue_ptr q, *pq;
    pq = &q;
    struct data temp;
    scanf("%d", &cp);
    scanf("%d", &num);
    struct proc{
        int t1, t2;
    }*pc;
    pc = (struct proc*)malloc(num*sizeof(struct proc));
    for(i = 0; i<num; i++){
        scanf("%d %d", &pc[i].t1, &pc[i].t2);
    }
    init_queue(pq, cp);
    temp.t1 = pc[0].t1;
    temp.t2 = pc[0].t2;
    count++;
    current_time = temp.t1;
    insert(pq, temp);
    for(i = 0;i<num;i++){
        j = pq->count;
        while(j<pq->cap&&i+pq->count<num){
            temp.t1 = pc[count].t1;
            temp.t2 = pc[count].t2;
            if(temp.t1<=current_time){
                insert(pq, temp);
                count++;
            }
            else if(temp.t1<current_time+maximum(pq)){
                current_time = pass(pq, temp.t1-current_time, current_time);
                insert(pq, temp);
                count++;
            }
            else break;
            j++;
        }
        temp = extract(pq);
        current_time = pass(pq, temp.t2, current_time);
        
    }
    printf("%d", current_time);
    free(pc);
    free(pq->heap);
    return 0;
}

