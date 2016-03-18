import java.util.*;

public class SkipList<K extends Comparable<K>,V> extends AbstractMap<K,V> {
    ArrayList<MPair<K, V>>[] list;
    final static Random random = new Random();
    int i, levels, size;
    MPair<K, V> first;
    public SkipList(int levels) {
        this.size = 0;
        this.levels = levels;
        first = new MPair<K, V>(null, null);
    }
    MPair<K, V>[] skip(K key){
        MPair<K, V> x = first;
        MPair<K, V> res[] = new MPair[levels];
        for(i = levels-1; i>=0; i--){
            while (x.getNext()[i] != null && x.getNext()[i].getKey().compareTo(key) < 0) x = x.getNext()[i];
            res[i] = x;
        }
        return res;
    }
    public MPair succ(MPair x){
        return x.getNext()[0];
    }
    
    @Override
    public boolean isEmpty() {
        return size==0;
    }
    
    @Override
    public int size() {
        return this.size;
    }
    
    @Override
    public V put(K key, V value) {
        MPair<K, V> elem = new MPair<K, V>(key, value);
        MPair<K, V>[] p = skip(key);
        V toReturn = get(key);
        int r = random.nextInt()*2;
        for(i = 0; i<levels && r%2==0; i++, r/=2){
            elem.getNext()[i] = p[i].getNext()[i];
            p[i].getNext()[i] = elem;
        }
        if(toReturn==null) size++;
        return toReturn;
    }
    @Override
    public V get(Object key) {
        MPair<K, V>[] p = skip((K) key);
        return succ(p[0]) != null && succ(p[0]).getKey().equals((K)key) ?  (V)succ(p[0]).getValue() : null;
    }
    
    @Override
    public Set<Entry<K, V>> entrySet() {
        return new SkipListSet();
    }
    
    @Override
    public V remove(Object key) {
        MPair<K, V>[] p = skip((K)key);
        MPair<K, V> x = succ(p[0]);
        if(x==null || !x.getKey().equals((K)key)) return null;
        for(i = 0; i<levels && p[i].getNext()[i]==x; i++) p[i].getNext()[i] = x.getNext()[i];
        size--;
        return x.getValue();
    }
    
    @Override
    public void clear() {
        size = 0;
        first = new MPair<>(null, null);
    }
    
    private class MPair<K, V> implements Entry<K, V>{
        V value;
        K key;
        MPair<K, V>[] next;
        public MPair(K key, V value){
            this.key = key;
            this.value = value;
            next = new MPair[levels];
        }
        public MPair<K, V>[] getNext(){
            return next;
        }
        @Override
        public V getValue() {
            return value;
        }
        
        @Override
        public K getKey() {
            return key;
        }
        
        @Override
        public V setValue(V value) {
            return this.value = value;
        }
    }
    private class SkipListSet extends AbstractSet{
        private class SkipListIterator implements Iterator {
            MPair<K, V> f = first;
            
            @Override
            public Object next() {
                f = f.getNext()[0];
                return f;
            }
            
            @Override
            public boolean hasNext() {
                return f.getNext()[0] != null ? true : false;
            }
            
            @Override
            public void remove() {
                SkipList.this.remove(f.getKey());
            }
        }
        @Override
        public Iterator iterator() {
            return new SkipListIterator();
        }
        
        @Override
        public int size() {
            return SkipList.this.size();
        }
    }
}