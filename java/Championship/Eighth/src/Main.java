import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int n = scan.nextInt();
        int[][] ar = new int[n][n];
        int[][] ans = new int[n][n];

        for (int i = 0; i < n; i++) {
            String row = scan.next();

            for (int j = 0; j < n; j++) {
                ar[i][j] = (int)row.charAt(j) - 48;
                ans[i][j] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (ar[i][j] == 1) {
                    ans[i][j] = 1;
                    for (int u = j + 1; u < n; u++) {
                        ar[i][u] = (ar[i][u] + 10 - ar[j][u]) % 10;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(ans[i][j]);
            }
            System.out.println();
        }
    }
}