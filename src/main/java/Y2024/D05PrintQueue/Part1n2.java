package Y2024.D05PrintQueue;

import javax.swing.*;
import java.io.*;
import java.util.*;

public class Part1n2 {
    static Map<Integer,ArrayList<Integer>> pageOrderList = new HashMap<>();
    static ArrayList<ArrayList<Integer>> updateOrderList = new ArrayList<>();

    private static void fileReader(String inputFile) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(inputFile));
            boolean beforeBreakLine = true;
            String s = "";
            while ((s = br.readLine()) != null) {
                if (s.isEmpty()){
                    beforeBreakLine = false;
                    continue;}
                if (beforeBreakLine) {
                    Integer[] temp = stringToIntegerHashMap(s);
                    if (pageOrderList.containsKey(temp[0])) {
                        pageOrderList.get(temp[0]).add(temp[1]);
                    } else {
                        pageOrderList.put((temp[0]), new ArrayList<>(){{add(temp[1]);}});

                    }
                } else {
                    updateOrderList.add(stringToIntegerArrayList(s));
                }
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private static ArrayList<Integer> stringToIntegerArrayList(String input) {
        ArrayList<Integer> list = new ArrayList<>();
        String[] arr = input.split(",");
        for(String a : arr){
            list.add(Integer.parseInt(a));
        }
        return list;
    }

    private static Integer[] stringToIntegerHashMap(String input) {
        String[] arr = input.split("\\|");
        return new Integer[]{Integer.parseInt(arr[0]), Integer.parseInt(arr[1])};
    }

    private static boolean checkIfOrderIsCorrect (ArrayList<Integer> list){
        for (int i = 0; i < list.size()-1; i++) {
            try {

            boolean temp = pageOrderList.get(list.get(i)).contains(list.get(i+1));
            if (!temp) {
                return false;
            }
            } catch (NullPointerException e) {
                return false;
            }
        }
        return true;
    }

    private static int findMiddleNumber (ArrayList<Integer> list){
        boolean temp = checkIfOrderIsCorrect(list);
        int a = list.get((list.size()-1)/2);
        return temp? a : 0;
    }

    private static int totalSumOfMiddleNumbers(){
        return updateOrderList.stream().mapToInt(i -> findMiddleNumber(i)).sum();
    }

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D05PrintQueue/Input");
//        System.out.println(pageOrderList.toString());
//        System.out.println(updateOrderList.toString());
        System.out.println(totalSumOfMiddleNumbers());
    }
}
