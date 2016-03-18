import java.util.*;
public class MapRoute {
    static class Vertex implements Comparable{
        ArrayList<Vertex> next = new ArrayList<>();
        int dist = Integer.MAX_VALUE-10, w;
        public Vertex(int w){
            this.w = w;
        }
        @Override
        public int compareTo(Object o) {
            return this.dist-((Vertex)o).dist;
        }
    }
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        Vertex[][] graph = new Vertex[n][n];
        PriorityQueue<Vertex> vQueue = new PriorityQueue<>();
        for(int i = 0; i<n; i++) for(int j = 0; j<n; j++) {
            Vertex v = new Vertex(in.nextInt());
            graph[i][j] = v;
        }
        for(int i = 0; i<n; i++){
            for(int j= 0; j<n; j++){
                if(i<n-1) graph[i][j].next.add(graph[i+1][j]);
                if(j<n-1) graph[i][j].next.add(graph[i][j+1]);
                if(i>0) graph[i][j].next.add(graph[i-1][j]);
                if(j>0) graph[i][j].next.add(graph[i][j-1]);
            }
        }
        graph[0][0].dist = 0;
        vQueue.add(graph[0][0]);
        dijkstra(vQueue);
        System.out.print(graph[n-1][n-1].dist+graph[0][0].w);
    }
    public static void dijkstra(PriorityQueue<Vertex> vQueue){
        while(!vQueue.isEmpty()){
            Vertex v = vQueue.poll();
            v.next.forEach(w->{
                if(v.dist+w.w<w.dist){
                    w.dist = v.dist+w.w;
                    vQueue.add(w);
                }
            });
        }
    }
}