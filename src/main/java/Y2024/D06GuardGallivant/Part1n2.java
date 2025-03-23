package Y2024.D06GuardGallivant;

import javax.swing.plaf.synth.SynthOptionPaneUI;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

public class Part1n2 {
    static ArrayList<ArrayList<Character>> board = new ArrayList();
    static Integer[] currectPosition = new Integer[2];
    static int currentDirection = 0;
    static final char[] directions = {'N', 'E', 'S', 'W'};
    static boolean ifGuardLeave = false;
    //read data
    private static void fileReader(String filePath){
        try(BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String s = "";
            while((s = br.readLine()) != null){
                ArrayList<Character> temp = new ArrayList<>();
                int count = 0;
                while(count < s.length()){
                    temp.add(s.charAt(count));
                    count++;
                }
                board.add(temp);
            }
        } catch (
                Exception e) {
            throw new RuntimeException(e);
        }
    }

    //find the start location
    private static void findStartIndex(ArrayList<ArrayList<Character>> board){
        for (ArrayList<Character> row : board){
            for (Character c : row){
                if (c == '^'){
                    currectPosition[0] = board.indexOf(row);
                    currectPosition[1] = row.indexOf(c);
                }
            }
        }
    }

    //check if every location is qualified to win the game
    private static void checkIfGuardLeaveTheBoard(int xIndex, int yIndex){
        ifGuardLeave = (xIndex==0 || xIndex==board.get(0).size()-1 ||
                yIndex==0 || yIndex==board.size()-1) ? true : false;
    }

    //exit the game if the guard is left
    private static void ifExitGame (){
        checkIfGuardLeaveTheBoard(currectPosition[0],currectPosition[1]);
        if (ifGuardLeave){
            System.out.println("Part 1: " + countAllMarkedX());
            System.exit(0);
        }
    }

    //get next position
    private static void getNext_N(){
        for (int i = currectPosition[0]; i >= 0; i--) {
            if (board.get(i).get(currectPosition[1]) == '#'){
                board.get(i+1).set(currectPosition[1],'>');
                break;
            } else {

            board.get(i).set(currectPosition[1],'X');
            currectPosition[0] = i;
            ifExitGame();
            }
        }
    }

    private static void getNext_E(){
        for (int i = currectPosition[1]; i < board.get(0).size(); i++) {
            if (board.get(currectPosition[0]).get(i) == '#'){
                board.get(currectPosition[0]).set(i-1,'v');
                break;
            } else {
            board.get(currectPosition[0]).set(i,'X');
            currectPosition[1] = i;
            ifExitGame();
            }
        }
    }

    private static void getNext_S(){
        for (int i = currectPosition[0]; i < board.size(); i++) {
            if (board.get(i).get(currectPosition[1]) == '#'){
                board.get(i-1).set(currectPosition[1],'<');
                break;
            } else {
            board.get(i).set(currectPosition[1],'X');
            currectPosition[0] = i;
            ifExitGame();
            }
        }
    }

    private static void getNext_W(){
        for (int i = currectPosition[1]; i >= 0; i--) {
            if (board.get(currectPosition[0]).get(i) == '#'){
                board.get(currectPosition[0]).set(i+1,'^');
                break;
            } else {
            board.get(currectPosition[0]).set(i,'X');
            currectPosition[1] = i;
            ifExitGame();
            }
        }
    }

    //check all "X"
    private static int countAllMarkedX() {
//        int count = 0;
//        for (ArrayList<Character> row : board) {
//            for (Character c : row) {
//                if (c == 'X') {
//                    count++;
//                }
//            }
//        }
//        return count;

        return (int) board.stream().flatMap(i -> i.stream()).filter(j -> j=='X').count();
    }

    private static void gameLogic() {
        findStartIndex(board);
        while (!ifGuardLeave){
            getNext_N();
            getNext_E();
            getNext_S();
            getNext_W();
        }
    }

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D06GuardGallivant/input");
        gameLogic();
    }
}
