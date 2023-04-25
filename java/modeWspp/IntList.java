import java.util.Arrays;

public class IntList {
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

    private int[] growList(int[] list) {
        return Arrays.copyOf(list, size * 2);
    }

    public int length() {
        return size;
    }
} 