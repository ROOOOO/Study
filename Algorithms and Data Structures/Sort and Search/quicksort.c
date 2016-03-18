#include <stdio.h>
int Partition(int*a, int low, int high);
void qs(int *a, int low, int high, int m);
void selection(int *a, int low, int high) {
    int i, j;
    int min, temp;
    for (i = low; i < high - 1; i++) {
        min = i;
        for(j = i + 1; j < high; j++) {
            if(a[j] < a[min])
            min = j;
        }
        if(min != i){
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}
int main(int argc, const char * argv[]) {
    int n, i, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int a[n];
    for( i = 0; i < n; i++)
    scanf("%d", &a[i]);
    
    qs(a, 0, n, m);
    for( i = 0; i < n; i++)
    printf("%d ", a[i]);
    return 0;
}

void qs(int *a, int low, int high, int m){
    int i;
    while (high-low>=m){
        i = Partition(a, low, high);
        if(high-i<i){
            qs(a, low, i, m);
            low = i+1;
        }
        else{
            qs(a, i+1, high, m);
            high = i;
        }
    }
    selection(a, low, high);
}

int Partition(int*a, int low, int high){
    int elem = (low+high)/2;
    int i, j, temp;
    high--;
    i = low;
    j = low;
    temp = a[high];
    a[high] = a[elem];
    a[elem] = temp;
    while (j<high){
        if (a[j] <= a[high]){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
        }
        j++;
    }
    temp = a[i];
    a[i] = a[high];
    a[high] = temp;
    return i;
}