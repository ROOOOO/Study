import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class FormulaOrder {
    static int index, varIndex, valIndex;
    static Vertex[] graph;
    static ArrayList<Vertex> ans;
    static ArrayList<String> vars;
    static HashMap<String, Vertex> formulas;
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        ArrayList<String> expressions = new ArrayList<String>();
        while(in.hasNextLine()) expressions.add(in.nextLine());
        int count = expressions.size();
        ArrayList<Token>[] allLex = new ArrayList[count];
        graph = new Vertex[count];
        ans = new ArrayList<Vertex>();
        formulas = new HashMap<String, Vertex>();
        for(int i = 0; i<count; i++){
            allLex[i] = new ArrayList<Token>();
            getTokens(expressions.get(i), allLex[i]);
            graph[i] = new Vertex(allLex[i], expressions.get(i));
            graph[i].used = 0;
        }
        vars = new ArrayList<String>();
        putFormulas(graph);
        makeGraph(graph);
        topSort();
        for(Vertex item : ans){
            System.out.println(item.formula);
        }
        
    }
    enum tag_t{PLUS, DIV, MUL, SUB, EQ, OPEN, CLOSE, COMMA, NUM, VAR};
    static class Token{
        String value;
        tag_t tag;
        String expr;
        public Token(String value, tag_t tag){
            this.value = value;
            this.tag = tag;
            this.expr = "";
        }
        public String getValue() {
            return value;
        }
        
        public tag_t getTag() {
            return tag;
        }
    }
    static class Vertex{
        ArrayList<Token> value;
        ArrayList<Vertex> next;
        String formula;
        int used;
        public Vertex(ArrayList<Token> v, String f){
            this.value = v;
            this.formula = f;
            next = new ArrayList<Vertex>();
            int s = value.size();
        }
    }
    static void dfs(Vertex v){
        v.used = 1;
        for(Vertex item : v.next){
            if(item.used==0){
                dfs(item);
            }
            else if (item.used==1){
                System.out.print("cycle");
                System.exit(0);
            }
        }
        v.used = 2;
        ans.add(v);
    }
    static void topSort(){
        for(Vertex item :graph){
            if(item.used==0){
                dfs(item);
            }
        }
    }
    private static void getTokens(String exp, ArrayList<Token> tokens){
        int i, j, length = exp.length();
        for(i = 0; i<length; i++){
            if(exp.charAt(i)==' ') continue;
            else if(exp.charAt(i)=='+') tokens.add(new Token("+", tag_t.PLUS));
            else if(exp.charAt(i)=='-') tokens.add(new Token("-", tag_t.SUB));
            else if(exp.charAt(i)=='*') tokens.add(new Token("*", tag_t.MUL));
            else if(exp.charAt(i)=='/') tokens.add(new Token("/", tag_t.DIV));
            else if(exp.charAt(i)=='=') tokens.add(new Token("=", tag_t.EQ));
            else if(exp.charAt(i)=='(') tokens.add(new Token("(", tag_t.OPEN));
            else if(exp.charAt(i)==')') tokens.add(new Token(")", tag_t.CLOSE));
            else if(exp.charAt(i)==',') tokens.add(new Token(",", tag_t.COMMA));
            else if(Character.isDigit(exp.charAt(i))){
                for(j = i;j<length && Character.isDigit(exp.charAt(j)); j++);
                tokens.add(new Token(exp.substring(i, j), tag_t.NUM));
                j--;
                i = j;
            }
            else if(Character.isLetter(exp.charAt(i))){
                for(j = i; j<length && (Character.isDigit(exp.charAt(j)) || Character.isLetter(exp.charAt(j))); j++);
                tokens.add(new Token(exp.substring(i, j), tag_t.VAR));
                j--;
                i = j;
            }
            else{
                System.out.print("syntax error");
                System.exit(0);
            }
        }
    }
    private static void makeGraph(Vertex[] graph){
        for(Vertex item : graph){
            index = 0;
            valIndex = 0;
            varIndex = 0;
            try{
                parseForm(item);
            }
            catch (Exception e){
                System.out.print("syntax error");
                System.exit(0);
            }
            if(index<item.value.size()||valIndex!=varIndex){
                System.out.print("syntax error");
                System.exit(0);
            }
        }
    }
    private static Vertex putFormulas(Vertex[] graph){
        for(Vertex v : graph){
            for(Token item : v.value){
                if(item.tag==tag_t.VAR) formulas.put(item.value, v);
                else if(item.getTag()==tag_t.EQ) break;
            }
        }
        return null;
    }
    private static void parseForm(Vertex v){
        parseVariable(v);
        if(v.value.get(index).tag!=tag_t.EQ){
            System.out.print("syntax error");
            System.exit(0);
        }
        index++;
        parseExpr(v);
    }
    private static void parseVariable(Vertex v){
        if(v.value.get(index).tag!=tag_t.VAR){
            System.out.print("syntax error");
            System.exit(0);
        }
        if(!vars.contains(v.value.get(index).value)) vars.add(v.value.get(index).value);
        else{
            System.out.print("syntax error");
            System.exit(0);
        }
        index++;
        varIndex++;
        while(index < v.value.size() && v.value.get(index).tag==tag_t.COMMA){
            index++;
            parseVariable(v);
        }
    }
    private static void parseExpr(Vertex v){
        valIndex++;
        parseE(v);
        while(index < v.value.size() && v.value.get(index).tag==tag_t.COMMA){
            index++;
            parseExpr(v);
        }
    }
    private static void parseE(Vertex v){
        parseT(v);
        while(index<v.value.size()&&(v.value.get(index).tag == tag_t.PLUS || v.value.get(index).tag == tag_t.SUB)){
            index++;
            parseT(v);
        }
    }
    private static void parseT(Vertex v){
        parseF(v);
        while(index<v.value.size()&&(v.value.get(index).tag==tag_t.MUL || v.value.get(index).tag==tag_t.DIV)) {
            index++;
            parseF(v);
        }
    }
    private static void parseF(Vertex v){
        if(v.value.get(index).tag == tag_t.NUM) index++;
        else if(v.value.get(index).tag == tag_t.VAR){
            if(formulas.containsKey(v.value.get(index).value)){
                v.next.add(formulas.get(v.value.get(index).value));
            }
            else{
                System.out.print("syntax error");
                System.exit(0);
            }
            index++;
        }
        else if(v.value.get(index).tag == tag_t.OPEN){
            index++;
            parseE(v);
            if(v.value.get(index).tag!=tag_t.CLOSE){
                System.out.print("syntax error");
                System.exit(0);
            }
            index++;
        }
        else if(v.value.get(index).tag == tag_t.SUB){
            index++;
            parseF(v);
        }
        else{
            System.out.println("syntax error");
            System.exit(0);
        }
    }
}

