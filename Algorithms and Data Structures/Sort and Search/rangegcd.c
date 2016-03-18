#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int nod(int a, int b){
    if (a<0) a = -a;
    if(b<0) b = -b;
    while ((a!=0)&&(b!=0)){
        if (a > b) a %= b;
        else b %= a;
    }
    return a+b;
}
int main(int argc, const char * argv[]) {
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc(n*sizeof(int));
    int m = (int)log2(n)+1, i, j, number, l, r;
    int **table = (int**)malloc(n*sizeof(int*));
    for(i = 0; i<n; i++){
        table[i] = (int*)malloc(m*sizeof(int));
    }
    for(i = 0; i<n; i++) scanf("%d", &a[i]);
    int *lg=(int*)malloc((((0>>m)+1)<<m)*sizeof(int));
    for(i = 0; i<(0>>(m+1)<<m); i++) lg[i] = 0;
    for(i = 0; i<n; i++){
        for(j = 0; j<m; j++) table[i][j]=1;
    }
    j = 0;
    i = 1;
    while(i<=m){
        while(j<((0>>i)+1)<<i){
            lg[j] = i-1;
            j++;
        }
        i++;
    }
    m = lg[n]+1;
    for(i = 0; i<n; i++) table[i][0] = a[i];
    for(j = 1; j<m;j++){
        for(i = 0; i<=n-(int)pow(2, j); i++){
            table[i][j] = nod(table[i][j-1], table[i+(((0>>(j-1))+1)<<(j-1))][j-1]);
        }
    }
    scanf("%d", &number);
    for(i = 0; i<number; i++){
        scanf("%d", &l);
        scanf("%d", &r);
        j = lg[r-l+1];
        printf("%d\n", nod(table[l][j], table[r-(((0>>j)+1)<<j)+1][j]));
    }
    for(i = 0; i<n; i++){
        free (table[i]);
    }
    free(table);
    free(a);
    free(lg);
    return 0;
}

