#include <stdio.h>
#include <string.h>
void prefix(char *s, int* p){
    int k=0;
    int i;
    int len = (int)strlen(s);
    p[0] = 0;
    for(i = 1; i<len; i++){
        while((k>0)&&(s[k]!=s[i])){
            k = p[k-1];
        }
        if(s[k] ==s[i])
        k++;
        p[i] = k;
    }
}

int main(int argc, const char * argv[]) {
    char* s = argv[1];
    int p[strlen(s)], i, len = (int)strlen(s);
    prefix(s, p);
    for(i = 1; i< len; i++){
        if((i+1-p[i]<=p[i])&&((i+1)%(i+1-p[i])==0))
        printf("%d %d\n", i+1, (i+1)/(i+1-p[i]));
    }
    
    return 0;
}

