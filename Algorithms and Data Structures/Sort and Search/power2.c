#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    int n, i, j, k, count, count1, num, sum;
    scanf("%d", &n);
    int a[n];
    count = 0;
    k = 0;
    for (i = 0; i < n; i++)
    scanf ("%d", &a[i]);
    num = pow(2, n);
    for (count = 0; count < num-1;){
        count += 1;
        count1 = count;
        sum = 0;
        for (j = 0; j < n; j++){
            if ((count1 & 1) == 1)
            sum += a[j];
            count1 >>= 1;
            
        }
        if (((sum & (sum -1)) == 0) & (sum != 0))
        k += 1;
    }
    printf("%d", k);
    
    return 0;
}