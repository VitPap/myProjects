import java.util.Scanner;

import static java.lang.Math.min;
import static java.lang.Math.max;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int n = scan.nextInt();

        int xl = Integer.MAX_VALUE;
        int xr = Integer.MIN_VALUE;
        int yl = xl;
        int yr = xr;

        for (int test = 0; test < n; test++) {
            int cx = scan.nextInt();
            int cy = scan.nextInt();
            int h = scan.nextInt();

            xl = min(xl, cx - h);
            yl = min(yl, cy - h);
            xr = max(xr, cx + h);
            yr = max(yr, cy + h);
        }

        System.out.println((xl + xr) / 2 + " " + (yl + yr) / 2 + " " + (1 + Math.max(xr - xl, yr - yl)) / 2);
    }
}