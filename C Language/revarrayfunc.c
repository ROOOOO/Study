void revarray(void *base, unsigned long nel, unsigned long width)
{
    int i, j;
    int n;
    for( j = 0; j < width/sizeof(char); j++){
        for(i = 0; i < nel/2; ++i)
        {
            n = *(char *)(base+i*width);
            *(char *)(base+i*width) = *(char *)(base + nel*width - 1*width - i*width);
            *(char *)(base + nel*width - 1*width - i*width) = n;
            
            
        }
        base = base+sizeof(char);
    }
}