import java.util.ArrayList;
import java.util.Scanner;
public class MinDist {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        char x = in.next().charAt(0), y = in.next().charAt(0);
        ArrayList<Integer> xl = new ArrayList<Integer>(), yl = new ArrayList<Integer>();
        int len = s.length(), lenXl, lenYl, min = len;
        for(int i = 0; i < len; i++){
            if(s.charAt(i)==x) xl.add(i);
            if(s.charAt(i)==y) yl.add(i);
        }
        lenXl = xl.size();
        lenYl = yl.size();
        for(int i = 0; i < lenXl; i++){
            for(int j = 0; j < lenYl; j++){
                if(Math.abs(xl.get(i)-yl.get(j))<min){
                    min = Math.abs(xl.get(i)-yl.get(j));
                }
            }
        }
        System.out.println(min-1);
    }
}

