import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class GraphBase {
    static Vertex[] graph;
    static Stack<Vertex> stack;
    static CondVertex[] cond;
    static int time = 1, count = 1;
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), m = in.nextInt(), temp;
        graph = new Vertex[n];
        stack = new Stack<Vertex>();
        for(int i = 0; i<n; i++) graph[i] = new Vertex();
        for(int i = 0; i < m; i++){
            temp = in.nextInt();
            graph[temp].next.add(in.nextInt());
        }
        tarjan();
        cond = new CondVertex[--count];
        for(int i = 0; i<count; i++) cond[i] = new CondVertex();
        for(int i = 0; i<n; i++) cond[graph[i].comp-1].vertexes.add(i);
        for(Vertex v : graph){
            for(Integer j : v.next){
                if(v.comp!=graph[j].comp && !cond[graph[j].comp-1].next.contains(v.comp-1)) cond[graph[j].comp-1].next.add(v.comp-1);
            }
        }
        for(CondVertex v : cond){
            if(v.next.size()==0) System.out.print(findMin(v.vertexes)+" ");
        }
    }
    static int findMin(ArrayList<Integer> array){
        int min = Integer.MAX_VALUE;
        for(Integer i : array){
            if(i<min) min = i;
        }
        return min;
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
        for(Integer u : v.next){
            if(graph[u].t1 == 0) visitVertex(graph[u]);
            if(graph[u].comp == 0 && v.low > graph[u].low) v.low = graph[u].low;
        }
        if(v.t1 == v.low){
            for(temp = stack.pop(), temp.comp = count; v!=temp; temp = stack.pop(), temp.comp = count);
            count++;
        }
    }
    static class Vertex{
        int t1;
        int comp;
        int low;
        ArrayList<Integer> next;
        public Vertex(){
            next = new ArrayList<Integer>();
            comp = 0;
            t1 = 0;
        }
    }
    static class CondVertex{
        ArrayList<Integer> vertexes;
        ArrayList<Integer> next;
        boolean isBase;
        public CondVertex(){
            vertexes = new ArrayList<Integer>();
            next = new ArrayList<Integer>();
        }
    }
}