#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]) {
    char *s = argv[1];
    char *t = argv[2];
    int lens = (int)strlen(s), i = 0, lent = (int)strlen(t), k = lens-1, j, temp = lens;
    int d1[28][lens];
    
    for(i = 0; i<28; i++) {
        for(j = 0; j<lens; j++){
            if(s[j]-97==i) temp = lens-j-1;
            d1[i][j]=temp;
        }
        temp = lens;
    }
    
    
    while(k<lent){
        i = lens-1;
        while(t[k] == s[i]){
            if(i == 0){
                printf("%d\n", k);
                return 0;
            }
            i--;
            k--;
        }
        k += d1[t[k]-97][i];
    }
    k = lent;
    printf("%d\n", k);
    return 0;
}

