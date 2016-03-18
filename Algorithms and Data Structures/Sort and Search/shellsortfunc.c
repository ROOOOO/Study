void shellsort(unsigned long nel,
               int (*compare)(unsigned long i, unsigned long j),
               void (*swap)(unsigned long i, unsigned long j))
{
    int k, mem, loc, i, j, temp;
    int d[100];
    d[0] = 0;
    d[1] = 1;
    mem = 0;
    temp = 0;
    for (k = 2; d[k-1] < nel; k++ ){
        d[k] = d[k-1] + d[k-2];
        mem = k-1;
    }
    for(k = mem; k > 1; k--){
        for(i = d[k]; i < nel; i++){
            for (j = i; j>=d[k];){
                if ((compare (j, j-d[k])) < 0){
                    swap (j, j-d[k]);
                    j -= d[k];
                }
                else break;
            }
        }
    }
}