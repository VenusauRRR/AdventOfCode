package Y2024.D04CeresSearch;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Part1n2 {
    static ArrayList<String> list = new ArrayList<>();
    static int stringLength;
    static int count = 0;

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
                if (list.get(i).substring(j,j+4).equals("XMAS")){count++;}
            }

        }

        //horizontal - written backwards
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < stringLength-3; j++){
                if (list.get(i).substring(j,j+4).equals("SAMX")){count++;}
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
                    count++;
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
                    count++;
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
                    count++;
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
                    count++;
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
                    count++;
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
                    count++;
                }
            }
        }

    }

    private static int totalCount_part1(){
        fileReader();
        horizontal();
        vertical();
        diagonal();
        return count;
    }

    public static void main(String[] args) {
        System.out.println("Part 1: " + totalCount_part1());
    }
}
