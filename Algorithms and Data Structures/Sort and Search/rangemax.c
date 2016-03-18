#include <stdio.h>
#include <stdlib.h>
int max(int a, int b){
    if(a>b)
    return a;
    return b;
}
int min(int a, int b){
    if(a<b) return a;
    return b;
}
void build(int *b, int lb, int rb, int i, int *a){
    int m;
    if(lb==rb) b[i] = a[lb];
    else{
        m = (lb+rb)/2;
        build(b, lb, m,  2*i+1, a);
        build(b, m+1, rb,  2*i+2, a);
        b[i] = max(b[2*i+1], b[2*i+2]);
    }
    
}
int query(int* b, int lb, int rb, int l, int r, int i){
    int m;
    if(l>r) return -1000000001;
    if((lb==l)&&(rb==r)) return b[i];
    else{
        m = (lb+rb)/2;
        return max(query(b, lb, m, l, min(r, m), 2*i+1), query(b, m+1, rb, max(l, m+1), r, 2*i+2));
    }
}
void update(int *b, int lb, int rb, int i, int pos, int new){
    int m;
    if(lb==rb) b[i]=new;
    else{
        m = (lb+rb)/2;
        if(pos<=m) update(b, lb, m, 2*i+1, pos, new);
        else update(b, m+1, rb, 2*i+2, pos, new);
        b[i] = max(b[2*i+1], b[2*i+2]);
    }
}
int main(int argc, const char * argv[]) {
    int n, i, n1, n2, number;
    scanf("%d", &n);
    int *a = (int*)malloc(n*sizeof(int));
    int q = 4*n, *b = (int*)malloc(q*sizeof(int));
    for(i = 0; i<n; i++) scanf("%d", &a[i]);
    scanf("%d", &number);
    for(i = 0; i<q; i++) b[i] = -1000000001;
    build(b, 0, n-1, 0, a);
    free (a);
    char command[3];
    for(i = 0; i<number; i++){
        scanf("%s", command);
        scanf("%d", &n1);
        scanf("%d", &n2);
        if(command[0]=='U') update(b, 0, n-1, 0, n1, n2);
        if(command[0]=='M') printf("%d\n", query(b, 0, n-1, n1, n2, 0));
    }
    free (b);
    return 0;
}

