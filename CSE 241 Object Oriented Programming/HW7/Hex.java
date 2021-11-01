
//package hw7;

import java.awt.Color;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 *
 * @author omera
 */
public class Hex implements hexGame{
    Scanner scanner  = new Scanner(System.in);
    int gameSaveNum = 1;
    
    public void setLastx(int lastx) {
        this.lastx = lastx;
    }

    public void setLasty(int lasty) {
        this.lasty = lasty;
    }
    
    int size = 26;
    char type = '1';
    List<List<Cell>> hexCells = new ArrayList<>();
    int totalmarked = 0;
    private int lastx = 0;
    private int lasty = 0;
    int winCond = 0;
    
    Hex(int size , char type, int gsn) {
        if(size >=5)this.size = size;
        this.type = type;
        gameSaveNum = gsn;
        createBoard();
    }
    Hex(char type , int size, int gsn) {
        if(size >=5)this.size = size;
        this.type = type;
        gameSaveNum = gsn;
        createBoard();
    }
    Hex(int size, int gsn) {
        if (size >= 5)this.size = size;
        gameSaveNum = gsn;
        createBoard();
    }
    Hex(char type, int gsn) {
        this.type = type;
        gameSaveNum = gsn;
        createBoard();
    }
    public void createBoard(){
        hexCells.clear();
        for (int i = 0; i < 26; i++) {
            List<Cell> tempCell = new ArrayList<Cell>();
            for (int j = 0; j < 26; j++) {
                tempCell.add(new Cell('.'));
            }
            hexCells.add(tempCell);
        }
    }
    //void saveFile();
    //void loadFile();
    public int getSize(){
        return size;
    }
    public void displayBoard(){
        System.out.print(" ");
        for (int i = 0; i < size; i++)
            System.out.print((char)('A' + i)+" ");
        System.out.println("");
        for (int i = 0; i < size; i++) {
            System.out.print(i+1);
            if (i < 9) {
                for (int j = 0; j < i + 1; j++) {
                    System.out.print(" ");
                }
            }
            else {
                for (int j = 0; j < i; j++) {
                    System.out.print(" ");
                }
            }
            for (int j = 0; j < size; j++) {
                System.out.print(hexCells.get(i).get(j).getVal()+" ");
            }
            System.out.println("");
        }
    }
    public void play(){
        int tempx = lastx;
        int tempy = lasty;

        int prex = lastx;

        while (true) {
            if (tempx != size - 1)tempx++;
            while (tempx >= 0 && hexCells.get(tempx).get(tempy).getVal() != '.')tempx--;
            if (tempx == -1) {
                tempx = prex;
                tempy++;
                if (tempy == size)tempy = 0;
                if (tempy == lasty)prex++;
            }
            else break;
        }
        hexCells.get(tempx).get(tempy).setVal('o');
        lastx = tempx;
        lasty = tempy;
        System.out.println("computer played at:" + (char)(tempy + 'A') + " " + (tempx + 1));
        totalmarked++;
    }
    public void play(int x,char y){
        int a = y - 'A';
        if(totalmarked %2 == 0)
            hexCells.get(x).get(a).setVal('x');
        else 
            hexCells.get(x).get(a).setVal('o');
        lastx = x;
        lasty = y - 'A';
        totalmarked++;
    
    }
    public void isWin(char player, int x, int y, boolean[] winCondition, int[][] map){
        if (x >= size || y >= size || x < 0 || y < 0 || map[x][y] == 1 || (winCondition[0] && winCondition[1]))return;
        if (player == 'x' && hexCells.get(x).get(y).getVal() != 'x')return;
        if (player == 'o' && hexCells.get(x).get(y).getVal() != 'o')return;
        hexCells.get(x).get(y).setVal((char) (hexCells.get(x).get(y).getVal()-' '));
        if (player == 'x') {
            if (x == 0)winCondition[0] = true;
            if (x == size - 1)winCondition[1] = true;
        }
        if (player == 'o') {
            if (y == 0)winCondition[0] = true;
            if (y == size - 1)winCondition[1] = true;
        }
        map[x][y] = 1;

        isWin(player, x - 1, y, winCondition, map);
        isWin(player, x - 1, y + 1, winCondition, map);
        isWin(player, x, y + 1, winCondition, map);
        isWin(player, x + 1, y, winCondition, map);
        isWin(player, x + 1, y - 1, winCondition, map);
        isWin(player, x, y - 1, winCondition, map);
        if (winCondition[0] && winCondition[1]) return;
        hexCells.get(x).get(y).setVal((char) (hexCells.get(x).get(y).getVal()+' '));
    }
    public boolean checkWin(char player){
        for (int i = 0; i < size; i++) {
            int[][] map = new int[26][26];
            boolean[] winCondition ={false,false} ;
            if (player == 'x' && hexCells.get(0).get(i).getVal() == 'x') {
                isWin(player, 0, i, winCondition, map);
            }
            else if (hexCells.get(i).get(0).getVal() == 'o') {
                isWin(player, i, 0, winCondition, map);
            }
            if (winCondition[0] && winCondition[1])
                return true;
            
        }
    return false;
    }
    public void playGame(){
         if(winCond == 1){
            System.out.println("\n player1 won");
            displayBoard();
            return;
        }

        else if(winCond == 2){
            System.out.println("\n player1 or computer won");
            displayBoard();
            return;
        }

        displayBoard();

        if (type == '1') {
            gameForComputer();
        }
        else {
            gameForUser();
        }
    }
    public int totalMarked() { 
        return totalmarked; 
    }
    public boolean gameForUser(){
        while (true) {
            System.out.println("if you want quit type 'q'");
            if (totalmarked % 2 == 0)
                System.out.println("Turn for 1 please write num and char in given format(A 1)");
            else
                System.out.println("Turn for 2 please write num and char in given format(A 1)");

            int x, y;
            char c;
            c = scanner.next().charAt(0);
            if (c == 'q') return true;
            x = scanner.nextInt();
            y = c - 'A';
            x--;
            //Checks is movement avalaible
            if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || hexCells.get(x).get(y).getVal() != '.') {
                System.out.println("\nwrong ! Try again");
                continue;
            }

            play(x, (char)(y + 'A'));

            displayBoard();
            if (totalmarked % 2 == 0) {
                if (checkWin('x')) {
                    System.out.println("\n player1 won");
                    winCond = 1;
                    displayBoard();
                    return true;
                }
            }

            else {
                if (checkWin('o')) {
                    System.out.println("\n player2 won");
                    winCond = 2;
                    displayBoard();
                    return true;
                }
            }
            if (totalmarked == (size * size)) {
                System.out.println("\n DRAW!!");
                return true;
            }

        }
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void setType(char type) {
        this.type = type;
    }
    public boolean gameForComputer(){
        while (true) {
            System.out.println("if you want quit type 'q'");
            System.out.println("please write num and char in given format(A 1)");
            int x, y;
            char c;
            c = scanner.next().charAt(0);
            if (c == 'q') return true;
            x = scanner.nextInt();
            y = c - 'A';
            x--;
            //Checks is movement avalaible
            if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || hexCells.get(x).get(y).getVal() != '.') {
                System.out.println("\nwrong ! Try again");
                continue;
            }
            play(x, c);
            displayBoard();

            if (checkWin('x')) {
                System.out.println("\n player1 won");
                winCond = 1;
                displayBoard();
                return true;
            }
            play();
            displayBoard();
            if (checkWin('o')) {
                System.out.println("\n computer won");
                winCond = 2;
                displayBoard();
                return true;
            }
            if (totalmarked == (size * size)) {
                System.out.println("\n DRAW!!");
                return true;
            }
        }
        
    }
    public boolean compare(Hex a) {
        return totalmarked > a.totalmarked;
    }  

    public int getLastx() {
        return lastx;
    }

    public int getLasty() {
        return lasty;
    }

    public void reset(){
        createBoard();
        HW7.mark=0;
        for (int i = 0 ; i < gameScreen.arr.length;i++){
            for (int j =0;j<gameScreen.arr.length;j++){
                gameScreen.arr[i][j].setBackground(Color.darkGray);
                hexCells.get(i).get(j).setVal('.');
            }
        }
        HW7.moves.clear();
    }
    
    public void save() throws IOException{
        String filename = JOptionPane.showInputDialog("File Name :");
        try {
            FileWriter myWriter = new FileWriter(filename);
            int size = gameScreen.arr.length;
            for(int i =0;i<26;i++){
                for(int j = 0;j<26;j++){
                    if(size <=i || size <=j)
                        myWriter.write(".");
                    else if(gameScreen.arr[i][j].getBackground() == Color.RED)
                        myWriter.write("x");
                    else if(gameScreen.arr[i][j].getBackground() == Color.blue)
                        myWriter.write("o");
                    else
                        myWriter.write(".");
                      
                    //myWriter.write(hexCells.get(i).get(j).getVal());
                }
                myWriter.write("\n");
            }
            myWriter.write(size+"\n");
            myWriter.write(type+"\n");
            myWriter.write(lastx+"\n");
            myWriter.write(lasty+"\n");
            myWriter.write(totalmarked+"\n");
            myWriter.write(winCond+"\n");
            for(int i = 0;i< HW7.moves.size();i++){
               myWriter.write(HW7.moves.get(i).getX()+" "+HW7.moves.get(i).getY()); 
               if(i != HW7.moves.size()-1)
                   myWriter.write("\n");
            }
            myWriter.close();
        } 
        catch (Exception e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
    
    public void undo(){
        if(HW7.moves.size() == 0) {
            JOptionPane.showMessageDialog(null,"There is no move", "error",JOptionPane.ERROR_MESSAGE);
            return;
        }
        int x = HW7.moves.get(HW7.moves.size()-1).getX();
        int y = HW7.moves.get(HW7.moves.size()-1).getY();
        
        gameScreen.arr[x][y].setBackground(Color.darkGray);
        hexCells.get(x).get(y).setVal('.');
        HW7.mark--;
        HW7.moves.remove(HW7.moves.size()-1);
        
    }
    private int toInt(String s){
        int res=0;
        for(int i = 0;i< s.length();i++){
            if(s.charAt(i) == '\n' || s.charAt(i)=='\0') break;
            res*=10;
            res+=s.charAt(i)-'0';
        }
        return res;
    }
    
    public void load(){
        HW7.moves.clear();
        String filename = JOptionPane.showInputDialog("File Name :");
        try {
            
            File myObj = new File(filename);
            Scanner myReader = new Scanner(myObj);
            int counter = 0;
            while (myReader.hasNextLine()) {
                
                String data = myReader.nextLine();
                if(counter <26){
                    for(int i = 0;i<26;i++){
                        //System.out.println("sa");
                        hexCells.get(counter).get(i).setVal(data.charAt(i));
                    }
                }
                else if (counter == 26){
                    size = toInt(data);
                }
                else if(counter == 27){
                    type = data.charAt(0);
                }
                else if(counter == 28){
                    lastx = toInt(data);
                }
                else if(counter == 29){
                    lasty = toInt(data);
                }
                else if(counter == 30){
                    totalmarked = toInt(data);
                    HW7.mark = totalmarked;
                }
                else if(counter == 31){
                    winCond = toInt(data);
                }
                else{
                    
                    int t1 = 0;
                    int t2 = 0;
                    int i = 0;
                    while(data.charAt(i) != ' '){
                        //System.out.println(data+i);
                        t1*=10;
                        t1+=data.charAt(i)-'0';
                        i++;
                    }
                    i++;
                    while(i<data.length() && data.charAt(i) != '\n' && data.charAt(i) != '\0'){
                        //System.out.println(data+i);
                        t2*=10;
                        t2+=data.charAt(i)-'0';
                        i++;
                    }
                    HW7.moves.add(new point(t1, t2));
                    
                }
                counter++;
            }
            myReader.close();
     
            
            
        } 
        catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
    
    public char getType(){
        return type;
    }
    
}
