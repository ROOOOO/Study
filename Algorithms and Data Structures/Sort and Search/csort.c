#include <stdio.h>
#include <string.h>

int wcount(char *s)
{
    int i, count;
    count = 0;
    unsigned long length;
    length = strlen(s);
    s[length] = ' ';
    for (i = 0; i < length; ++i){
        if((s[i] != ' ') && (s[i+1] == ' '))
        count++;
    }
    s[length] = '\0';
    return (count);
}
void csort(char *src, char *dest);
int main(int argc, const char * argv[]) {
    char array[100];
    char buf[100];
    fgets(array, 100, stdin);
    csort(array, buf);
    return 0;
}
void csort(char *src, char *dest)
{
    int i = 0, j, mem = 1,begin = 0, wordindex = 0, lenght = 0, k;
    int words = wcount(src);
    int arr[words];
    int keys[words][2];
    int count[words][2];
    for(j = 0; j < words; j++){
        for (i = begin; (src[i+1]!=' ')&&(src[i+1]!='\n'); i++){
            begin++;
        }
        keys[j][0] = wordindex;
        keys[j][1] = begin-wordindex+1;
        for (i = begin; src[i+1]==' '; i++){
            begin++;
            wordindex=begin+1;
        }
        
    }
    
    for(i = 0; i < words; i++)
    arr[i] = 0;
    for(i = 0; i < words; i++){
        for(j = i + 1; j < words; j++){
            if(keys[j][1] < keys[i][1])
            arr[i]++;
            else
            arr[j]++;
        }
    }
    for(i = 0; i < words; i++){
        count[arr[i]][1]=keys[i][1];
        count[arr[i]][0]=keys[i][0];
    }
    
    for(i = 0; i< words; i++)
    lenght += count[i][1];
    lenght += words;
    mem = 0;
    begin = 0;
    for (i = 0; i < words; i++){
        k = 0;
        for (j = mem; j < count[i][1]+ begin; j++){
            dest[j] = src[count[i][0]+k];
            mem++;
            k++;
        }
        dest[mem] = ' ';
        mem++;
        begin = mem;
    }
    dest[lenght-1] = '\0';
    
    printf("%s", dest);
}

