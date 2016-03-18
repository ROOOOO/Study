
#include <stdio.h>

int main(int argc, const char * argv[])
{
    int strok, stolb, i, j, coord1, coord2, maximum, minimum;
    scanf("%d%d", &strok, &stolb);
    int matrix[strok][stolb];
    int max[strok];
    int min[stolb];
    for (i = 0; i < strok; ++i)
    {
        for (j = 0; j < stolb; ++j)
        scanf ("%d", &matrix[i][j]);
    }
    
    
    for(i = 0; i < strok; ++i)
    max[i] = 0;
    for(j = 0; j < stolb; ++j)
    min[j] = matrix[0][j];
    
    
    
    for (i = 0; i < strok; ++i)
    {
        for (j = 0; j < stolb; ++j)
        {if (matrix[i][j] < min[j])
            (min[j] = matrix[i][j]);
            
            if (matrix[i][j] > max[i])
            (max[i] = matrix[i][j]);
        }
        
    }
    
    coord1 = NULL;
    coord2 = NULL;
    maximum = 0;
    minimum = 2147483647;
    
    
    if (strok == 1){
        coord1 = 0;
        for (j = 0; j < stolb; ++j)
        if( matrix[0][j] > maximum){
            coord2 = j;
            maximum = matrix[0][j];
        }
        printf("%d %d", coord1, coord2);
    }
    else if (stolb == 1){
        coord2 = 0;
        for (i = 0; i < strok; ++i)
        if( matrix[i][0] < minimum){
            coord1 = i;
            minimum = matrix[i][0];
        }
        printf("%d %d", coord1, coord2);
    }
    else {
        for( i = 0; i < strok; ++i){
            for( j = 0; j < stolb; ++j){
                if (max[i] == min[j])
                {
                    coord1 = i;
                    coord2 = j;
                    break;
                }
            }
        }
        if((coord1 != NULL) && (coord2 != NULL))
        (printf("%d %d", coord1, coord2));
        else printf("none");
    }
    return 0;
}

