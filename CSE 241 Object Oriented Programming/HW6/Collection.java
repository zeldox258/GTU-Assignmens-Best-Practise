/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// package hw6;

/**
 *
 * @author omera
 * @param <E>
 */
public interface Collection<E>{
    Iterator<E> iterator();
    boolean add(E e);
    boolean addAll(Collection c);
    void clear();
    boolean contains(E e); 
    boolean containsAll(Collection c);
    boolean isEmpty();
    void remove(E e);
    void removeAll(Collection c);
    void retainAll(Collection c);
    int size();
}
