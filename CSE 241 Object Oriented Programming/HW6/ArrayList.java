/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// package hw6;
public class ArrayList<E>  implements List<E>{
    private E[] arr;// = new E[100];
    private int size = 0;
    public E get(int index){
        return arr[index];
    }

    public ArrayList() {
        arr = (E[]) new Object[250];
    }
    private void openSpace(){
        E [] temp = (E[]) new Object[size*2];
        for(int i = 0;i<size;i++){
            temp[i] = arr[i];
        }
        arr = temp;
    }
    private void retrieveSize(){
        while(size-1 >= 0 && arr[size-1] == null)size--;
    }
    
    public Iterator<E> iterator() {
        retrieveSize();
        return new Itr<E>(arr,size,'a');
    }

    
    public boolean add(Object e) {
        retrieveSize();
        try {
            if(size == arr.length){
                openSpace();
            }
            arr[size++] = (E) e;
        } 
        catch (Exception ex) {
            return false;
        }
        return true;
        
    }

    
    public boolean addAll(Collection c) {
        retrieveSize();
        try {
            Iterator<E> it = c.iterator();
            while (it.hasNext()) {            
                add(it.next());
            }
        } 
        catch (Exception e) {
            return false;
        }
        
        
        return true;
    }

    
    public void clear() {
        retrieveSize();
        size = 0;
        arr = (E[]) new Object[250];
    }

    
    public boolean contains(Object e) {
        retrieveSize();
        for(int i = 0;i<size;i++){
            if(e.equals(arr[i])) return true;
        }
        return false;
    }

    
    public boolean containsAll(Collection c) {
        retrieveSize();
        Iterator<E> it = c.iterator();
        while(it.hasNext()){
            if(!contains(it.next())) return false;
        }
        return true;
    }

    
    public boolean isEmpty() {
        retrieveSize();
        return size == 0;
    }

    
    public void remove(Object e) {
        retrieveSize();
        if(contains(e)){
            size--;
            int ind = 0;
            for(int i = 0;i<=size;i++){
                if(e.equals(arr[i])){
                    ind = i;
                    break;
                }
            }
            arr[ind] =arr[size];
        }
        else{
            try {
                throw new Exception("this is not in the set");
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
            }
        }
    }

    
    public void removeAll(Collection c) {
        retrieveSize();
        Iterator<E> it = c.iterator();
        while(it.hasNext()){
            remove(it.next());
        }
    }

    
    public void retainAll(Collection c) {
        retrieveSize();
        E [] temp = (E[]) new Object[size*2];
        int idx = 0;
        Iterator<E> it = c.iterator();
        while(it.hasNext()){
            E tt = it.next();
            if(contains(tt))temp[idx++] = tt;
        }
        
        arr = temp;
        size = idx;
    }

    
    public int size() {
        retrieveSize();
        return size;
    }

    
    public void add(int idx, E e) {
        retrieveSize();
        if(size == arr.length){
            openSpace();
        }
        for(int i = size;i>idx;i--){
            arr[i] = arr[i-1];
        }
        arr[idx] = e;
        size++;
    }
}
 