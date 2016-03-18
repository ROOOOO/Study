import java.util.ArrayList;
import java.util.Collections;
import java.io.*;

public class Sync {
    static ArrayList<String> cpy;
    static ArrayList<String> del;
    public static void main(String[] args) {
        del = new ArrayList<String>();
        cpy = new ArrayList<String>();
        sync(args[0], args[1], "");
        if(cpy.size()==0&&del.size()==0){
            System.out.print("IDENTICAL");
            System.exit(0);
        }
        Collections.sort(del);
        Collections.sort(cpy);
        for(String item: del){
            System.out.println(item);
        }
        for(String item: cpy){
            System.out.println(item);
        }
    }
    private static void sync(String path1, String path2, String name){
        File s = new File(path1);
        File d = new File(path2);
        for(String item : s.list()){
            File temp1 = new File(path1 + "/" + item);
            File temp2 = new File(path2 + "/" + item);
            if(temp1.isFile()){
                if(!temp2.exists()) cpy.add("COPY "+name+item);
                else if(!compareFiles(temp1, temp2)){
                    cpy.add("COPY "+name+item);
                    del.add("DELETE "+name+item);
                }
            }
            if(temp1.isDirectory()){
                if(!temp2.exists()) syncNonExistDir(temp1.getPath(), item+"/");
                else sync(temp1.getPath(), temp2.getPath(), name+item+"/");
            }
        }
        for(String item : d.list()){
            File temp1 = new File(path1 + "/" + item);
            File temp2 = new File(path2 + "/" + item);
            if(!temp1.exists()){
                if(temp2.isFile()) del.add("DELETE "+ name + item);
                if(temp2.isDirectory()){
                    delNonExistDir(temp2.getPath(), item+"/");
                }
            }
        }
    }
    private static void syncNonExistDir(String path, String name){
        File temp = new File(path);
        for(String item : temp.list()){
            File temp1 = new File(path + "/" + item);
            if(temp1.isFile()) cpy.add("COPY " + name + item);
            if(temp1.isDirectory()) syncNonExistDir(temp1.getPath(), name +"/" + item);
        }
    }
    private static void delNonExistDir(String path, String name){
        File temp = new File(path);
        for(String item : temp.list()){
            File temp1 = new File(path + "/" + item);
            if(temp1.isFile()) del.add("DELETE " + name + item);
            if(temp1.isDirectory()) delNonExistDir(temp1.getPath(), name + "/" + item);
        }
    }
    private static boolean compareFiles(File first, File second){
        try {
            InputStreamReader isr1 =
            new InputStreamReader( new FileInputStream(first),
                                  "UTF-8");
            BufferedReader buff1 = new BufferedReader(isr1);
            InputStreamReader isr2 =
            new InputStreamReader( new FileInputStream(second),
                                  "UTF-8");
            BufferedReader buff2 = new BufferedReader(isr2);
            int c1, c2;
            while (((c1 = buff1.read()) != -1 )&&((c2 = buff2.read()) != -1 )) {
                if(c1!=c2) return false;
            }
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }
}

