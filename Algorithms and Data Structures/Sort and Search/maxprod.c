#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, const char * argv[]) {
    int n, i, ch, zn, l = 0, r = 0, start = 0;
    float maxsum = 0, sum = 0;
    scanf("%d", &n);
    float *a = (float*)malloc(n*sizeof(float));
    for(i = 0; i<n; i++){
        scanf("%d/%d", &ch, &zn);
        a[i] = log(ch)-log(zn);
    }
    maxsum = a[0];
    for(i = 0; i<n;){
        sum+=a[i];
        if(sum>maxsum){
            maxsum = sum;
            l = start;
            r = i;
        }
        ++i;
        if(sum<0){
            sum = 0;
            start = i;
        }
    }
    printf("%d %d", l, r);
    free(a);
    return 0;
}

