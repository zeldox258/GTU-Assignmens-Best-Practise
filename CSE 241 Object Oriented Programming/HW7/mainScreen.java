//package hw7;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.Action;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import static javax.swing.WindowConstants.DISPOSE_ON_CLOSE;
/**
 *
 * @author omera
 */
public class mainScreen {

    public mainScreen() throws InterruptedException {
        startGame();
    }
    
   public static void startGame()throws InterruptedException{
       final JFrame frame = new JFrame("Hex Game");
       frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
       frame.setSize(500, 500);
       frame.setLayout(null); 
       
       final JTextField tf = new JTextField();
       tf.setText("0");
       tf.setSize(100,30);
       tf.setLocation(50, 40);
       frame.add(tf);
       
       JLabel sizetext = new JLabel();
       sizetext.setText("Size:");
       sizetext.setSize(40,18);
       sizetext.setLocation(15,50);
       frame.add(sizetext);
       
       final JRadioButton oneVone = new JRadioButton();
       oneVone.setText("Player Vs Player");
       oneVone.setSize(180,30);
       oneVone.setLocation(250, 40);
       frame.add(oneVone);
       
       JRadioButton oneVcom = new JRadioButton();
       oneVcom.setText("Player Vs Computer");
       oneVcom.setSize(180,30);
       oneVcom.setLocation(250, 70);
       oneVcom.setSelected(true);
       frame.add(oneVcom);
       
       ButtonGroup bg = new ButtonGroup();
       bg.add(oneVcom);
       bg.add(oneVone);
       
       
       
       JButton startButton = new JButton();
       startButton.setText("Start Game");
       startButton.setSize(125,30);
       startButton.setLocation(165,300);
       startButton.addActionListener(new ActionListener() {
           @Override
           public void actionPerformed(ActionEvent e) {
               
               int size =Integer.parseInt(tf.getText());
               if(size <6 || size >26){
                   JOptionPane.showMessageDialog(null,"Please give me size between [6,26]","Warning",JOptionPane.WARNING_MESSAGE);
                   return;
               }
               
               String type = "1";
               if(oneVone.isSelected()) type = "2";
               frame.setVisible(false);
               try {
                   new gameScreen(size, type);
                   frame.dispose();
               } catch (InterruptedException ex) {
                   Logger.getLogger(mainScreen.class.getName()).log(Level.SEVERE, null, ex);
               }
               
           }
        });
       
       frame.add(startButton);
       
       
       frame.setVisible(true);
       
       
       
   }
   
}
