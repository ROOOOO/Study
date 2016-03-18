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
void build(int *b, int lb, int rb, int i, int *a, int n){
    int m;
    if((lb==rb)&&(lb>0)&&(lb<n-1)){
        if((a[lb]>=a[lb+1])&&(a[lb]>=a[lb-1])) b[i] = 1;
        else b[i]=0;
    }
    else if((lb==rb)&&(n==1)) b[i] = 1;
    else if((lb==rb)&&(lb==0)){
        if((a[lb]>=a[lb+1])) b[i] = 1;
        else b[i] = 0;
    }
    else if((lb==rb)&&(lb==n-1)){
        if((a[lb]>=a[lb-1])) b[i] = 1;
        else b[i] = 0;
    }
    else{
        m = (lb+rb)/2;
        build(b, lb, m,  2*i+1, a, n);
        build(b, m+1, rb,  2*i+2, a, n);
        b[i] = b[2*i+1]+b[2*i+2];
    }
    
}
int query(int* b, int lb, int rb, int l, int r, int i){
    int m;
    if(l>r) return 0;
    if((lb==l)&&(rb==r)) return b[i];
    else{
        m = (lb+rb)/2;
        return query(b, lb, m, l, min(r, m), 2*i+1) + query(b, m+1, rb, max(l, m+1), r, 2*i+2);
    }
}
void update(int *b, int lb, int rb, int i, int pos, int new, int *a, int n){
    int m;
    if((lb==rb)&&(lb>0)&&(lb<n-1)){
        if((new>=a[lb+1])&&(new>=a[lb-1])) b[i] = 1;
        else b[i]=0;
    }
    else if((lb==rb)&&(n==1)) b[i] = 1;
    else if((lb==rb)&&(lb==0)){
        if((new>=a[lb+1])) b[i] = 1;
        else b[i] = 0;
    }
    else if((lb==rb)&&(lb==n-1)){
        if((new>=a[lb-1])) b[i] = 1;
        else b[i] = 0;
    }
    else{
        m = (lb+rb)/2;
        if(pos<=m) update(b, lb, m, 2*i+1, pos, new, a, n);
        else update(b, m+1, rb, 2*i+2, pos, new, a, n);
        b[i] = b[2*i+1] + b[2*i+2];
    }
}
int main(int argc, const char * argv[]) {
    int n, i, n1, n2, number;
    scanf("%d", &n);
    int *a = (int*)malloc(n*sizeof(int));
    int q = 4*n;
    int *b = (int*)malloc(q*sizeof(int));
    for(i = 0; i<n; i++) scanf("%d", &a[i]);
    scanf("%d", &number);
    for(i = 0; i<q; i++) b[i] = 0;
    build(b, 0, n-1, 0, a, n);
    char command[4];
    for(i = 0; i<number; i++){
        scanf("%s", command);
        scanf("%d", &n1);
        scanf("%d", &n2);
        if(command[0]=='U'){
            update(b, 0, n-1, 0, n1, n2, a, n);
            a[n1] = n2;
            if(n1-1>=0) update(b, 0, n-1, 0, n1-1, a[n1-1], a, n);
            if(n1+1<n)update(b, 0, n-1, 0, n1+1, a[n1+1], a, n);
        }
        if(command[0]=='P') printf("%d\n", query(b, 0, n-1, n1, n2, 0));
    }
    free (a);
    free (b);
    return 0;
}

