#include <stdio.h>
#include <string.h>
void prefix(char *s, int* p){
    int k=0;
    int i;
    unsigned long len = strlen(s);
    for(i = 0; i<len;i++)
    p[i] = 0;
    for(i = 1; i<len; i++){
        while((k>0)&&(s[k]!=s[i])){
            k = p[k-1];
        }
        if(s[k] ==s[i])
        k++;
        p[i] = k;
    }
}
int main(int argc, char * argv[]) {
    char *s = argv[1];
    char *t = argv[2];
    unsigned long k=0, lent = strlen(t), lens = strlen(s), ans;
    int p[lens];
    int q = 0;
    prefix(s, p);
    while(k<lent){
        while((q>0)&&(s[q]!=t[k]))
        q = p[q-1];
        if (s[q]==t[k])
        q++;
        if (q == lens){
            ans = k-lens+1;
            printf("%lu ", ans);
        }
        k++;
    }
    return 0;
}

