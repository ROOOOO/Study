int strdiff(char *a, char *b)
{
    
    int i, j;
    char c = 1;
    int count = 0;
    for(i = 0; ((a[i] != '\0') || (b[i] != '\0')); ++i){
        c = 1;
        for (j = 0; j < 8; j++){
            if ((a[i] & c)==(b[i] & c)){
                count++;
                c *= 2;
            }
            else{
                return(count);
            }
        }
    }
    count = -1;
    return count;
    
}