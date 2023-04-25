import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner fileScan = new Scanner(System.in);
        int a = fileScan.nextInt();
        int b = fileScan.nextInt();
        int n = fileScan.nextInt();
        System.out.println(((n - b + (b - a) - 1) / (b - a)) * 2 + 1);
    }
}