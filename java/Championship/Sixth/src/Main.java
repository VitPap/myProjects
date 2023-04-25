import java.util.HashMap;
import java.util.Hashtable;
import java.util.Map;
import java.util.Scanner;
import static java.lang.Math.max;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int n = scan.nextInt();
        int[] ar = new int[n];
        int[] pref = new int[n];

        int maximum = 0;

        for (int i = 0; i < n; i++) {
            ar[i] = scan.nextInt();

            pref[i] = ar[i];

            if (i != 0) {
                pref[i] += pref[i - 1];
            }

            maximum = Math.max(maximum, ar[i]);
        }

        Map <Integer, Integer> calculated = new HashMap<>();

        int q = scan.nextInt();

        for (int test = 0; test < q; test++) {
            int t = scan.nextInt();

            if (calculated.containsKey(t)) {
                System.out.println(calculated.get(t));
            } else if (maximum > t) {
                System.out.println("Impossible");
            } else {
                int answer = 0;
                int from = 0;

                while (from < n) {
                    int l = from, r = n - 1;
                    int collectedSum = (l == 0 ? 0 : pref[l - 1]);

                    while (l < r) {
                        int md = (l + r + 1) / 2;
                        if (pref[md] - collectedSum > t) {
                            r = md - 1;
                        } else l = md;
                    }

                    from = l + 1;
                    answer++;
                }
                calculated.put(t, answer);

                System.out.println(answer);
            }
        }
    }
}