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
public interface List<E> extends Collection<E>{
    void add(int idx,E e);
    E get(int index);
}
