package Y2024.D01Historian_Hysteria;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;
import java.util.stream.Collectors;

public class Part1n2 {

    static ArrayList leftList = new ArrayList<Integer>();
    static ArrayList rightList = new ArrayList<Integer>();

    private static void fileReader(String filePath){
        try {
            BufferedReader br = new BufferedReader(new FileReader(filePath));
            String s = null;
            while ((s = br.readLine()) != null){
                String[] temp = s.split("   ");
                leftList.add(Integer.parseInt(temp[0]));
                rightList.add(Integer.parseInt(temp[1]));
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());;
        }
    }

    //Part 1

    private static List<Integer> getSortedList(ArrayList<Integer> originalList){
        List<Integer> temp = new ArrayList<>(originalList);
        return temp.stream().sorted().toList();
    }

    private static int getDifferenceBtwLists(ArrayList list1, ArrayList list2){
        int difference = 0;
        List<Integer> sortedList1 = getSortedList(list1);
        List<Integer> sortedList2 = getSortedList(list2);
        int count = 0;
        int totalResult = 0;
        while (count < sortedList1.size()){
            totalResult += Math.abs(sortedList1.get(count) - sortedList2.get(count));
            count++;
        }
        return totalResult;
    }

    //Part 2

    private static Map<Integer,Long> countDuplicateTotalInList (List<Integer> list){
        ArrayList<Integer> temp = new ArrayList<>(list);
        Map<Integer, Long> map = temp.stream().collect(Collectors.groupingBy(a -> a, Collectors.counting()));
        return map;
    }

    private static int calculateIndividualSimilarityScore (int valueFromLeftList, int countFromRightList){
        return valueFromLeftList*countFromRightList;
    }

    private static int calculateTotalSimilarityScore (List<Integer> leftList, List<Integer> rightList){
        Map<Integer,Long> countDuplicate = countDuplicateTotalInList(rightList);
        int totalScore = 0;
        List<Integer> temp = new ArrayList<>(leftList);
        return temp.stream().mapToInt(a -> a*countDuplicate.getOrDefault(a,0L).intValue()).sum();
    }

    public static void main(String[] args) {
        Part1n2.fileReader("src/main/java/Y2024/D01Historian_Hysteria/Input");
        System.out.println("Part 1 " + getDifferenceBtwLists(leftList, rightList));
        System.out.println("Part 2 " + calculateTotalSimilarityScore(leftList, rightList));
    }
}
