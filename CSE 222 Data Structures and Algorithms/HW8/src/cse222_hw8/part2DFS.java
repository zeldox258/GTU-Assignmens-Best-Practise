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
// Java program to print DFS
//mtraversal from a given given
// graph
import java.io.*;
import java.util.*;
 
// This class represents a
// directed graph using adjacency
// list representation
public class part2DFS {
    private int V; // No. of vertices
    private int res = 0;
    // Array  of lists for
    // Adjacency List Representation
    private LinkedList<Integer> adj[];
 
    // Constructor
    @SuppressWarnings("unchecked") part2DFS(int v)
    {
        V = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; ++i)
            adj[i] = new LinkedList();
    }
 
    // Function to add an edge into the graph
    void addEdge(int v, int w)
    {
        adj[v].add(w); // Add w to v's list.
    }
 
    // A function used by DFS
    void DFSUtil(int v, boolean visited[])
    {
        // Mark the current node as visited and print it
        visited[v] = true;
        System.out.print(v + " ");
 
        // Recur for all the vertices adjacent to this
        // vertex
        Iterator<Integer> i = adj[v].listIterator();
        while (i.hasNext())
        {
            int n = i.next();
            if (!visited[n]){
                DFSUtil(n, visited);
                res++;
            }
                
        }
    }
 
    // The function to do DFS traversal.
    // It uses recursive
    // DFSUtil()
    int DFS(int v)
    {
        // Mark all the vertices as
        // not visited(set as
        // false by default in java)
        boolean visited[] = new boolean[V];
 
        // Call the recursive helper
        // function to print DFS
        // traversal
        DFSUtil(v, visited);
        return res;
    }
 
    
    static void create1000(){
        part2DFS g = new part2DFS(1000);
        Random rand = new Random();
        for(int i = 0;i< 1000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(1000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Depth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.DFS(0);
    }
    
    static void create2000(){
        part2DFS g = new part2DFS(2000);
        Random rand = new Random();
        for(int i = 0;i< 2000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(2000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Depth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.DFS(0);
    }
    
    static void create5000(){
        part2DFS g = new part2DFS(5000);
        Random rand = new Random();
        for(int i = 0;i< 5000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(5000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Depth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.DFS(0);
    }
    
    static void create10000(){
        part2DFS g = new part2DFS(10000);
        Random rand = new Random();
        for(int i = 0;i< 10000;i++){
            int a = i;
            while(a == i)
                a = rand.nextInt(10000);
            g.addEdge(i, a);
            g.addEdge(a, i);
        }
        System.out.println("Following is Depth First Traversal "+
                           "(starting from vertex 0 for 1000 size)");
        g.DFS(0);
    }
    
    
    // Driver Code
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