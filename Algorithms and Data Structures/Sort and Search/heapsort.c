#include <stdio.h>
#include <string.h>
int compare(const void *a, const void *b){
    char *c_a = (char*)a, *c_b = (char*)b;
    int key_a = 0, key_b = 0, i;
    for(i = 0; i<strlen(c_a); i++){
        if(c_a[i] == 'a')
        key_a++;
    }
    for(i = 0; i<strlen(c_b); i++){
        if(c_b[i] == 'a')
        key_b++;
    }
    return key_a - key_b;
}
void swap(int i, int k, void *a, unsigned long width){
    int j;
    int temp;
    for(j = 0;j<width;j++){
        temp = *(char*)(a+k*width*(sizeof(char))+j*(sizeof(char)));
        *(char*)(a+k*width*(sizeof(char))+j*(sizeof(char))) = *(char*)(a+i*width*(sizeof(char))+j*(sizeof(char)));
        *(char*)(a+i*width*(sizeof(char))+j*(sizeof(char))) = temp;
        
    }
}
void newelem(void *a, int k, unsigned long n, unsigned long width){
    int left = 2*k+1;
    int right = left+1;
    int MaxChild = left;
    while(MaxChild < n) {
        
        if((right < n) && (compare(a+left*width*sizeof(char), a+right*width*sizeof(char))<0))
        MaxChild = right;
        if(compare(a+k*width*sizeof(char), a+MaxChild*width*sizeof(char))>=0)
        break;
        else
        swap(k, MaxChild, a, 100);
        k = MaxChild;
        left = 2 * k + 1;
        right = left + 1;
        MaxChild = left;
    }
}
void hsort(void *base, size_t nel, size_t width,
           int (*compare)(const void *a, const void *b)) {
    int i;
    for(i = nel/2-1; i>=0; i--)
    newelem(base, i, nel, width);
    
    for (i = nel-1; i>0; i--){
        swap(0, i, base, width);
        newelem(base, 0, i, width);
    }
}

int main(int argc, const char * argv[]){
    
    int i;
    unsigned long n;
    scanf("%ld\n", &n);
    char a[n][100];
    for(i = 0; i < n; i++)
    fgets(a[i], 100, stdin);
    hsort(a, n, 100, compare);
    for(i = 0; i < n; i++)
    printf("%s", a[i]);
    
    return 0;
}

