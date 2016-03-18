#include <stdio.h>
void zero(int *p){
    int i;
    for(i = 0; i < 256; i++)
    p[i] = 0;
}

int main(int argc, const char * argv[]) {
    int n, i, j, count=0;
    scanf("%d", &n);
    int x1[n], array[256];
    union int32{
        int x;
        unsigned char bytes[4];
    }int32[n];
    for(i = 0; i < n; i++)
    scanf("%d", &int32[i].x);
    for(i = 0; i < n; i++){
        if(int32[i].x<0)
        count++;
    }
    for(j = 0; j < 3; j++){
        zero(array);
        for(i = 0; i<n; i++){
            array[(unsigned int)(int32[i].bytes[j])] +=1;
        }
        for(i = 1; i<256; i++){
            array[i]+=array[i-1];
        }
        for(i = n-1; i>=0; i--){
            array[(unsigned int)int32[i].bytes[j]] -= 1;
            x1[array[(unsigned int)int32[i].bytes[j]]] = int32[i].x;
        }
        
        for(i = 0; i<n; i++)
        int32[i].x = x1[i];
    }
    zero(array);
    for(i = 0; i<n; i++){
        array[(unsigned int)(int32[i].bytes[3])] +=1;
    }
    for(i = 1; i<256; i++){
        array[i]+=array[i-1];
    }
    for(i = n-1; i>=0; i--){
        if(int32[i].x>=0){
            array[(unsigned int)int32[i].bytes[3]] -= 1;
            x1[array[(unsigned int)int32[i].bytes[3]]+count] = int32[i].x;
        }
        else{
            array[(unsigned int)int32[i].bytes[3]] -= 1;
            x1[array[(unsigned int)int32[i].bytes[3]]-n+count] = int32[i].x;
        }
    }
    for(i = 0; i<n; i++)
    int32[i].x = x1[i];
    
    
    for(i = 0; i < n; i++)
    printf("%d ", int32[i].x);
    return 0;
}

