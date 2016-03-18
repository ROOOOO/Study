void bubblesort(unsigned long nel,
                int (*compare)(unsigned long i, unsigned long j),
                void (*swap)(unsigned long i, unsigned long j))
{
    int LeftLim, RightLim, i, count, j=1;
    RightLim = nel-1;
    count = 0;
    for (LeftLim = 0; LeftLim < RightLim;){
        for (i = LeftLim; i < RightLim; i++)
        {
            if (compare (i, i+1) > 0)
            {
                swap(i, i+1);
                count = i;
            }
        }
        RightLim = count;
        
        for (i = RightLim; i > LeftLim; i--)
        {
            if (compare (i, i-1) < 0)
            {
                swap(i, i-1);
                count = i;
            }
        }
        LeftLim = count;
    }
}

