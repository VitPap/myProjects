import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.StringReader;

import java.util.Arrays;

public class StatWord implements Comparable<StatWord> {
    public IntList first;
    public IntList second;

    public String word;
    public StatWord() {
        first = new IntList();
        second = new IntList();
    }
    public StatWord(IntList first, IntList second) {
        this.first = first;
        this.second = second;
    }

    public StatWord(String word) {
        this.word = word;
        first = new IntList();
        second = new IntList();
    }
    @Override
    public int compareTo(StatWord current) {
        return this.first.length() - current.first.length();
    }
}