/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// package hw6;

/**
 *
 * @author omera
 */
public interface Queue<E> extends Collection<E>{
    boolean add(E e);
    E element();
    boolean offer(E e);
    E poll();
}
