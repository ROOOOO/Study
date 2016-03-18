#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char *concat(char **s, int n);
int main(int argc, const char * argv[])
{
    int n,i;
    scanf("%d\n", &n);
    char s[n][100];
    char *str[n];
    for (i = 0; i < n; i++){
        fgets(s[i], 100, stdin);
        s[i][strlen(s[i])-1] = '\0';
        str[i] = s[i];
    }
    char *string = concat(str, n);
    printf("%s", string);
    free(string);
    return 0;
}

char *concat(char **s, int n){
    int i, mem, ad;
    mem = 0;
    for (i = 0; i < n; i++)
    mem += strlen(s[i]);
    char *stroka;
    stroka = (char*)malloc((mem+1)*sizeof(char));
    //strcpy(stroka, *s);
    ad = 0;
    for (i = 0; i < n; ++i){
        strcpy(stroka+ad, *(s+i));
        ad += strlen(*(s+i));
    }
    return (stroka);
}