import java.util.ArrayList;
import java.util.Scanner;

public class EqDist {
    private static class Elem{
        boolean used;
        ArrayList<Integer> list;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int  n = in.nextInt();
        int  m = in.nextInt();
        int i, v, a, b, j;
        boolean isEmpty = true;
        Elem[] graph = new Elem[n];
        int[] d = new int[n];
        int[] res = new int[n];
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
        int mv = in.nextInt();
        v = in.nextInt();
        bfs(res, graph, v);
        for(i = 1; i<mv; i++){
            v = in.nextInt();
            for(j = 0; j<n; j++){
                graph[j].used = false;
                d[j] = 0;
            }
            bfs(d, graph, v);
            for(j = 0; j<n; j++){
                if(res[j]!=d[j]){
                    res[j] = 0;
                }
            }
        }
        for(i = 0; i<n; i++){
            if(res[i]!=0){
                System.out.print(i+" ");
                isEmpty = false;
            }
        }
        if(isEmpty) System.out.print("-");
        
    }
    private static int bfs(int d[], Elem[] graph, int cur){
        int q, i, s, dist = 0;
        ArrayList<Integer> queue = new ArrayList<Integer>();
        queue.add(cur);
        graph[cur].used = true;
        d[cur] = 0;
        while(!queue.isEmpty()){
            q = queue.get(0);
            queue.remove(0);
            s = graph[q].list.size();
            for(i = 0; i < s; i++){
                if(!graph[graph[q].list.get(i)].used){
                    graph[graph[q].list.get(i)].used = true;
                    queue.add(graph[q].list.get(i));
                    d[graph[q].list.get(i)] = d[q] + 1;
                }
            }
        }
        return 0;
    }
}