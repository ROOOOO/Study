import java.util.*;

public class Cpm {
    static class Vertex implements Comparable{
        String name, color = "";
        int used = 0;
        int time, dist = Integer.MAX_VALUE;
        Vertex parent = null;
        ArrayList<Vertex> next = new ArrayList<>();
        ArrayList<Vertex> prev = new ArrayList<>();
        ArrayList<Vertex> parents = new ArrayList<>();
        public Vertex(String s){
            int i, j;
            for(i = 0; s.charAt(i)!='('; i++);
            name = s.substring(0, i);
            for(j = i+1; s.charAt(j)!=')'; j++);
            time = -Integer.parseInt(s.substring(i+1, j));
        }
        
        @Override
        public int compareTo(Object o) {
            return this.name.compareTo(((Vertex)o).name);
        }
    }
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        ArrayList<String> all = new ArrayList<>();
        while(in.hasNextLine()) all.add(in.nextLine());
        String s = "";
        for(String str : all) s+=str;
        ArrayList<Vertex> graph = new ArrayList<>();
        ArrayList<Vertex> starts = new ArrayList<>();
        s = s.replaceAll(" ", "");
        int l = s.length();
        Vertex vert = null, prev = null;
        for(int i = 0; i<l;){
            int b;
            for(b = i; b<l && s.charAt(b)!= '<' && s.charAt(b) != ';'; b++);
            if(s.substring(i, b).contains("(")) {
                vert = new Vertex(s.substring(i, b));
                graph.add(vert);
                if(prev!=null){
                    if(!prev.next.contains(vert))prev.next.add(vert);
                    vert.prev.add(prev);
                }
                prev = vert;
            }
            else{
                for(Vertex x: graph){
                    if (x.name.equals(s.substring(i, b))){
                        if(prev!=null){
                            if(!prev.next.contains(x))prev.next.add(x);
                            x.prev.add(prev);
                        }
                        prev = x;
                        break;
                    }
                }
            }
            if(b<l && s.charAt(b) == ';') {
                vert = null;
                prev = null;
            }
            i = b+1;
        }
        for(Vertex v : graph){
            if(v.prev.size()==0)
            {
                v.dist = v.time;
                starts.add(v);
            }
        }
        for(Vertex v: graph){
            if(v.used==0) dfs(v);
        }
        int critical = 0;
        bellmanFord(graph);
        for(Vertex v : graph) if(!v.color.equals("blue") && v.dist < critical) critical = v.dist;
        for(Vertex v : graph) if(!v.color.equals("blue") && v.dist == critical) dfsRed(v);
        Collections.sort(graph);
        System.out.println("digraph {");
        for(Vertex v : graph){
            System.out.print("\t" + v.name + " [label = \"" + v.name + "(" + (-v.time) + ")\"");
            if(v.color.length()>0) System.out.print(", color = " + v.color);
            System.out.println("]");
        }
        
        for(Vertex v : graph){
            for(Vertex u : v.next){
                System.out.print("\t" + v.name + " -> " + u.name);
                if(u.color.equals(v.color) && v.color.equals("blue")) System.out.println(" [color = " + v.color+"]");
                if(u.parents.contains(v) && u.color.equals("red")) System.out.println(" [color = " + v.color+"]");
                else System.out.print("\n");
            }
        }
        System.out.print("}");
    }
    static void dfs(Vertex v){
        v.used = 1;
        for(Vertex u : v.next){
            if(u.used==0) dfs(u);
            else if(u.used==1) dfsBlue(u);
        }
        v.used = 2;
    }
    static void dfsBlue(Vertex v){
        v.color = "blue";
        for(Vertex u : v.next) if(!u.color.equals("blue")) dfsBlue(u);
    }
    static void dfsRed(Vertex v){
        v.color = "red";
        for(Vertex u : v.parents) if(!u.color.equals("red")) dfsRed(u);
    }
    static void bellmanFord(ArrayList<Vertex> graph){
        int s = graph.size();
        for(int i = 0; i<s-1; i++){
            for (Vertex v : graph) {
                for(Vertex u :v.next){
                    relax(v, u, u.time);
                }
            }
        }
        for(int i = 0; i<s-1; i++){
            for (Vertex v : graph) {
                for(Vertex u :v.next){
                    relax1(v, u, u.time);
                }
            }
        }
    }
    static boolean relax(Vertex u, Vertex v, int w){
        boolean changed = u.dist+w <= v.dist;
        if(changed) v.dist = u.dist+w;
        return changed;
    }
    static boolean relax1(Vertex u, Vertex v, int w){
        boolean changed = u.dist+w <= v.dist;
        if(changed){
            v.dist = u.dist+w;
            if(!v.parents.contains(u)) v.parents.add(u);
        }
        return changed;
    }
}

