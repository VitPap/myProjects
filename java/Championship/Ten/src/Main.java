import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int t = scan.nextInt();

        for (int test = 0; test < t; test++) {
            Map<Integer, Integer> map = new HashMap<>();
            int n = scan.nextInt();

            int[] ar = new int[n];

            for (int i = 0; i < n; i++) {
               ar[i] = scan.nextInt();
            }

            int answer = 0;

            for (int i = n - 1; i >= 0; i--) {
                for (int j = 0; j < i; j++) {
                    int key = 2 * ar[i] - ar[j];
                    answer += map.getOrDefault(key, 0);
                }
                map.put(ar[i], map.getOrDefault(ar[i], 0) + 1);
            }
            System.out.println(answer);
        }
    }
}