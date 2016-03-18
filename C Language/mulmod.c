
#include <stdio.h>

int main()
{
    unsigned long int b, k, a, n, z;
    int m[64];
    int i;
    
    scanf("%ld", &a);
    scanf("%ld", &b);
    scanf("%ld", &z);
    
    
    for (i = 63; i >= 0; --i)
    {
        k = b >> i;
        m[i] = (k & 1);
    }
    
    n = a*m[63]%z;
    
    for (i = 62; i >= 0; --i)
    n = (n*2+a*m[i]%z)%z;
    
    printf("%ld\n", n);
    
    return 0;
}

