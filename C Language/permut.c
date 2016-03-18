
#include <stdio.h>

int main(int argc, const char * argv[])
{
    int a[7];
    int b[7];
    int i, k, count;
    int acheck[7];
    int bcheck[7];
    for (i = 0; i <= 7; i++){
        acheck[i] = 0;
        bcheck[i] = 0;
    }
    count = 0;
    
    for (i = 0; i <= 7; ++i){
        scanf("%d", &a[i]);
    }
    
    for (k = 0; k <= 7; ++k){
        scanf("%d", &b[k]);
    }
    
    for (i = 0; i <= 7; ++i){
        for (k = 0; k <= 7; ++k){
            if ((a[i] == b[k]) & (acheck[i] == 0) & (bcheck[k] == 0)){
                ++count;
                acheck[i] = 1;
                bcheck[k] = 1;
            }
        }
    }
    if (count == 8)
    printf("yes");
    else
    printf("no");
    return 0;
}


