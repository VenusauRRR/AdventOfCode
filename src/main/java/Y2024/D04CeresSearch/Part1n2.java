package Y2024.D04CeresSearch;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

public class Part1n2 {
    static ArrayList<String> list = new ArrayList<>();
    static int stringLength;
    static int count_part1 = 0;
    static int count_part2 = 0;

    private static void fileReader(){
        String filePath = "src/main/java/Y2024/D04CeresSearch/input";
        try {
            BufferedReader br = new BufferedReader(new FileReader(filePath));
            String s = "";
            while ((s = br.readLine()) != null) {
                list.add(s);
            }
            stringLength = list.get(0).length();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    //Part 1
    private static void horizontal(){
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < stringLength-3; j++){
                if (list.get(i).substring(j,j+4).equals("XMAS")){
                    count_part1++;}
            }

        }

        //horizontal - written backwards
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < stringLength-3; j++){
                if (list.get(i).substring(j,j+4).equals("SAMX")){
                    count_part1++;}
            }

        }
    }

    private static void vertical(){
        for (int i = 0; i < list.size()-3; i++){
            for (int j = 0; j < stringLength; j++){
                if (list.get(i).charAt(j)=='X' &&
                    list.get(i+1).charAt(j)=='M' &&
                    list.get(i+2).charAt(j)=='A' &&
                    list.get(i+3).charAt(j)=='S'){
                    count_part1++;
                }
            }
        }

        //vertical - written backwards
        for (int i = 0; i < list.size()-3; i++){
            for (int j = 0; j < stringLength; j++){
                if (list.get(i).charAt(j)=='S' &&
                        list.get(i+1).charAt(j)=='A' &&
                        list.get(i+2).charAt(j)=='M' &&
                        list.get(i+3).charAt(j)=='X'){
                    count_part1++;
                }
            }
        }
    }

    private static void diagonal(){

        //right diagonal
        for (int i = 0; i < list.size()-3; i++){
            for (int j = 0; j < stringLength-3; j++){
                if (list.get(i).charAt(j)=='X' &&
                list.get(i+1).charAt(j+1)=='M' &&
                list.get(i+2).charAt(j+2)=='A' &&
                list.get(i+3).charAt(j+3)=='S'){
                    count_part1++;
                }
            }
        }

        //right diagonal - written backwards
        for (int i = 0; i < list.size()-3; i++){
            for (int j = 0; j < stringLength-3; j++){
                if (list.get(i).charAt(j)=='S' &&
                    list.get(i+1).charAt(j+1)=='A' &&
                    list.get(i+2).charAt(j+2)=='M' &&
                    list.get(i+3).charAt(j+3)=='X'){
                    count_part1++;
                }
            }
        }

        //left diagonal
        for (int i = 0; i < list.size()-3; i++){
            for (int j = 3; j < stringLength; j++){
                if (list.get(i).charAt(j)=='X' &&
                    list.get(i+1).charAt(j-1)=='M' &&
                    list.get(i+2).charAt(j-2)=='A' &&
                    list.get(i+3).charAt(j-3)=='S'){
                    count_part1++;
                }
            }
        }

        //left diagonal - written backwards
        for (int i = 0; i < list.size()-3; i++){
            for (int j = 3; j < stringLength; j++){
                if (list.get(i).charAt(j)=='S' &&
                    list.get(i+1).charAt(j-1)=='A' &&
                    list.get(i+2).charAt(j-2)=='M' &&
                    list.get(i+3).charAt(j-3)=='X'){
                    count_part1++;
                }
            }
        }

    }

    private static int totalCount_part1(){
        horizontal();
        vertical();
        diagonal();
        return count_part1;
    }

    //Part 2

    //right diagonal
    private static boolean X_rightDiagonal(int i, int j){
        if (list.get(i).charAt(j)=='M' &&
                list.get(i+1).charAt(j+1)=='A' &&
                list.get(i+2).charAt(j+2)=='S'){
            return true;
        }
        return false;
    }

    //right diagonal - written backwards
    private static boolean X_rightDiagonalBackwards(int i, int j){
        if (list.get(i).charAt(j)=='S' &&
                list.get(i+1).charAt(j+1)=='A' &&
                list.get(i+2).charAt(j+2)=='M'){
            return true;
        }
        return false;
    }

    //left diagonal
    private static boolean X_leftDiagonal(int i, int j){
        if (list.get(i).charAt(j+2)=='M' &&
                list.get(i+1).charAt(j+1)=='A' &&
                list.get(i+2).charAt(j)=='S'){
            return true;
        }
        return false;
    }

    //left diagonal - written backwards
    private static boolean X_leftDiagonalBackwards(int i, int j){
        if (list.get(i).charAt(j+2)=='S' &&
                list.get(i+1).charAt(j+1)=='A' &&
                list.get(i+2).charAt(j)=='M'){
            return true;
        }
        return false;
    }

    private static void checkX_Diagonal(){
        for (int i = 0; i < list.size()-2; i++){
            for (int j = 0; j < stringLength-2; j++){
                if ((X_rightDiagonal(i, j) || X_rightDiagonalBackwards(i,j)) &&
                        (X_leftDiagonal(i, j) || X_leftDiagonalBackwards(i,j))){
                    count_part2++;
                }
            }
        }
    }

    private static int totalCount_part2(){
        checkX_Diagonal();
        return count_part2;
    }

    public static void main(String[] args) {
        fileReader();
        System.out.println("Part 1: " + totalCount_part1());
        System.out.println("Part 2: " + totalCount_part2());
    }
}
