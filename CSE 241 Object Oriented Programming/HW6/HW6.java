// package hw6;

/**
 *
 * @author omera
 */
public class HW6 {
    public static void main(String[] args) {
        ArrayList<Integer> al = new ArrayList<Integer>();
        for(int i = 0;i<200;i++){
            al.add(i);
        }
        
        //linkelist add
        LinkedList<Integer> ab = new LinkedList<Integer>();
        for(int i = 0;i<250;i+=3){
            ab.add(i);
        }
        //retain all examples
        al.retainAll(ab);
        
        //arraylist get example
        for(int i = 0;i<al.size();i++){
            System.out.println(i+"->"+al.get(i));
        }
        //iter remove
        Iterator<Integer> aa = al.iterator();
        aa.remove();
        aa.remove();
        aa.remove();
        aa.remove();
        aa.remove();
        aa.remove();
        aa.remove();
        for(int i = 0;i<al.size();i++){
            System.out.println(i+"->"+al.get(i));
        }
        System.out.println(al.size());
        System.out.println(al.contains(25));
        al.remove(20);
        
        //add all ab to al and display
        al.addAll(ab);
        for(int i = 0;i<al.size();i++){
            System.out.println(i+"->"+al.get(i));
        }
        
        HashSet<String> set = new HashSet<>();
        
        //no duplicate
        set.add("hi");
        System.out.println(set.size());
        set.add("hi");
        System.out.println(set.size());
        
        System.out.println(ab.poll());
        //I used all functions with differentway you can check it also
        
    }
    
}
