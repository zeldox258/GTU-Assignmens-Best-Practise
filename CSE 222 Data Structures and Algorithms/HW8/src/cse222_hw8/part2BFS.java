/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cse222_hw8;

/**
 *
 * @author omera
 */
// Java program to print BFS traversal from a given source vertex.
// BFS(int s) traverses vertices reachable from s.
import java.io.*;
import java.util.*;
 
// This class represents a directed graph using adjacency list
// representation
public class part2BFS
{
    private int V;   // No. of vertices
    private LinkedList<Integer> adj[]; //Adjacency Lists
 
    // Constructor
    part2BFS(int v)
    {
        V = v;
        adj = new LinkedList[v];
        for (int i=0; i<v; ++i)
            adj[i] = new LinkedList();
    }
 
    // Function to add an edge into the graph
    void addEdge(int v,int w)
    {
        adj[v].add(w);
    }
 
    // prints BFS traversal from a given source s
    int BFS(int s)
    {
        // Mark all the vertices as not visited(By default
        // set as false)
        boolean visited[] = new boolean[V];
        int res = 0;
        // Create a queue for BFS
        LinkedList<Integer> queue = new LinkedList<Integer>();
 
        // Mark the current node as visited and enqueue it
        visited[s]=true;
        queue.add(s);
 
        while (queue.size() != 0)
        {
            // Dequeue a vertex from queue and print it
            s = queue.poll();
            System.out.print(s+" ");
 
            // Get all adjacent vertices of the dequeued vertex s
            // If a adjacent has not been visited, then mark it
            // visited and enqueue it
            Iterator<Integer> i = adj[s].listIterator();
            while (i.hasNext())
            {
                int n = i.next();
                if (!visited[n])
                {
                    visited[n] = true;
                    queue.add(n);
                    res++;
                }
            }
        }
        return res;
    }
 
    
    
    
    static void create1000(){
        part2BFS g = new part2BFS(1000);
        Random rand = new Random();
        for(int i = 0;i< 1000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(1000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Breadth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.BFS(0);
    }
    
    static void create2000(){
        part2BFS g = new part2BFS(2000);
        Random rand = new Random();
        for(int i = 0;i< 2000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(2000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Breadth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.BFS(0);
    }
    
    static void create5000(){
        part2BFS g = new part2BFS(5000);
        Random rand = new Random();
        for(int i = 0;i< 5000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(5000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Breadth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.BFS(0);
    }
    
    static void create10000(){
        part2BFS g = new part2BFS(10000);
        Random rand = new Random();
        for(int i = 0;i< 10000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(10000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Breadth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.BFS(0);
    }
    
    // Driver method to
    public static void main(String args[])
    {
        long start,stop;
        start = System.nanoTime();
        create1000();
        stop = System.nanoTime();
        
        System.out.println("\ntotal time for 1000 :" + (stop - start));
        
        start = System.nanoTime();
        create2000();
        stop = System.nanoTime();
        
        System.out.println("\ntotal time for 2000 :" + (stop - start));
        
        start = System.nanoTime();
        create5000();
        stop = System.nanoTime();
        
        System.out.println("\ntotal time for 5000 :" + (stop - start));
        
        start = System.nanoTime();
        create10000();
        stop = System.nanoTime();
        
        System.out.println("\ntotal time for 10000 :" + (stop - start));
    }
}
