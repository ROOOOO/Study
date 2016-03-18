public class Element<T>
{
    private T x;
    int depth;
    private Element<T> parent = this;
    // Создаёт новый элемент со значением x
    public Element(T x)
    {
        this.x = x;
        this.depth = 0;
        // ...
    }
    private Element<T> find() {
        if (this.parent != this) {
            this.parent = this.parent.find();
        }
        return this.parent;
    }
    // Возвращает значение элемента
    public T x()
    {
        return this.x;
        // ...
    }
    
    // Определяет, принадлежит ли текущий элемент
    // тому же множеству, что и элемент elem
    public boolean equivalent(Element<T> elem)
    {
        return this.find() == elem.find();
    }
    
    // Объединяет множество, которому принадлежит текущий
    // элемент, с множеством, которому принадлежит
    // элемент elem
    public void union(Element<T> elem)
    {
        Element<T> x = this.find();
        Element<T> y = elem.find();
        if(x.depth<y.depth){
            x.parent = y;
        }
        else{
            y.parent = x;
            if((x.depth==y.depth)&&(x!=y)){
                x.depth++;
            }
        }
        
    }
}

