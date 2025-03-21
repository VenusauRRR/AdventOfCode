package Y2024.D06GuardGallivant;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;

public class Part1n2 {
    static ArrayList<ArrayList<Character>> board = new ArrayList();

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
    private static Integer[] findStartIndex(ArrayList<ArrayList<Character>> board){
        int x = -1;
        int y = -1;
        for (ArrayList<Character> row : board){
            for (Character c : row){
                if (c == '^'){
                    x = row.indexOf(c);
                    y = board.indexOf(row);
                }
            }
        }
        System.out.println("x:" + x + " y:" + y);
        return new Integer[]{x, y};
    }

    //check if every location is qualified to win the game
    private static boolean checkIfGuardLeaveTheBoard(int xIndex, int yIndex){
        return (xIndex==0 || xIndex==board.get(0).size()-1 ||
                yIndex==0 || yIndex==board.size()-1) ? true : false;
    }

    //check if there's obstacles at the front
    //change direction
    //mark "X"
    //check all "X"

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D06GuardGallivant/testInput");
        findStartIndex(board);
    }
}
