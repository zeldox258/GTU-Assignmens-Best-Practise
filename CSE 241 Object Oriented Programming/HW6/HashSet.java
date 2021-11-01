// package hw6;

import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author omera
 */
public class HashSet<E> implements Set<Object>{
    private E[] arr;// = new E[100];
    private int size = 0;
    public HashSet() {
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
    
    
    public Iterator iterator() {
        retrieveSize();
        return new Itr<E>(arr,size,'h');
    }

    
    public boolean add(Object e) {
        retrieveSize();
        if(contains(e)) return false;
        try {
            if(size == arr.length)
                openSpace();
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
                E a = it.next();
                if(!contains(a))add(a);
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
    
}
