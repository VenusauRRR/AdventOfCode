package Y2024.D02RedNoseReports;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.Collectors;

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

    private static String ifReportIsIncreasingOrDecreasing (ArrayList<Integer> report){
        int temp = report.get(1)-report.get(0);
        if (temp>=1 && temp<=3){
            return "increasing";
        } else if (temp<=-1 && temp>=-3) {
            return "decreasing";
        }
        return "err";
    }

    private static boolean ifReportIncreasingBy1To3 (ArrayList<Integer> report){
        boolean result = false;
        for (int i = 0; i < report.size()-1; i++) {
            int diff = report.get(i+1)-report.get(i);
            if (diff>=1 && diff<=3){
                result = true;
            } else {
                return false;
            }
        }
        return result;
    }

    private static boolean ifReportDecresingBy1To3 (ArrayList<Integer> report){
        boolean result = false;
        for (int i = 0; i < report.size()-1; i++) {
            int diff = report.get(i+1)-report.get(i);
            if (diff<=-1 && diff>=-3){
                result = true;
            } else {
                return false;
            }
        }
        return result;
    }

    private static int count1ifReportSafe (ArrayList<Integer> report, String status){
        switch (status){
            case "increasing": return ifReportIncreasingBy1To3 (report) ? 1 : 0;
            case "decreasing": return ifReportDecresingBy1To3 (report) ? 1 : 0;
            default: return 0;
        }
    }

    private static int countTotalSafeReports (ArrayList<ArrayList<Integer>> reportList){
        fileReader("src/main/java/Y2024/D02RedNoseReports/Input");
        int count = 0;
        for (int i = 0; i < reportList.size(); i++) {
            String status = ifReportIsIncreasingOrDecreasing(reportList.get(i));
            count += count1ifReportSafe(reportList.get(i),status);
        }
        return count;
    }

    public static void main(String[] args) {
        System.out.println(countTotalSafeReports(reportList));
    }
}
