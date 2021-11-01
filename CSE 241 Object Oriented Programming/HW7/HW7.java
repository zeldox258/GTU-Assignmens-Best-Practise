
//package hw7;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.util.ArrayList;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import static javax.swing.WindowConstants.DISPOSE_ON_CLOSE;

/**
 *
 * @author omera
 */
public class HW7 {
    static ArrayList<point> moves = new ArrayList<>();
    public static int mark = 0;
    public static Hex game = new Hex(26, '1'); 
    public static void main(String[] args) throws InterruptedException {
        new mainScreen();
    }
    
}
