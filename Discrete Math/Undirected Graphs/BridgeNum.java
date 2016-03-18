
import java.util.ArrayList;
import java.util.Scanner;

public class BridgeNum {
    private static ArrayList<Integer> l;
    ArrayList<Integer> lst;
    private static class Elem{
        boolean used;
        ArrayList<Integer> list;
        int parent;
        int comp;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int  n = in.nextInt();
        int  m = in.nextInt();
        int i, comps = 0, a, b, component=0;
        l = new ArrayList<Integer>();
        Elem[] graph = new Elem[n];
        for(i = 0; i<n; i++){
            graph[i] = new Elem();
            graph[i].list = new ArrayList<Integer>();
            graph[i].used = false;
            graph[i].comp = -1;
            
        }
        for(i = 0; i<m; i++){
            a = in.nextInt();
            b = in.nextInt();
            graph[a].list.add(b);
            graph[b].list.add(a);
        }
        for(i = 0; i<n; i++){
            if(!graph[i].used){
                graph[i].parent = -1;
                dvs1(i, graph);
                comps++;
            }
        }
        int s = l.size();
        
        for(i = 0; i<s; i++){
            if(graph[l.get(i)].comp==-1){
                dvs2(l.get(i), graph, component);
                component++;
            }
        }
        System.out.println(component - comps);
        
    }
    private static void dvs1(int cur, Elem[] graph){
        graph[cur].used = true;
        l.add(cur);
        int size = graph[cur].list.size();
        for(int i = 0; i<size; i++){
            if(!graph[graph[cur].list.get(i)].used){
                graph[graph[cur].list.get(i)].parent = cur;
                dvs1(graph[cur].list.get(i), graph);
            }
        }
        
    }
    private static void dvs2(int cur, Elem[] graph, int component){
        graph[cur].comp = component;
        int size = graph[cur].list.size();
        for(int i = 0; i<size; i++){
            if((graph[graph[cur].list.get(i)].comp==-1)&&(graph[graph[cur].list.get(i)].parent!=cur)){
                dvs2(graph[cur].list.get(i), graph, component);
            }
        }
        
    }
}