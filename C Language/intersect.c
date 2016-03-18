
#include <stdio.h>

int main(int argc, const char * argv[])
{
    unsigned int mnozhestvo1, mnozhestvo2, peresechenie;
    mnozhestvo1 = 0;
    mnozhestvo2 = 0;
    unsigned int n1, n2, a, k, count1, count2;
    int i;
    scanf("%d", &n1);
    count1 = 0;
    count2 = 0;
    for (i = 0; i < n1; ++i)
    {
        scanf("%d", &a);
        k = 0;
        if (a == 0)
        (count1 = 1);
        k >>=  (a-1);
        k |= 1;
        k <<=  (a-1);
        mnozhestvo1 |= k;
    }
    
    if ((count1 != 0) & (count2 != 0))
    printf("0 ");
    
    scanf("%d", &n2);
    for (i = 0; i < n2; ++i)
    {
        scanf("%d", &a);
        k = 0;
        if (a == 0)
        (count2 = 1);k = k >> (a-1);
        k |= 1;
        k <<= (a-1);
        mnozhestvo2 = mnozhestvo2 | k;
    }
    
    if ((count1 != 0) & (count2 != 0))
    printf("0 ");
    
    peresechenie = mnozhestvo1 & mnozhestvo2;
    for (i = 0; i < 31; ++i){
        k = peresechenie >> i;
        if ((k & 1) == 1)
        (printf("%d ", i+1));
    }
    
    
    return 0;
}