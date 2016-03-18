#include <stdio.h>
#include <stdlib.h>
struct data{
    int elem, index, esc;
};
struct queue_ptr{
    struct data* heap;
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
    while((i>0)&&(q->heap[(i-1)/2].elem > q->heap[i].elem)){
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
void heapify(struct queue_ptr *q, int i, int n)
{
    int l;
    int r = i;
    while(1)
    {
        l = 2 * i + 1;
        if ((l < n) && (q->heap[l].elem < q->heap[r].elem)) r = l;
        l++;
        if ((l < n) && (q->heap[l].elem < q->heap[r].elem)) r = l;
        if (r == i) break;
        swap(q, i, r);
        i = r;
    }
}
int main(int argc, const char * argv[]) {
    struct queue_ptr q, *pq;
    pq = &q;
    int i, k, count = 0, j;
    scanf("%d", &k);
    init_queue(pq, k);
    int *s = (int*)malloc(k*sizeof(int));
    int **arrays = (int**)malloc(k*sizeof(size_t));
    struct data temp;
    for(i = 0; i<k; i++){
        scanf("%d", &s[i]);
        arrays[i] = (int*)malloc((s[i]+100)*sizeof(int));
        count+=s[i];
    }
    for(i = 0; i<k; i++){
        for(j = 0; j<s[i]; j++) scanf("%d", &arrays[i][j]);
    }
    for(i = 0; i<k; i++){
        if(s[i]>0){
            temp.elem = arrays[i][0];
            temp.index = i;
            temp.esc = 0;
            insert(pq, temp);
        }
    }
    for(i = 0; i<count;){
        if(q.count>0){
            temp = extract(pq);
            printf("%d ", temp.elem);
            i++;
        }
        temp.esc++;
        if(temp.esc!=s[temp.index]){
            temp.elem = arrays[temp.index][temp.esc];
            insert(pq, temp);
            
        }
    }
    free(q.heap);
    free(s);
    for(i = 0; i<k; i++) free(arrays[i]);
    free(arrays);
    return 0;
}



