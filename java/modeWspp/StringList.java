import java.util.Arrays;

public class StringList {
    private int size;
    private String[] list;

    public StringList() {
        size = 0;
        list = new String[1];
    }

    public void add(String x) {
        if (size == list.length) {
            list = growList(list);
        }

        list[size++] = x;
    }
    
    public String get(int ind) {
        return list[ind];
    }

    public void set(int ind, String value) {
        list[ind] = value;
    }

    private String[] growList(String[] list) {
        return Arrays.copyOf(list, size * 2);
    }

    public int length() {
        return size;
    }
} 