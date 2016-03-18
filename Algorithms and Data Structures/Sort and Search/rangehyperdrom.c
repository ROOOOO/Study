#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int xor(int a, int b);

int max(int a, int b){
    return a>b? a : b;
}
int min(int a, int b){
    return a<b? a : b;
}
void build(int *b, int lb, int rb, int i, char *a){
    int m;
    if(lb==rb) b[i] = ((0>>((int)a[lb]-97))+1)<<(a[lb]-97);
    else{
        m = (lb+rb)/2;
        build(b, lb, m,  2*i+1, a);
        build(b, m+1, rb,  2*i+2, a);
        b[i] = xor(b[2*i+1], b[2*i+2]);
    }
    
}
int query(int* b, int lb, int rb, int l, int r, int i){
    int m;
    if(l>r) return 0;
    if((lb==l)&&(rb==r)) return b[i];
    else{
        m = (lb+rb)/2;
        return xor(query(b, lb, m, l, min(r, m), 2*i+1), query(b, m+1, rb, max(l, m+1), r, 2*i+2));
    }
}
void update(int *b, int lb, int rb, int i, int pos, char* new, int j){
    int m;
    if(lb==rb){
        b[i]=((0>>((int)new[j]-97))+1)<<(new[j]-97);
    }
    else{
        m = (lb+rb)/2;
        if(pos<=m) update(b, lb, m, 2*i+1, pos, new, j);
        else update(b, m+1, rb, 2*i+2, pos, new, j);
        b[i] = xor(b[2*i+1], b[2*i+2]);
    }
}

int xor(int a, int b){
    int x = (~a|~b)&(a|b);
    return x;
}
int main(int argc, const char * argv[]) {
    char *a=(char*)malloc(1000001*sizeof(char)), cmd[3];
    char *n2c = (char*)malloc(1000001*sizeof(char));
    scanf("%s", a);
    int l = (int)strlen(a), i, n, n1, n2, j, temp;
    int *b = (int*)malloc(4*l*sizeof(int));
    for(i = 0; i<4*l; i++) b[i] = 0;
    build(b, 0, l-1, 0, a);
    scanf("%d", &n);
    for(i = 0; i<n; i++){
        scanf("%s", cmd);
        if(cmd[0]=='H'){
            scanf("%d", &n1);
            scanf("%d", &n2);
            if(n1==n2) printf("YES\n");
            else if(query(b, 0, l-1, n1, n2, 0)==0) printf("YES\n");
            else{
                temp = query(b, 0, l-1, n1, (int)n2, 0);
                if((temp&(temp-1))==0) printf("YES\n");
                else printf("NO\n");
            }
        }
        if(cmd[0]=='U'){
            scanf("%d", &n1);
            scanf("%s", n2c);
            int n = (int)strlen(n2c), count = n1;
            for(j = 0; j<n; j++){
                a[count] = n2c[j];
                count++;
            }
            if((l/log2(l))<n) build(b, 0, l-1, 0, a);
            else{
                for(j = 0; j<n; j++){
                    update(b, 0, l-1, 0, n1, n2c, j);
                    n1++;
                }
            }
        }
    }
    free(n2c);
    free(b);
    free(a);
    return 0;
}

