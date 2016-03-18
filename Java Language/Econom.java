import java.util.ArrayList;
import java.util.Scanner;
public class Econom {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        ArrayList<String> exprs = new ArrayList<String>();
        String exp = new String(input.nextLine());
        int count = 0, scb = 0, i, j, len = exp.length();;
        for(i = 0; i < len; i++){
            if(exp.charAt(i) == '('){
                scb++;
                count++;
                for(j = i+1; scb != 0; j++, count++){
                    if(exp.charAt(j) == '(') scb++;
                    if(exp.charAt(j) == ')') scb--;
                }
                if(!(exprs.contains(exp.substring(i, i+count)))) exprs.add(exp.substring(i, i+count));
                count = 0;
            }
        }
        System.out.print(exprs.size());
    }
}

