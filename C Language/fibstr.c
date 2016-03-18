#include <stdio.h>
#include <stdlib.h>


char *fibstr(int n);
int main(int argc, const char * argv[])
{
    int n;
    scanf("%d", &n);
    char *x = fibstr(n);
    printf("%s", x);
    free(x);
    return 0;
    
    
}

char *fibstr(int n)
{
    int i, l, j;
    int array[n];
    char *string;
    array[0] = 1;
    array [1] = 1;
    for (i = 2; i < n; ++i)
    array[i] = array[i-1]+array[i-2];
    l = array[n-1];
    string = (char*)malloc((l+1)*sizeof(char));
    string[l] = '\0';
    if (n == 1){
        string[0] = 'a';
        return (string);
    }
    else if (n == 2){
        string[0] = 'b';
        return (string);
    }
    string[0] = 'a';
    string[1] = 'b';
    for(i = 2; i < n-1; i++){
        for (j = array[i]; j > 0; j--){
            string[j+array[i-1]-1] = string[j-1];
        }
        for(j = 0; j < array[i-1]; j++)
        string[j] = string[array[i]+j];
    }
    
    return string;
}