unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
    unsigned long min, max, mid;
    min = 0;
    max = nel - 1;
    while (min <=max){
        mid = (min+max)/2;
        if (compare(mid) == -1)
        min = mid + 1;
        else if (compare(mid) == 1)
        max = mid-1;
        else{
            return (mid);
            break;
        }
        
    }
    return (nel);
}

