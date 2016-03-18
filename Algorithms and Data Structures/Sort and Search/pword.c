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
    char* s = argv[1];
    char* t = argv[2];
    
    int k=0, lent = (int)strlen(t), lens = (int)strlen(s), sum = 0;
    int p[lens];
    int q = 0;
    int n = (int)lent;
    prefix(s, p);
    while(lent>0){
        while(k<lent){
            while((q>0)&&(s[q]!=t[k]))
            q = p[q-1];
            if (s[q]==t[k])
            q++;
            k++;
        }
        if(q==0){
            printf("no");
            return 0;
        }
        sum +=q;
        lent -= q;
        t[lent] = '\0';
        k = 0;
        q = 0;
    }
    if(n-sum==0)
    printf("yes");
    return 0;
}

