int maxarray(void *base, unsigned long nel, unsigned long width,
             int (*compare)(void *a, void *b))
{
    int i, max, comp;
    max = 0;
    void *maxbase = base;
    for( i = 0; i < nel-1; ++i){
        comp = compare((base+(i + 1)*width), maxbase);
        if (comp >= 1){
            (max = i+1);
            maxbase = base+(i + 1)*width;
        }
    }
    return (max);
}