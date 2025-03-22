package Y2024.D06GuardGallivant;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

public class Part1n2 {
    static ArrayList<ArrayList<Character>> board = new ArrayList();
    static Integer[] currectPosition = new Integer[2];
    static int currentDirection = 0;
    static final char[] directions = {'N', 'E', 'S', 'W'};

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
            System.out.println(board.toString());
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
    private static boolean checkIfGuardLeaveTheBoard(int xIndex, int yIndex){
        return (xIndex==0 || xIndex==board.get(0).size()-1 ||
                yIndex==0 || yIndex==board.size()-1) ? true : false;
    }

    //get next position
    private static void getNext_N(){
        for (int i = currectPosition[0]; i >= 0; i--) {
            if (board.get(i).get(currectPosition[1]) == '#'){
                currentDirection = (currentDirection+1)%3;
                board.get(i+1).set(currectPosition[1],'>');
                break;
            }
            board.get(i).set(currectPosition[1],'X');
            currectPosition[0] = i;
        }
    }

    //mark "X"
    //check all "X"

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D06GuardGallivant/testInput");
        findStartIndex(board);
        getNext_N();
        System.out.println(board.toString());
    }
}
