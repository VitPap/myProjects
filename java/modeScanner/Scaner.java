import java.io.*;

import java.util.Arrays;

public class Scaner {
    private final Reader reader;
    private int pos;
    private char[] buffer;
    private boolean isHas;
    private void constructFields() throws IOException{
        buffer = new char[0];
        updBuffer();
    }

    public Scaner(InputStream input) throws IOException{
        reader = new BufferedReader(new InputStreamReader(input));    
        constructFields();
    }

    public Scaner(String input) throws IOException{
        reader = new BufferedReader(new StringReader(input));    
        constructFields();
    }

    public Scaner(String fileName, String format) throws IOException{
        reader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName), format));    
        constructFields();
    }

    private boolean updBuffer() throws IOException{
        char[] newBuffer = new char[1024];
        int len = reader.read(newBuffer);
        if (len > 0) {
            buffer = Arrays.copyOf(buffer, buffer.length + len);
            System.arraycopy(newBuffer, 0, buffer, buffer.length - len, len);
        }

        return len > 0;
    }

    private boolean isTranslate(char symbol) {
        return symbol == '\n' || symbol == '\r';
    }

    private void takeNewInput() throws IOException{
        if (pos == buffer.length) {
            if (isHas) {
                updBuffer();
            } else {
                getNewBuffer();
            }
        }
    }

    private void getNewBuffer() throws IOException {
        int len = reader.read(buffer);
        if (len >= 0) {
            pos = 0;
            buffer = Arrays.copyOf(buffer, len);
        }
    }

    private void clearBuffer() {
        if (pos >= 1024) {
            buffer = Arrays.copyOfRange(buffer, pos, buffer.length);
            pos = 0;
        }
    }
    public boolean hasNextLine() throws IOException{
        return pos < buffer.length;
    }
    public boolean hasNextInt() throws IOException{
        isHas = true;
        Integer res = nextInt();
        isHas = false;
        return res != null;
    }   

    public Boolean hasNext() throws IOException{
        isHas = true;
        String res = next();
        isHas = false;
        return res.length() != 0;
    }

    public String nextLine() throws IOException{
        StringBuilder line = new StringBuilder();
        while (pos < buffer.length) {
            char symbol = buffer[pos];

            pos++;
            takeNewInput();
            if (!isTranslate(symbol)) {
                if (!Character.isWhitespace(symbol) || (line.length() > 0 && line.charAt(line.length() - 1) != ' ')) {
                    line.append(symbol);
                }
            } else {
                if (pos < buffer.length && symbol == '\r' && buffer[pos] == '\n') {
                    pos++;
                    takeNewInput();
                }

                break;
            }
        }
        clearBuffer();

        return line.toString();
    }

    public Integer nextInt() throws IOException{
        StringBuilder result = new StringBuilder();
        int savedPos = pos;
        while (pos < buffer.length) {
            char symbol = buffer[pos];
            pos++;
            takeNewInput();

            if (Character.isWhitespace(symbol) && result != null) {
                break;
            } else {
                result.append(symbol);
            }
        }

        if (isHas) {
            pos = savedPos;
        } else {
            clearBuffer();
        }

        if (result.isEmpty()) {
            return null;
        }

        return Integer.parseInt(result.toString());
    }

    public String next() throws IOException{
        StringBuilder str = new StringBuilder();
        int savedPos = pos;
        while (pos < buffer.length) {
            char symbol = buffer[pos];
            pos++;
            takeNewInput();

            if (Character.isWhitespace(symbol) && !str.isEmpty()) {
                break;
            } else if (!Character.isWhitespace(symbol)) {
                str.append(symbol);
            }
        }

        if (isHas) {
            pos = savedPos;
        } else {
            clearBuffer();
        }

        return str.toString();
    }

    public void close() throws IOException{    
        reader.close();
    }
}