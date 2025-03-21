package Y2024.D06GuardGallivant;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

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
    //check if every location is qualified to win the game
    //check if there's obstacles at the front
    //change direction
    //mark "X"
    //check all "X"

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D06GuardGallivant/testInput");
    }
}
