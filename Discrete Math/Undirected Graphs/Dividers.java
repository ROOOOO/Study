import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Dividers {
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long x = in.nextLong();
        int i, j, k, mult = 1, c = 0;
        int n = (int)Math.sqrt(x)+1;
        ArrayList<Long> divs = new ArrayList<Long>();
        ArrayList<String> ans = new ArrayList<String>();
        for(i = 1; i<n; i++){
            if(x%i==0){
                if(x/i!=i) {
                    divs.add((long) i);
                    divs.add(x / i);
                }
                else divs.add((long) i);
            }
        }
        System.out.println("graph {");
        n = divs.size();
        long[] dvs = new long[n];
        for(i = 0; i<n; i++) dvs[i] = divs.get(i);
        Arrays.sort(dvs);
        for(i = n-1; i>=0; i--)System.out.println("\t\t"+dvs[i]);
        for(i = n-1; i>=0; i--){
            for(j = i-1; j>=0; j--){
                c = 0;
                if(dvs[i]%dvs[j]==0) {
                    for (k = i-1; k >= 0; k--) {
                        if ((dvs[k] % dvs[j] == 0)&&(k!=j)&&(dvs[i]%dvs[k]==0)){
                            c = 1;
                            break;
                        }
                    }
                    if (c == 0) {
                        System.out.println("\t\t"+dvs[i] + "--" + dvs[j]);
                    }
                }
            }
        }
        System.out.print("}");
    }
}