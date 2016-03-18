import java.util.Scanner;
public class MaxNum {
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int count = input.nextInt(), len_i, len_j;
        int[] a = new int[count];
        String[] aStr = new String[count];
        String temp = new String();
        for(int i = 0; i < count; i++){
            a[i] = input.nextInt();
            aStr[i] = Integer.toString(a[i]);
        }
        for(int i = 0; i < count-1; i++){
            for(int j = i+1; j<count; j++){
                if(aStr[j].startsWith(aStr[i])){
                    len_j = aStr[j].length();
                    len_i = aStr[i].length();
                    for(int k = len_i; k < len_j; k++){
                        if(aStr[j].charAt(k) > aStr[i].charAt(len_i-1)){
                            temp = aStr[i];
                            aStr[i] = aStr[j];
                            aStr[j] = temp;
                            break;
                        }
                        if((aStr[j].charAt(k) == aStr[i].charAt(len_i-1))&&(aStr[j].charAt(0)<aStr[j].charAt(k))){
                            temp = aStr[i];
                            aStr[i] = aStr[j];
                            aStr[j] = temp;
                            break;
                        }
                        if(aStr[j].charAt(k) <= aStr[i].charAt(len_i-1)) break;
                    }
                }
                else if(aStr[i].startsWith(aStr[j])){
                    len_j = aStr[j].length();
                    len_i = aStr[i].length();
                    for(int k = len_j; k < len_i; k++){
                        if(aStr[i].charAt(k) < aStr[j].charAt(len_j-1)){
                            temp = aStr[i];
                            aStr[i] = aStr[j];
                            aStr[j] = temp;
                            break;
                        }
                        if((aStr[i].charAt(k) == aStr[j].charAt(len_j-1))&&(aStr[i].charAt(0)>aStr[i].charAt(k))){
                            temp = aStr[i];
                            aStr[i] = aStr[j];
                            aStr[j] = temp;
                            break;
                        }
                        if(aStr[i].charAt(k) >= aStr[j].charAt(len_j-1)) break;
                    }
                }
                
                else if (aStr[i].compareTo(aStr[j]) < 0){
                    temp = aStr[i];
                    aStr[i] = aStr[j];
                    aStr[j] = temp;
                }
            }
        }
        for(int i = 0; i<count; i++)
            System.out.print(aStr[i]);
    }
}

