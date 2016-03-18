import java.util.Collections;
import java.util.ArrayList;
import java.util.Scanner;
public class Mars {
    static class Elem {
        ArrayList<Integer> list;
        boolean used;
        int parent;
        int depth;
        public Elem(){
            this.list = new ArrayList<Integer>();
            this.used = false;
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), i, j, temp = 0, count, size;
        String[] s = new String[n];
        Elem[] graph = new Elem[n];
        in.nextLine();
        ArrayList<Integer> readyToFly = new ArrayList<Integer>();
        ArrayList<Integer> notUsed = new ArrayList<Integer>();
        ArrayList<ArrayList<Integer>[]> team = new ArrayList<ArrayList<Integer>[]>();
        for(i = 0; i<n; i++) s[i] = in.nextLine();
        for(i = 0; i<n; i++){
            graph[i] = new Elem();
            for(j = 0; j<2*n; j+=2){
                if(s[i].charAt(j)=='+') graph[i].list.add(j/2) ;
            }
        }
        for(i = 0, j = 0; i<n; i++){
            if((graph[i].list.size()!=0)&&(!graph[i].used)){
                graph[i].parent = -1;
                team.add(new ArrayList[2]);
                team.get(j)[0] = new ArrayList<Integer>();
                team.get(j)[1] = new ArrayList<Integer>();
                preTeamDivider(team.get(j), graph, i, 0, 0);
                j++;
            }
            else if(graph[i].list.size()==0) notUsed.add(i+1);
        }
        Collections.sort(notUsed);
        for(ArrayList[] item:team){
            temp+=item[0].size();
        }
        for(i = 0; i<n/2-temp; i++){
            readyToFly.add(notUsed.get(0));
            notUsed.remove(0);
        }
        count  = team.size();
        for(i = 0; i<count; i++){
            temp = team.get(i)[0].size()-team.get(i)[1].size();
            if(temp>0 && notUsed.size() == 0){
                for(Integer item:team.get(i)[1]) {
                    readyToFly.add(item);
                }
            }
            else if((temp>0)&&(team.get(i)[0].get(0) > notUsed.get(0))){
                for(j = 0; j<temp; j++){
                    readyToFly.add(notUsed.get(0));
                    notUsed.remove(0);
                }
                for(Integer item:team.get(i)[1]){
                    readyToFly.add(item);
                }
            }
            else{
                for(Integer item:team.get(i)[0]){
                    readyToFly.add(item);
                }
            }
        }
        Collections.sort(readyToFly);
        
        for(Integer item:readyToFly) System.out.print(item+" ");
    }
    private static void preTeamDivider(ArrayList<Integer>[] team, Elem[] graph, int cur, int id, int depth){
        int i, s = graph[cur].list.size();
        graph[cur].used = true;
        graph[cur].depth = depth;
        team[id].add(cur+1);
        int idNext = id==0? 1:0;
        for(i = 0; i<s; i++){
            if(!graph[graph[cur].list.get(i)].used){
                graph[graph[cur].list.get(i)].parent = cur;
                preTeamDivider(team, graph, graph[cur].list.get(i), idNext, depth+1);
            }
            else if((graph[cur].parent!=graph[cur].list.get(i))&&(Math.abs(graph[cur].depth - graph[graph[cur].list.get(i)].depth)%2==0)){
                System.out.print("No solution");
                System.exit(0);
            }
        }
    }
}

