/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// package hw6;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author omera
 */
public class Itr<E> implements Iterator<E>{
    private int cursor  = 0;
    private E [] arr;
    private int size;
    private char type;
    public Itr(E [] arrTemp , int sizeTemp,char typeTemp) {
        size = sizeTemp;
        arr = arrTemp;
        type = typeTemp;
    }
    
    
    
    public boolean hasNext() {
        return cursor < size;
    }

    
    public E next() {
       return arr[cursor++];
    }

    
    public void remove() {
        if(type == 'q') try {
            throw new Exception();
        } catch (Exception ex) {
            Logger.getLogger(Itr.class.getName()).log(Level.SEVERE, null, ex);
        }
        for(int i = cursor+1;i<size;i++){
            arr[i-1] = arr[i];
        }
        size--;
        arr[size] = null;
    }

    
    
}
