import java.util.AbstractSet;
import java.util.Iterator;

public class IntSparseSet extends AbstractSet<Integer> {
    int low, high, m, i;
    int[] dense, sparse;
    public IntSparseSet(int low, int high){
        this.low = low;
        this.high = high;
        this.dense = new int[high-low];
        this.sparse = new int[high-low];
        this.m = 0;
    }
    
    @Override
    public boolean add(Integer integer) {
        if(integer<low || integer>=high) return false;
        int a = sparse[integer-low];
        if(a>=m || dense[a] != integer-low) {
            sparse[integer-low] = m;
            dense[m] = integer-low;
            m++;
            return true;
        }
        return false;
    }
    @Override
    public boolean remove(Object o) {
        if((Integer)o<low || (Integer)o >=high) return false;
        int a = sparse[(Integer)o-low];
        int n = m-1;
        if(a <=n && dense[a] == (Integer)o-low) {
            int e = dense[n];
            m = n;
            dense[a] = e;
            sparse[e] = a;
            return true;
        }
        else return false;
    }
    
    @Override
    public boolean contains(Object o) {
        if((Integer)o<low || (Integer)o >=high) return false;
        int a = sparse[(Integer)o-low];
        return a<m && dense[a]==(Integer)o-low;
    }
    
    @Override
    public void clear() {
        sparse = new int[high-low];
        dense = new int[high-low];
        m = 0;
    }
    
    @Override
    public int size() {
        return this.m;
    }
    @Override
    public Iterator<Integer> iterator() {
        return new MIterator();
    }
    private class MIterator implements Iterator<Integer>{
        int pos;
        public MIterator(){
            pos = 0;
        }
        @Override
        public boolean hasNext() {
            return pos < m? true : false;
        }
        @Override
        public Integer next() {
            return dense[pos++]+low;
        }
        
        @Override
        public void remove() {
            IntSparseSet.this.remove(dense[pos - 1] + low);
        }
    }
    
}

