import java.util.ArrayList;
import java.util.Scanner;

public class CompSet {
    private static class Elem{
        boolean used;
        ArrayList<Integer> list;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int  n = in.nextInt();
        int  m = in.nextInt();
        int i, comps = 0, a, b;
        Elem[] graph = new Elem[n];
        for(i = 0; i<n; i++){
            graph[i] = new Elem();
            graph[i].list = new ArrayList<Integer>();
            graph[i].used = false;
            
        }
        for(i = 0; i<m; i++){
            a = in.nextInt();
            b = in.nextInt();
            graph[a].list.add(b);
            graph[b].list.add(a);
        }
        for(i = 0; i<n; i++){
            if(!graph[i].used){
                dvs(i, graph);
                comps++;
            }
        }
        System.out.print(comps);
    }
    private static void dvs(int cur, Elem[] graph){
        graph[cur].used = true;
        int size = graph[cur].list.size();
        for(int i = 0; i<size; i++){
            if(!graph[graph[cur].list.get(i)].used){
                dvs(graph[cur].list.get(i), graph);
            }
        }
        
    }
}