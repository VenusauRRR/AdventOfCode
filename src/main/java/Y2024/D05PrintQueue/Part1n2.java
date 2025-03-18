package Y2024.D05PrintQueue;

import java.io.*;
import java.util.*;

public class Part1n2 {
    static Map<Integer,ArrayList<Integer>> pageOrderList = new HashMap<>();
    static ArrayList<ArrayList<Integer>> updateOrderList = new ArrayList<>();
    static ArrayList<ArrayList<Integer>> incorrectedList = new ArrayList<>();
    static ArrayList<ArrayList<Integer>> revisedIncorrectedList = new ArrayList<>();

    //Part 1
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
                    incorrectedList.add(list);
                    return false;
                }
            } catch (NullPointerException e) {
                incorrectedList.add(list);
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

    private static int totalSumOfMiddleNumbers(ArrayList<ArrayList<Integer>> list){
        return list.stream().mapToInt(i -> findMiddleNumber(i)).sum();
    }

    //Part 2
    private static ArrayList<Integer> fixIncorrectOrderList(ArrayList<Integer> list){
        ArrayList<Integer> newList = new ArrayList<>(list);
        int i = 0;
        boolean a = false;
        while(i < newList.size()-1){
            try{
                a = pageOrderList.get(newList.get(i)).contains(newList.get(i+1));
            } catch (NullPointerException e) {
            }
                if (a){
                    i++;
                    a = false;
                } else {
                    Collections.swap(newList, i, i+1);
                    i = 0;
                }
        }
        return newList;
    }

    private static void revisedOrderList (){
        for (ArrayList<Integer> list : incorrectedList) {
            revisedIncorrectedList.add(fixIncorrectOrderList(list));
        }
    }

    public static void main(String[] args) {
        fileReader("src/main/java/Y2024/D05PrintQueue/input");
        System.out.println("Part 1: " + totalSumOfMiddleNumbers(updateOrderList));
        revisedOrderList();
        System.out.println("Part 2: " + totalSumOfMiddleNumbers(revisedIncorrectedList));
    }
}
