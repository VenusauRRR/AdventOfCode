package Y2024.D02RedNoseReports;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Part1n2 {
    static ArrayList<Integer> report = new ArrayList<>();
    static ArrayList<ArrayList<Integer>> reportList = new ArrayList<>();

    private static void fileReader(String filePath){
        try {
            Scanner sc = new Scanner(new File(filePath));
            String s = null;
            while (sc.hasNextLine()) {
                s = sc.nextLine();
                Arrays.stream(s.split(" ")).forEach(x -> report.add(Integer.parseInt(x)));
                reportList.add(new ArrayList<>(report));
                report.clear();
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D02RedNoseReports/Input");
    }
}
