import java.util.*;

public class Loops {
    static int time = 0;
    static class Vertex implements Comparable{
        ArrayList<Vertex> next = new ArrayList<Vertex>(), bucket = new ArrayList<Vertex>(), prev = new ArrayList<Vertex>();
        Vertex ancestor = null, sdom = this, label = this, parent = null, dominator = null;
        int mark, operand, t, used = 0;
        String command;
        public Vertex(int mark, String command){
            this.mark = mark;
            this.command = command;
            
        }
        public Vertex(int mark, String command, int operand){
            this.mark = mark;
            this.command = command;
            this.operand = operand;
        }
        
        @Override
        public int compareTo(Object o) {
            return this.t - ((Vertex)o).t;
        }
    }
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        ArrayList<Vertex> graph = new ArrayList<Vertex>();
        HashMap<Integer, Vertex> marks = new HashMap<Integer, Vertex>();
        String[] cur;
        String current;
        in.nextLine();
        //----------------------------------MAKING GRAPH---------------------------------
        for(int i = 0; i<count; i++){
            current = in.nextLine();
            cur = current.split(" ");
            switch (cur[1].charAt(0)){
                case 'A': graph.add(new Vertex(Integer.parseInt(cur[0]), cur[1]));
                    break;
                default:graph.add(new Vertex(Integer.parseInt(cur[0]), cur[1], Integer.parseInt(cur[2])));
                    break;
            }
            marks.put(Integer.parseInt(cur[0]), graph.get(graph.size()-1));
        }
        for(int i = 0; i<count; i++){
            if(graph.get(i).command.charAt(0)=='A' && i < count-1){
                graph.get(i).next.add(graph.get(i+1));
                graph.get(i+1).prev.add(graph.get(i));
            }
            if(graph.get(i).command.charAt(0)=='J'){
                graph.get(i).next.add(marks.get(graph.get(i).operand));
                marks.get(graph.get(i).operand).prev.add(graph.get(i));
            }
            if(graph.get(i).command.charAt(0)=='B'){
                graph.get(i).next.add(marks.get(graph.get(i).operand));
                marks.get(graph.get(i).operand).prev.add(graph.get(i));
                if(i<count-1){
                    graph.get(i).next.add(graph.get(i+1));
                    graph.get(i+1).prev.add(graph.get(i));
                }
            }
        }
        //---------------------------------- END MAKING GRAPH---------------------------------
        dfs(graph.get(0));
        //-----------------------------------REMOVING UNUSED VERTEXES-----------------------------
        Iterator<Vertex> it = graph.iterator();
        while(it.hasNext()){
            Vertex v = it.next();
            if(v.used==0) it.remove();
            else{
                Iterator<Vertex> it2 = v.prev.iterator();
                while(it2.hasNext()){
                    Vertex u = it2.next();
                    if(u.used==0) it2.remove();
                }
            }
        }
        //-----------------------------------END REMOVING UNUSED VERTEXES-----------------------------
        Collections.sort(graph);
        dominators(graph);
        int answer = 0;
        //---------------------------------FINDING NATURAL LOOPS----------------------------------------
        for (Vertex v : graph)
            for (Vertex u : v.prev) {
                for (; u != null && u != v; u = u.dominator);
                if (u == v) {
                    answer++;
                    break;
                }
            }
        System.out.println(answer);
    }
    //----------------------------MAKING DOMINATORS---------------------------
    public static Vertex findMin(ArrayList<Vertex> graph, Vertex v){
        if(v.ancestor == null) return v;
        else{
            Stack<Vertex> stack =  new Stack<Vertex>();
            Vertex u = v;
            while (u.ancestor.ancestor != null){
                stack.push(u);
                u = u.ancestor;
            }
            while(!stack.empty()){
                v = stack.pop();
                if(v.ancestor.label.sdom.t < v.label.sdom.t) v.label = v.ancestor.label;
                v.ancestor = u.ancestor;
            }
            return v.label;
        }
    }
    public static void dominators(ArrayList<Vertex> graph){
        for(int i = graph.size()-1; i>0; i--){
            Vertex w = graph.get(i);
            for(Vertex v : w.prev){
                Vertex u = findMin(graph, v);
                if(u.sdom.t<w.sdom.t) w.sdom = u.sdom;
            }
            w.ancestor = w.parent;
            w.sdom.bucket.add(w);
            for(Vertex v: w.parent.bucket){
                Vertex u = findMin(graph, v);
                if(u.sdom == v.sdom) v.dominator = w.parent;
                else v.dominator = u;
            }
        }
        for (int i = 1; i < graph.size(); i++) {
            Vertex u = graph.get(i);
            if (u.dominator != u.sdom) u.dominator = u.dominator.dominator;
        }
        graph.get(0).dominator = null;
    }
    //---------------------------- END MAKING DOMINATORS---------------------------
    public static void dfs(Vertex v){
        v.used = 1;
        v.t = time++;
        for(Vertex u : v.next){
            if(u.used==0){
                u.parent = v;
                dfs(u);
            }
        }
    }
}

