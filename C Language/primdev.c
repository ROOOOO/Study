#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, const char * argv[])
{
    
    long int n, n1, i, j;
    scanf("%ld", &n);
    if (n < 0)
    n = -n;
    n1 = n;
    n = sqrt(n);
    char *a;
    a = (char *)malloc((n + 1) * sizeof(char));
    
    for (i = 0; i <= n; ++i)
    a[i] = 1;
    for ( i = 2; i <= n; ++i)
    {
        while ((a[i] != 0) && (n1%i==0) && (n1 / i != 1))
        {
            n1 /= i;
        }
        for  ( j = i; j <= n; j += i)
        a[j] = 0;
    }
    printf("%ld", n1);
    free(a);
    return 0;
}