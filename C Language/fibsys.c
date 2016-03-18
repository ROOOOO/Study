#include <stdio.h>

int main(int argc, const char * argv[])
{
    int k, n, i, s, max;
    scanf("%d", &n);
    int a[n];
    s = 0;
    for (i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
    scanf("%d", &k);
    for (i = 1; i <= k; ++i)
    s = s+a[i];
    max = s;
    for (i = 2; i <= n-k+1; ++i){
        s = s - a[i-1] + a[i+k-1];
        if (s > max)
        (max = s);
    }
    printf("%d\n", max);
    return 0;
}