import java.util.Scanner;
import java.util.ArrayList;
import java.util.PriorityQueue;
public class Prim {
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), m = in.nextInt();
        int i, j, a, b, w, min = Integer.MAX_VALUE, index = 0, res = 0, l, item, k, s;
        Elem[] graph = new Elem[n];
        for(i = 0; i<n; i++) graph[i] = new Elem();
        ArrayList<Integer> tree = new ArrayList<Integer>();
        for(i = 0; i<m; i++){
            a  = in.nextInt();
            b = in.nextInt();
            w = in.nextInt();
            graph[a].list.add(new Edge(b, w));
            graph[b].list.add(new Edge(a, w));
        }
        tree.add(0);
        graph[0].used = true;
        for(i = 0; i<n-1; i++){
            l = tree.size();
            for(j = 0; j<l; j++) {
                item = tree.get(j);
                s = graph[item].list.size();
                for(k = 0; k<s; k++){
                    if(graph[graph[item].list.peek().d].used)
                        graph[item].list.remove();
                    else break;
                }
                if (!graph[item].list.isEmpty()) {
                    if (graph[item].list.peek().weight < min) {
                        min = graph[item].list.peek().weight;
                        index = item;
                    }
                }
            }
            graph[graph[index].list.peek().d].used = true;
            res += graph[index].list.peek().weight;
            tree.add(graph[index].list.poll().d);
            min = Integer.MAX_VALUE;
        }
        System.out.print(res);
    }
    static class Elem{
        PriorityQueue<Edge> list;
        boolean used;
        int parent;
        public Elem(){
            list = new PriorityQueue<Edge>();
            used = false;
        }
    }
    static class Edge implements Comparable<Edge>{
        int d;
        int weight;
        public Edge(int destination, int w){
            d = destination;
            weight = w;
        }
        
        @Override
        public int compareTo(Edge o) {
            return this.weight - o.weight;
        }
    }
}