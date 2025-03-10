package Y2024.D03MullItOver;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Part1n2 {
    static ArrayList<Integer[]> sortedList = new ArrayList<>();

    private static void fileReader (String filename) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String s;
            while ((s = br.readLine()) != null) {
                String pattern = "mul\\((\\d+),(\\d+)\\)";
                Pattern compliedPattern = Pattern.compile(pattern);
                Matcher matcher = compliedPattern.matcher(s);
                while (matcher.find()) {
                    Integer[] memory = new Integer[]{Integer.parseInt(matcher.group(1)),Integer.parseInt(matcher.group(2))};
                    System.out.println(memory.toString());
                    sortedList.add(memory);

                }
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private static int getAllMultiplications (ArrayList<Integer[]> list){
        return list.stream().mapToInt(a -> a[0]*a[1]).sum();
    }

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D03MullItOver/Input");
        System.out.println("Part 1: " + getAllMultiplications(sortedList));
    }
}
