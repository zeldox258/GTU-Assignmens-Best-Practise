/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package hw7;

import java.awt.Color;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 *
 * @author omera
 */
public class myButton extends JButton{
    int x;
    int y;
    public myButton(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    protected void fireActionPerformed(ActionEvent event) {
        if(getBackground() != Color.darkGray) return;
        if(HW7.mark %2 == 0)
            this.setBackground(Color.red);
        else
            this.setBackground(Color.blue);
        HW7.game.play(x,(char)(y+'A'));
        HW7.moves.add(new point(x, y));
        HW7.mark++;
        if(getBackground() == Color.blue){
            HW7.game.hexCells.get(x).get(y).setVal('o');
            HW7.game.setLastx(x);
            HW7.game.setLasty(y);
        }
        if(getBackground() == Color.red){
            HW7.game.hexCells.get(x).get(y).setVal('x');
            HW7.game.setLastx(x);
            HW7.game.setLasty(y);
        }
        if (HW7.game.checkWin('x')) {
                JOptionPane.showMessageDialog(null, "Game finished", "Red won the game", JOptionPane.WARNING_MESSAGE);
                HW7.game.displayBoard();
                System.exit(0);
                //System.out.println("O won the game");
            }
        
        
        if(gameScreen.type.charAt(0)=='1' && HW7.mark % 2 == 1){
                HW7.game.play();
                gameScreen.arr[HW7.game.getLastx()][HW7.game.getLasty()].setBackground(Color.blue);
                HW7.mark++;
                HW7.moves.add(new point(HW7.game.getLastx(), HW7.game.getLasty()));
        }
        if(HW7.game.checkWin('o')){
                JOptionPane.showMessageDialog(null, "Game finished", "Blue won the game", JOptionPane.WARNING_MESSAGE);
                HW7.game.displayBoard();
                System.exit(0);
                //System.out.println("X won the game");
        }
        
        
       
    }
    
}
