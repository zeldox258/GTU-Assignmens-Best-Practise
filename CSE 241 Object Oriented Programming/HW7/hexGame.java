//package hw7;

import java.io.IOException;

public interface hexGame {
    void createBoard();
    int getSize();
    void displayBoard();
    void play();
    void play(int x,char y);
    void isWin(char player, int x, int y, boolean[] winCondition, int[][] map);
    boolean checkWin(char player);
    void playGame();
    boolean gameForUser();
    boolean gameForComputer();
    boolean compare(Hex a);
    public void undo();
    public void load();
    public void save()throws IOException;
}
