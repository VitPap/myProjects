import java.util.Map;
import java.util.LinkedHashMap;
import java.util.InputMismatchException;

import java.lang.StringBuilder;

import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Wspp {

    private static int countWords;
    public static void main(String args[]) {
        Map<String, IntList> countMap = new LinkedHashMap<String, IntList>();

        countWords = 0;
        try {
            BufferedReader reader = openReader(args[0]);
            try {
                statInputWords(countMap, reader);
            } catch (IOException e) {
                System.out.println("File reading error " + e.getMessage()) ;
            } finally {
                reader.close();
            }
        } catch (FileNotFoundException e) {
            System.out.println("Input not found " + e.getMessage());   
        } catch (InputMismatchException e) {
            System.out.println("Invalid input format " + e.getMessage()) ;
        } catch (IOException e) {
            System.out.println("Openning input file error " + e.getMessage()) ;
        }

        try {
            BufferedWriter writer = openWriter(args[1]);
            try {   
                printResult(countMap, writer);
            } catch (IOException e) {
                System.out.println("Writing output file error " + e.getMessage());   
            } finally {
                writer.close();
            }
        } catch (IOException e) {
            System.out.println("Openning output file erorr " + e.getMessage());
        }
    }

    private static BufferedReader openReader(String fileName) throws FileNotFoundException, InputMismatchException, IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName), "UTF8"));
        
        return reader;
    }
    
    private static BufferedWriter openWriter(String fileName) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(fileName), "UTF8"));
        
        return writer;
    }

    private static void addWordToMap(String word, Map<String, IntList> countMap) {
        countWords++;
        word = word.toLowerCase();
        IntList list = countMap.getOrDefault(word, new IntList());

        list.add(countWords);
        countMap.put(word, list);
    }

    private static void printResult(Map<String, IntList> countMap, BufferedWriter writer) throws IOException {
            
        for (String word : countMap.keySet()) {
            IntList cur = countMap.get(word);
            writer.write(word + " " + Integer.toString(cur.length()));

            for (int i = 0; i < cur.length(); i++) {
                writer.write(" " + Integer.toString(cur.get(i)));
            }

            writer.write(System.lineSeparator());
        } 
    }

    private static void statInputWords(Map<String, IntList> countMap, BufferedReader reader) throws IOException {
        StringBuilder word = new StringBuilder();

        char[] buffer = new char[1024];
        int read = reader.read(buffer);
        int ind = 0;

        while (read >= 0 && ind < read) {
            char symbol = (char)buffer[ind++];

            if (Character.isLetter(symbol) || Character.getType(symbol) == Character.DASH_PUNCTUATION || symbol == '\'') {
                word.append(symbol);
            } else if (!word.isEmpty()){
                addWordToMap(word.toString(), countMap);
                word.setLength(0);
            } 

            if (ind == read) {
                ind = 0;
                read = reader.read(buffer);

                if (read == 0 && !word.isEmpty()) {
                    addWordToMap(word.toString(), countMap);
                }
            }
        }
    }
} 