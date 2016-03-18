#include <stdio.h>
#include <string.h>
int max(int a, int b){
    if(a<b)
    return b;
    return a;
}
void suffix(char *s, int* p){
    int len = (int)strlen(s), k = len-1, i = len-2;
    p[len-1] = len-1;
    while(i>=0){
        while((k<len-1)&&(s[k]!=s[i])) k = p[k+1];
        if(s[k]==s[i]) k--;
        p[i] = k;
        i--;
    }
    //for(i = 0; i<len; i++) printf("%d ", p[i]);
    //printf("\n");
}
void delta1(char* s, int* d1){
    int len = (int)strlen(s), size = 28, i = 0, j = 0;
    while(i<size){
        d1[i] = len;
        i++;
    }
    while(j<len){
        d1[s[j]-97] = len-j-1;
        j++;
    }
}

void delta2(char *s, int* d2, int* p){
    int len = (int)strlen(s), i = 0;
    suffix(s, p);
    int t = p[0];
    while(i<len){
        while(t<i) t = p[t+1];
        d2[i] = -i+t+len;
        i++;
    }
    i = 0;
    while(i<len-1){
        t = i;
        while(t<len-1){
            t = p[t+1];
            if(s[i]!=s[t]) d2[t] = -(i+1)+len;
        }
        i++;
    }
}


int main(int argc, const char * argv[]) {
    char *t = argv[2];
    char *s = argv[1];
    int lens = (int)strlen(s), i = 0, lent = (int)strlen(t), k = lens-1;
    int d2[lens], p[lens], d1[28];
    delta2(s, d2, p);
    delta1(s, d1);
    while(k<lent){
        i = lens-1;
        while(t[k] == s[i]){
            if(i == 0){
                //printf("%d\n", i);
                printf("%d\n", k);
                break;
            }
            i--;
            k--;
        }
        k += max(d1[t[k]-97], d2[i]);
    }
    return 0;
}

