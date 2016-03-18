#include <stdio.h>
#include <math.h>
void zero(int *p){
    int i;
    for(i = 0; i < 10; i++)
    p[i] = 0;
}
int main(int argc, const char * argv[]) {
    int n, i, j, temp = 1;
    scanf("%d", &n);
    int d[n];
    int d1[n];
    int array[10];
    zero(array);
    struct date{
        int day;
        int month;
        int year;
    } dates[n];
    
    for(i = 0; i<n; i++){
        scanf("%d", &dates[i].year);
        scanf("%d", &dates[i].month);
        scanf("%d", &dates[i].day);
    }
    for(i = 0; i<n; i++)
    d[i] = dates[i].year*10000+dates[i].month*100+dates[i].day;
    for(j = 10; j <= 100000000; j*=10){
        temp = j/10;
        zero(array);
        for(i = 0; i<n; i++){
            array[(d[i]%j)/temp] +=1;
        }
        for(i = 1; i<10; i++){
            array[i]+=array[i-1];
        }
        for(i = n-1; i>=0; i--){
            array[(d[i]%j)/temp] -= 1;
            d1[array[(d[i]%j)/temp]] = d[i];
        }
        for(i = 0; i<n; i++)
        d[i] = d1[i];
    }
    for(i = 0; i<n; i++){
        dates[i].year = d1[i]/10000;
        dates[i].month = d1[i]%10000/100;
        dates[i].day = d1[i]%100;
    }
    for(i = 0; i<n; i++){
        printf("%d ", dates[i].year);
        printf("%d ", dates[i].month);
        printf("%d\n", dates[i].day);
    }
    return 0;
}

