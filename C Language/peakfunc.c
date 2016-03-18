unsigned long peak(unsigned long nel,
                   int (*less)(unsigned long i, unsigned long j))
{
    unsigned long peaks = 0;
    unsigned long mid = 0, min, max;
    min = 0;
    max = nel-1;
    unsigned long remainder;
    while(min < max){
        remainder = (max % 2 + mid % 2) / 2;
        mid = max/2 + min/2 + remainder;
        if ((less(mid, mid - 1) == 0) && (less(mid, mid+1) == 0)){
            peaks = mid;
            return peaks;
            break;
        }
        else if (less (mid, mid-1) == 0)
        min = mid;
        else if(less(mid, mid+1) == 0)
        max = mid;
        else if ((less(mid, mid - 1) == 1) && (less(mid, mid+1) == 1))
        max = mid;
    }
    return(peaks);
}