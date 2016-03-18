import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
public class Calc {
    static HashMap<String, Integer> vars = new HashMap<String, Integer>();
    static int index = 0;
    static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        String exp = in.nextLine();
        ArrayList<Token> tokens = new ArrayList<Token>();
        getTokens(exp, tokens);
        int ans = 0;
        try {
            ans = parseE(tokens);
        }
        catch (Exception e){
            System.out.print("error");
            System.exit(0);
        }
        if(index<tokens.size()){
            System.out.print("error");
            System.exit(0);
        }
        System.out.print(ans);
    }
    private static void getTokens(String exp, ArrayList<Token> tokens){
        int i, j, length = exp.length();
        for(i = 0; i<length; i++){
            if(exp.charAt(i)==' ') continue;
            if(exp.charAt(i)=='+') tokens.add(new Token("+", "PLUS"));
            if(exp.charAt(i)=='-') tokens.add(new Token("-", "SUB"));
            if(exp.charAt(i)=='*') tokens.add(new Token("*", "MUL"));
            if(exp.charAt(i)=='/') tokens.add(new Token("/", "DIV"));
            if(exp.charAt(i)=='=') tokens.add(new Token("=", "EQ"));
            if(exp.charAt(i)=='(') tokens.add(new Token("(", "OPEN"));
            if(exp.charAt(i)==')') tokens.add(new Token(")", "CLOSE"));
            if(Character.isDigit(exp.charAt(i))){
                for(j = i;j<length && !"+-*/()= ".contains(String.valueOf(exp.charAt(j))); j++);
                tokens.add(new Token(exp.substring(i, j), "NUM"));
                j--;
                i = j;
            }
            if(Character.isLetter(exp.charAt(i))){
                for(j = i; j<length && !"+-*/()= ".contains(String.valueOf(exp.charAt(j))); j++);
                tokens.add(new Token(exp.substring(i, j), "VAR"));
                j--;
                i = j;
            }
        }
    }
    private static int parseE(ArrayList<Token> tokens){
        int ans = parseT(tokens);
        while(index<tokens.size()&&(tokens.get(index).type=="PLUS" || tokens.get(index).type=="SUB")){
            if(tokens.get(index).type == "PLUS"){
                index++;
                ans+=parseT(tokens);
            }
            else if(tokens.get(index).type == "SUB"){
                index++;
                ans-=parseT(tokens);
            }
        }
        return ans;
    }
    private static int parseT(ArrayList<Token> tokens){
        int ans = parseF(tokens);
        while(index<tokens.size()&&(tokens.get(index).type=="MUL" || tokens.get(index).type=="DIV")){
            if(tokens.get(index).type == "MUL"){
                index++;
                ans*=parseF(tokens);
            }
            else if(tokens.get(index).type == "DIV"){
                index++;
                ans/=parseF(tokens);
            }
        }
        return ans;
    }
    private static int parseF(ArrayList<Token> tokens){
        int ans = 0;
        if(tokens.get(index).type == "NUM"){
            ans = Integer.valueOf(tokens.get(index).value);
            index++;
        }
        else if(tokens.get(index).type == "VAR"){
            if(!vars.containsKey(tokens.get(index).value)) tokens.get(index).getVar();
            ans = vars.get(tokens.get(index).value);
            index++;
        }
        else if(tokens.get(index).type == "OPEN"){
            index++;
            ans = parseE(tokens);
            if(tokens.get(index).type!="CLOSE"){
                System.out.print("error");
                System.exit(0);
            }
            index++;
        }
        else if(tokens.get(index).type == "SUB"){
            index++;
            ans = -parseF(tokens);
        }
        else{
            System.out.print("error");
            System.exit(0);
        }
        return ans;
    }
    private static class Token{
        String value;
        String type;
        public Token(String v, String t){
            value = v;
            type = t;
        }
        public void getVar(){
            vars.put(value, in.nextInt());
        }
    }
}