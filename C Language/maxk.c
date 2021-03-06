/*Дан целочисленный массив, размер которого не превышает 1000000, и число k, которое меньше или равно длине массива. Составьте программу maxk.c, определяющую, какие k подряд идущих элементов массива имеют максимальную сумму.
 Программа должна считывать из стандартного потока ввода размер массива, его элементы и число k, а затем выводить в стандартный поток вывода максимальную сумму k подряд идущих элементов массива.
 В программе запрещается обращаться к одному и тому же элементу массива более двух раз, а также объявлять какие бы то ни было вспомогательные массивы.*/

#include <stdio.h>
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