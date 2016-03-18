#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char string[1000000];
    int i, j, temp = 0;
    int array[123];
    fgets(string, 1000000, stdin);
    int n = (int)strlen(string);
    for (i = 0; i < 123; i++)
    array[i] = 0;
    for (i = 0; i < n; i++){
        array[string[i]] +=1;
    }
    for(i = 97; i< 123; i++){
        for(j = 0; j < array[i]; j++){
            string[temp] = i;
            temp++;
        }
        
    }
    string[n-1] = '\0';
    printf("%s", string);
    return 0;
}