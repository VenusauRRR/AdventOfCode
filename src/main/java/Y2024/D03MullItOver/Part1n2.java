package Y2024.D03MullItOver;

import java.io.*;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Part1n2 {
    static ArrayList<Integer[]> sortedList = new ArrayList<>();
    static ArrayList<Integer[]> dontList = new ArrayList<>();
    static ArrayList<Integer[]> enabledList = new ArrayList<>();

    //Part 1
    private static void fileReader (String filename, ArrayList<Integer[]> list) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String s;
            while ((s = br.readLine()) != null) {
                String pattern = "mul\\((\\d+),(\\d+)\\)";
                Pattern compliedPattern = Pattern.compile(pattern);
                Matcher matcher = compliedPattern.matcher(s);
                while (matcher.find()) {
                    Integer[] memory = new Integer[]{Integer.parseInt(matcher.group(1)),Integer.parseInt(matcher.group(2))};
//                    System.out.println(memory.toString());
                    list.add(memory);

                }
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private static int getAllMultiplications (ArrayList<Integer[]> list){
        return list.stream().mapToInt(a -> a[0]*a[1]).sum();
    }

    //Part 2
    private static void readOnlyDontDataToList (String inputFile, String outputFile) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(inputFile));
            BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile,true));
            String s = "";
            while ((s = br.readLine()) != null) {
                String[] splitDontList = s.split("don't");
                for (int i = 1; i < splitDontList.length; i++) {
                    if (splitDontList[i].contains("do")) {
                        bw.append(splitDontList[i].split("do\\(")[0]);
                    } else {
                        bw.append(splitDontList[i]);
                    }
                    bw.append("\n");
                }
            }
                bw.close();
            fileReader(outputFile, dontList);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
/*

    private static void readEnabledList (String inputFile, String outputFile) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(inputFile));
            BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile,true));
            String s = "";
            while ((s = br.readLine()) != null) {
                String[] tempEnabledList = s.split("do\\(\\)");
                for (int i = 0; i < tempEnabledList.length; i++) {
                    if (tempEnabledList[i].contains("don't\\(\\)")) {
                        bw.append(tempEnabledList[i].split("don't\\(\\)")[0]);
                    } else {
                        bw.append(tempEnabledList[i]);
                    }
                }
            }
            bw.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
*/

    private static int getAllMultiplicationsFromDontList (ArrayList<Integer[]> list) {
        fileReader("src/main/java/Y2024/D03MullItOver/onlyDontListData",dontList);
        return getAllMultiplications(dontList);
    }

    private static int getTotalResultOfEnabledList(){
        return getAllMultiplications(sortedList)-getAllMultiplications(dontList);
    }

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D03MullItOver/input",sortedList);
        System.out.println("Part 1: " + getAllMultiplications(sortedList));
//        readEnabledList("src/main/java/Y2024/D03MullItOver/test","src/main/java/Y2024/D03MullItOver/enableListData");
//        fileReader("src/main/java/Y2024/D03MullItOver/enableListData",enabledList);
        readOnlyDontDataToList("src/main/java/Y2024/D03MullItOver/input","src/main/java/Y2024/D03MullItOver/onlyDontListData");
        System.out.println("Part 2: " + getTotalResultOfEnabledList());

    }
}
