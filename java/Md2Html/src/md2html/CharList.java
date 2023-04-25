package md2html;

import java.io.IOException;
import java.util.Arrays;

public class CharList {
    private char[] list;
    private int pos;

    public CharList() {
        list = new char[1];
        pos = 0;
    }

    public void add(char ch) {
        if (pos == list.length) {
            list = grow(list);
        }

        list[pos++] = ch;
    }

    public int size() {
        return pos;
    }
    public char get(int pos) {
        return list[pos];
    }
    public void pop() {
        pos--;
    }
    private char[] grow(char[] list) {
        return Arrays.copyOf(list, list.length * 2);
    }
}
