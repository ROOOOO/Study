import java.util.PriorityQueue;
import java.util.Scanner;

public class Kruskal {
    static class Attr {
        int x, y;
        Attr parent;
        public Attr(){
            this.parent = this;
        }
        private Attr find(){
            if (this.parent != this) {
                this.parent = this.parent.find();
            }
            return this.parent;
        }
        public void union(Attr elem){
            elem.find().parent = this.find().parent;
        }
        public boolean equivalent(Attr elem)
        {
            return this.find() == elem.find();
        }
        
    }
    static class Edge implements Comparable<Edge>{
        Attr a;
        Attr b;
        double weight;
        @Override
        public int compareTo(Edge a) {
            if(this.weight>a.weight) return 1;
            if(this.weight<a.weight) return -1;
            if(this.weight==a.weight) return 0;
            return 0;
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), i, j, m = n*(n-1)/2, k = 0, count = 0;
        Attr[] a = new Attr[n];
        Edge[] graph = new Edge[m];
        Edge temp;
        String ans = new String();
        double dist = 0;
        PriorityQueue<Edge> roads = new PriorityQueue<Edge>();
        for(i = 0; i<n; i++){
            a[i] = new Attr();
            a[i].x = in.nextInt();
            a[i].y = in.nextInt();
        }
        for(i = 0; i<n-1; i++){
            for(j = i+1; j<n; j++){
                graph[k] = new Edge();
                graph[k].a = a[i];
                graph[k].b = a[j];
                graph[k].weight = Math.sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));
                roads.add(graph[k]);
                k++;
            }
        }
        for(i = 0; i<m; i++){
            temp = roads.poll();
            if(!(temp.a.equivalent(temp.b))){
                dist+=temp.weight;
                temp.a.union(temp.b);
                count++;
            }
            if(count==n-1) break;
        }
        ans = String.format("%.2f", dist);
        System.out.print(ans);
    }
}