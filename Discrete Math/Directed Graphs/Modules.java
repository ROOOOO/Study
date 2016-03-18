import java.util.*;

public class Modules {
    static Vertex[] graph;
    static int index;
    static HashMap<String, Vertex> functions;
    static Stack<Vertex> stack;
    static int time = 1, count = 1;
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        ArrayList<String> expressions = new ArrayList<String>();
        while(in.hasNextLine()) expressions.add(in.nextLine());
        int cnt = expressions.size();
        for(int i = 0; i<cnt; i++) {
            if(expressions.get(i).length()==0){
                expressions.remove(i);
            }
        }
        cnt = expressions.size();
        ArrayList<Token>[] allLex = new ArrayList[cnt];
        graph = new Vertex[cnt];
        functions = new HashMap<String, Vertex>();
        stack = new Stack<Vertex>();
        for(int i = 0; i<cnt; i++){
            allLex[i] = new ArrayList<Token>();
            getTokens(expressions.get(i), allLex[i]);
            graph[i] = new Vertex(allLex[i], expressions.get(i));
        }
        putFunctions(graph);
        makeGraph(graph);
        tarjan();
        System.out.print(count-1);
        
    }
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
        ArrayList<String> vars;
        String name;
        String formula;
        int need;
        int t1, comp, low;
        public Vertex(ArrayList<Token> v, String f){
            this.value = v;
            this.formula = f;
            next = new ArrayList<Vertex>();
            this.vars = new ArrayList<String>();
            int s = value.size();
            need = 0;
        }
    }
    static void tarjan(){
        for(Vertex v : graph){
            if(v.t1==0){
                visitVertex(v);
            }
        }
    }
    static void visitVertex(Vertex v){
        v.t1 = v.low = time++;
        stack.push(v);
        Vertex temp;
        for(Vertex u : v.next){
            if(u.t1 == 0) visitVertex(u);
            if(u.comp == 0 && v.low > u.low) v.low = u.low;
        }
        if(v.t1 == v.low){
            do{
                temp = stack.pop();
                temp.comp = count;
            } while (temp!=v);
            count++;
        }
    }
    private static void putFunctions(Vertex[] graph){
        for(Vertex v : graph){
            functions.put(v.value.get(0).value, v);
            for(Token item : v.value){
                if(item.tag==tag_t.IDENT) v.need++;
                if(item.tag==tag_t.EQ) break;
            }
            v.need--;
        }
    }
    private static void makeGraph(Vertex[] graph){
        for(Vertex item : graph){
            index = 0;
            try{
                parseFunc(item);
            }
            catch (Exception e){
                System.out.print("error");
                System.exit(0);
            }
            if(index<item.value.size()){
                System.out.print("error");
                System.exit(0);
            }
        }
    }
    enum tag_t{PLUS, DIV, MUL, SUB, EQ, OPEN, CLOSE, COMMA, NUM, IDENT, DOUBLEP, EOFUNC, QUEST, LESS, MORE};
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
            else if(exp.charAt(i)==':') tokens.add(new Token(",", tag_t.DOUBLEP));
            else if(exp.charAt(i)==';') tokens.add(new Token(";", tag_t.EOFUNC));
            else if(exp.charAt(i)=='?') tokens.add(new Token(";", tag_t.QUEST));
            else if(exp.charAt(i)=='<') tokens.add(new Token("<", tag_t.LESS));
            else if(exp.charAt(i)=='>') tokens.add(new Token("<", tag_t.MORE));
            else if(Character.isDigit(exp.charAt(i))){
                for(j = i;j<length && Character.isDigit(exp.charAt(j)); j++);
                tokens.add(new Token(exp.substring(i, j), tag_t.NUM));
                j--;
                i = j;
            }
            else if(Character.isLetter(exp.charAt(i))){
                for(j = i; j<length && (Character.isDigit(exp.charAt(j)) || Character.isLetter(exp.charAt(j))); j++);
                tokens.add(new Token(exp.substring(i, j), tag_t.IDENT));
                j--;
                i = j;
            }
            else{
                System.out.print("error");
                System.exit(0);
            }
        }
    }
    private static void parseFunc(Vertex v){
        if(v.value.get(index).tag!=tag_t.IDENT&&v.value.get(index+1).tag!=tag_t.OPEN){
            System.out.print("error");
            System.exit(0);
        }
        v.name = v.value.get(index).value;
        index+=2;
        parseFormalArgsList(v);
        if(v.value.get(index).tag!=tag_t.CLOSE||v.value.get(index+1).tag!=tag_t.DOUBLEP||v.value.get(index+2).tag!=tag_t.EQ){
            System.out.print("error");
            System.exit(0);
        }
        index+=3;
        parseExpr(v);
        if(v.value.get(index).tag!=tag_t.EOFUNC){
            System.out.print("error");
            System.exit(0);
        }
        index++;
        
    }
    private static void parseFormalArgsList(Vertex v){
        if(v.value.get(index).tag==tag_t.CLOSE) return;
        parseIdentList(v);
    }
    private static void parseIdentList(Vertex v){
        if(v.value.get(index).tag!=tag_t.IDENT){
            System.out.print("error");
            System.exit(0);
        }
        v.vars.add(v.value.get(index).value);
        index++;
        while(v.value.get(index).tag==tag_t.COMMA){
            index++;
            parseIdentList(v);
        }
    }
    private static void parseExpr(Vertex v){
        parseCompExpr(v);
        if(v.value.get(index).tag==tag_t.QUEST){
            index++;
            parseCompExpr(v);
            if(v.value.get(index).tag!=tag_t.DOUBLEP){
                System.out.print("error");
                System.exit(0);
            }
            index++;
            parseExpr(v);
        }
    }
    private static boolean parseCompOp(Vertex v){
        if(v.value.get(index).tag==tag_t.EQ){
            index++;
            return true;
        }
        if(v.value.get(index).tag==tag_t.LESS){
            index++;
            if(v.value.get(index).tag==tag_t.MORE || v.value.get(index).tag==tag_t.EQ) index++;
            return true;
        }
        if(v.value.get(index).tag==tag_t.MORE){
            index++;
            if(v.value.get(index).tag==tag_t.EQ) index++;
            return true;
        }
        return false;
    }
    private static void parseCompExpr(Vertex v){
        parseArithExpr(v);
        if(parseCompOp(v)){
            parseArithExpr(v);
        }
    }
    private static void parseArithExpr(Vertex v){
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
        else if(v.value.get(index).tag == tag_t.IDENT){
            if(v.value.get(index+1).tag==tag_t.OPEN){
                String name = v.value.get(index).value;
                index+=2;
                int given = parseActArgList(v);
                if(v.value.get(index).tag!=tag_t.CLOSE){
                    System.out.print("error");
                    System.exit(0);
                }
                if(!functions.containsKey(name) || functions.get(name).need!=given){
                    System.out.println("error");
                    System.exit(0);
                }
                if(!v.next.contains(functions.get(name)) && v!=functions.get(name))v.next.add(functions.get(name));
            }
            else if(!v.vars.contains(v.value.get(index).value)){
                System.out.print("error");
                System.exit(0);
            }
            index++;
        }
        else if(v.value.get(index).tag == tag_t.OPEN){
            index++;
            parseExpr(v);
            if(v.value.get(index).tag!=tag_t.CLOSE){
                System.out.println("error");
                System.exit(0);
            }
            index++;
        }
        else if(v.value.get(index).tag == tag_t.SUB){
            while(v.value.get(index).tag == tag_t.SUB) index++;
            parseF(v);
        }
        else{
            System.out.println("error");
            System.exit(0);
        }
    }
    private static int parseActArgList(Vertex v){
        if(v.value.get(index).tag==tag_t.CLOSE) return 0;
        int given = parseExprList(v, 0);
        return given;
    }
    private static int parseExprList(Vertex v, int given){
        parseExpr(v);
        given++;
        while(v.value.get(index).tag==tag_t.COMMA){
            index++;
            parseExpr(v);
            given++;
        }
        return given;
    }
}

