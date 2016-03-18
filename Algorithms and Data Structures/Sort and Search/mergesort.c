#include <stdio.h>
#include <stdlib.h>
void InsertionSort(int *a, int lb, int rb);
void merge(int *a, int lb, int mid, int rb);

void merge_sort(int *a, int lb, int rb){
    int mid = (rb- lb)/2;
    if(rb - lb <= 5)
    InsertionSort(a, lb, rb);
    else{
        merge_sort(a, lb, mid+1);
        merge_sort(a, mid+1, rb);
        merge(a, lb, mid, rb);
    }
    
}
void InsertionSort(int *a, int lb, int rb){
    int i, j, temp;
    for (i = lb; i < rb; i++)
    for (j = i; j && abs(a[j]) < abs(a[j-1]); j--)
    {
        temp = a[j];
        a[j] = a[j-1];
        a[j-1] = temp;
    }
}
void merge(int *a, int lb, int mid, int rb){
    int buff[rb-lb+1];
    int p1 = 0, p2 = mid+1, i;
    int temp = 0;
    while((mid >= p1) && (rb > p2)){
        if(abs(a[p1]) > abs(a[p2])){
            buff[temp] = a[p2];
            p2++;
            temp++;
        }
        else{
            buff[temp] = a[p1];
            p1++;
            temp++;
        }
    }
    while (mid >= p1){
        buff[temp] = a[p1];
        p1++;
        temp++;
    }
    while (rb >= p2){
        buff[temp] = a[p2];
        p2++;
        temp++;
    }
    for(i = 0; i< rb-lb+1; i++)
    a[lb+i] = buff[i];
    
}
int main(int argc, const char * argv[]) {
    int n, i;
    scanf("%d", &n);
    int a[n];
    for (i = 0; i<n; i++)
    scanf("%d", &a[i]);
    merge_sort(a, 0, n);
    for (i = 0; i<n; i++)
    printf("%d ", a[i]);
    return 0;
}