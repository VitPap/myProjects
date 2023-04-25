import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int n = scan.nextInt();
        int k = scan.nextInt();
        int result = 0;

        int[] bp = new int[n + 1];

        bp[0] = 1;
        for (int i = 1; i <= n; i++) {
            bp[i] = mult(bp[i - 1], k);
        }
        int[] d = new int[n + 1];

        for (int i = 0; i <= n; i++) {
            d[i] = -1;
        }

        for (int newN = 1; newN <= n; newN++) {
            for (int l = 1; l * l <= newN; l++) {
                if (newN % l == 0) {
                    result = sum(result, D(l, bp, d));
                    if (l != newN / l) {
                        result = sum(result, D(newN / l, bp, d));
                    }
                }
            }
        }

        System.out.println(result);
    }

    public static int R(int n, final int[] bp) {
        return n % 2 == 1 ? mult(n, bp[n / 2 + 1]) : mult(n / 2, sum(bp[n / 2], bp[n / 2 + 1]));
    }
    public static int D(int n, final int[] bp, int[] d) {
        if (d[n] != -1) {
            return d[n];
        }

        int dec = 0;

        for (int l = 1; l * l <= n; l++) {
            if (n % l == 0) {
                if (n == 1) {
                    continue;
                }
                dec = sum(dec, mult(n / l, D(l, bp, d)));
                if (l != n / l && l != 1) {
                    dec = sum(dec, mult(l, D(n / l, bp, d)));
                }
            }

        }
        d[n] = sub(R(n, bp), dec);
        return d[n];
    }
    public static int mult(long x, long y) {
        return (int)((x * y) % 998244353);
    }

    public static int sum(int x, int y) {
        return (x + y) % 998244353;
    }
    public static int sub(int x, int y) {
        return (x - y + 998244353) % 998244353;
    }
}