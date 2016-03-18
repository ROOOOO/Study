import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Iterator;

public class SparseSet<T extends Hintable> extends AbstractSet<T> {
    int m, i;
    ArrayList<T> dense;
    ArrayList<Integer> sparse;
    public SparseSet(){
        this.dense = new ArrayList<T>();
        this.m = 0;
    }
    
    @Override
    public boolean add(T object) {
        int a = object.hint();
        if(a>=m || !(dense.get(a) == object)) {
            dense.add(m, object);
            object.setHint(m);
            m++;
            return true;
        }
        return false;
    }
    
    @Override
    public boolean remove(Object o) {
        int a = ((T) o).hint();
        int n = m-1;
        if(a <=n && dense.get(a)==(T) o) {
            T e = dense.get(n);
            e.setHint(a);
            m = n;
            dense.set(a, e);
            return true;
        }
        else return false;
    }
    @Override
    public boolean contains(Object o){
        int a = ((T) o).hint();
        return ((T) o).hint()<m && dense.get(a) == (T) o;
    }
    
    
    @Override
    public void clear() {
        dense = new ArrayList<T>();
        m = 0;
    }
    
    @Override
    public int size() {
        return this.m;
    }
    @Override
    public Iterator<T> iterator() {
        return new MIterator();
    }
    private class MIterator implements Iterator<T>{
        int pos;
        public MIterator(){
            pos = 0;
        }
        @Override
        public boolean hasNext() {
            return pos < m? true : false;
        }
        @Override
        public T next() {
            pos++;
            return dense.get(pos-1);
        }
        
        @Override
        public void remove() {
            SparseSet.this.remove(dense.get(pos-1));
        }
    }
    
}


