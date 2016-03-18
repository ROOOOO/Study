import java.util.Scanner;
import static java.lang.Math.*;
public class Kth {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long k = in.nextLong(), j, startk = 0, start = 1;
        long[] a = new long[19];
        int i, rank = 0;
        String temp = new String();
        a[0] = 8;
        for(i = 1; i < 18; i++){
            a[i] = (long)((pow(10, i+1)-pow(10, i))*(i+1)+a[i-1]);
            if(k < a[i]){
                rank = i+1;
                break;
            }
        }
        for(i = 0; i<=rank; i++){
            for(j = (long)((i+1)*pow(10, i)); j>i; j/=10){
                while(startk<=a[i]) {
                    if (startk + j <= k) {
                        startk += j;
                        start += j / (i + 1);
                    } else break;
                }
            }
        }
        temp+=start;
        System.out.println(temp.charAt((int)(k-startk)));
    }
}

