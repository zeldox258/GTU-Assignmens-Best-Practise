
//package hw7;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import static javax.swing.WindowConstants.DISPOSE_ON_CLOSE;




/**
 *
 * @author omera
 */
public class gameScreen {
    static myButton[][] arr;
    static int size;
    static String type;
    
    public gameScreen(int size , String type) throws InterruptedException {
        this.size = size;
        this.type = type;
        HW7.game.setSize(this.size);
        HW7.game.setType(this.type.charAt(0));
        startGame();
    }
        
    
    public static void startGame() throws InterruptedException{
        final JFrame frame = new JFrame("Hex Game");

        arr = new myButton[size][size];
        for(int i = 0;i<size;i++){
            for(int j = 0;j<size;j++){
                myButton but= new myButton(i, j);
                
                but.setBounds(j*30+i*15,i*30,25,25);
                but.setBackground(Color.darkGray);

                arr[i][j] = but;
                frame.add(but);
            }
        }
        for(int i = 0;i<size;i++){
            for(int j = 0;j<size;j++){
                if(HW7.game.hexCells.get(i).get(j).getVal() == 'x')
                     arr[i][j].setBackground(Color.RED);
                 else if(HW7.game.hexCells.get(i).get(j).getVal() == 'o')
                     arr[i][j].setBackground(Color.blue);
            }
        }
        JButton resetButton = new JButton("Reset");
        resetButton.setSize(100,30);
        resetButton.setLocation(25,size*35+50);
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                HW7.game.reset();
            }
        });
        
        
        JButton saveButton = new JButton("Save");
        saveButton.setSize(100,30);
        saveButton.setLocation(130,size*35+50);
        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    HW7.game.save();
                } catch (IOException ex) {
                    Logger.getLogger(gameScreen.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        
        JButton loadButton = new JButton("Load");
        loadButton.setSize(100,30);
        loadButton.setLocation(235,size*35+50);
        loadButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                HW7.game.load();
                frame.dispose();
                try {
                    //System.out.println(game.getSize());
                    new gameScreen(HW7.game.getSize(), (HW7.game.getType()+""));
                } 
                    
                catch (InterruptedException ex) {
                    Logger.getLogger(gameScreen.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        
        
        JButton undoButton = new JButton("Undo");
        undoButton.setSize(100,30);
        undoButton.setLocation(340,size*35+50);
        undoButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(type.equals("1")){
                    HW7.game.undo();
                    HW7.game.undo();
                }
                else{
                    HW7.game.undo();
                }
                    
            }
        });
        
        
        
        frame.add(resetButton);
        frame.add(saveButton);
        frame.add(loadButton);
        frame.add(undoButton);
        
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        frame.setSize(size*55+50, size*55+50);
        frame.setLayout(null); 
        frame.setVisible(true);
        
    }
}
