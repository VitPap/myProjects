import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int n = scan.nextInt();
        int m = scan.nextInt();
        IntList[] g = new IntList[n + 1];
        boolean[] isTeam = new boolean[n + 1];

        for (int i = 1; i <= n; i++) {
            g[i] = new IntList();
        }
        for (int i = 0; i < n - 1; i++) {
            int x = scan.nextInt();
            int y = scan.nextInt();

            g[x].add(y);
            g[y].add(x);
        }

        int root = 0;
        for (int i = 0; i < m; i++) {
            root = scan.nextInt();
            isTeam[root] = true;
        }
        int[] height = new int[n + 1];
        int best = -1, rootCandidate = root;
        int[] pred = new int[n + 1];
        dfs(root, pred, g, height);

        for (int i = 1; i <= n; i++) {
            if (isTeam[i] && height[i] > best) {
                best = height[i];
                rootCandidate = i;
            }
        }

        while (height[rootCandidate] != best / 2) {
            rootCandidate = pred[rootCandidate];
        }
        pred[rootCandidate] = 0;

        dfs_check(rootCandidate, pred, height, g);

        boolean isGood = true;
        int distance = -1;

        for (int i = 1; i <= n; i++) {
            if (isTeam[i]) {
                if (distance == -1 || distance == height[i]) {
                    distance = height[i];
                } else {
                    isGood = false;
                }
            }
        }

        if (isGood) {
            System.out.println("YES");
            System.out.println(rootCandidate);
        } else {
            System.out.println("NO");
        }
    }

    public static void dfs(
            int v,
            int[] pred,
            IntList[] g,
            int[] height
    ) {
        height[v] = (pred[v] == 0 ? 0 : height[pred[v]] + 1);

        for (int i = 0; i < g[v].length(); i++) {
            int nextV = g[v].get(i);
            if (nextV != pred[v]) {
                pred[nextV] = v;
                dfs(nextV, pred, g, height);
            }
        }
    }
    public static void dfs_check(
            int v,
            int[] pred,
            int height[],
            IntList[] g
    ) {
        height[v] = (pred[v] == 0 ? 0 : height[pred[v]] + 1);
        for (int i = 0; i < g[v].length(); i++) {
            int nextV = g[v].get(i);
            if (nextV != pred[v]) {
                pred[nextV] = v;
                dfs_check(nextV, pred, height, g);
            }
        }
    }
}


class IntList {
    private int size;
    private int[] list;

    public IntList() {
        size = 0;
        list = new int[1];
    }

    public void add(int x) {
        if (size == list.length) {
            list = growList(list);
        }

        list[size++] = x;
    }

    public int get(int ind) {
        return list[ind];
    }

    public void set(int ind, int value) {
        list[ind] = value;
    }
    public void deleteBack() {
        size--;
    }

    private int[] growList(int[] list) {
        return Arrays.copyOf(list, size * 2);
    }

    public int length() {
        return size;
    }
}