package md2html;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

import java.util.Arrays;

public class Scanner {
    private final Reader reader;
    private int pos;
    private char[] buffer;
    private void constructFields() throws IOException {
        buffer = new char[1024];
        getNewBuffer();
    }

    public Scanner(String fileName, String format) throws IOException{
        reader = new InputStreamReader(new FileInputStream(fileName), format);
        constructFields();
    }

    private boolean isTranslate(char symbol) {
        return symbol == '\n' || symbol == '\r';
    }

    private void takeNewInput() throws IOException{
        if (pos >= buffer.length) {
            getNewBuffer();
        }
    }

    private void getNewBuffer() throws IOException {
        int len = reader.read(buffer);
        if (len >= 0) {
            pos = 0;
            buffer = Arrays.copyOf(buffer, len);
        }
    }

    public boolean hasNextLine() throws IOException{
        return pos < buffer.length;
    }

    public String nextLine() throws IOException{
        StringBuilder line = new StringBuilder();
        while (pos < buffer.length) {
            char symbol = buffer[pos];

            if (isTranslate(symbol)) {
                break;
            }

            line.append(symbol);

            pos++;
            takeNewInput();
        }
        return line.toString();
    }
    public void goNextLine() throws IOException {

        while (pos < buffer.length && buffer[pos] == ' ') {
            pos++;
            takeNewInput();
        }
        if (pos < buffer.length && isTranslate(buffer[pos])) {
            for (int i = 0; i < System.lineSeparator().length(); i++) {
                pos++;
                takeNewInput();
            }
        }
    }

    public void close() throws IOException{
        reader.close();
    }
}