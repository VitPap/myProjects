import java.util.Map;
import java.util.TreeMap;
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

public class WordStatWordsShingles {

    public static void main(String args[]) {
        Map<String, Integer> countMap = new TreeMap<String, Integer>();

        try {
            BufferedReader reader = openReader(args);
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
            BufferedWriter writer = openWriter(args);
            try {   
                printResult(countMap, writer);
            } catch (IOException e) {
                System.out.println("Writing output file error " + e.getMessage());   
            } finally {
                writer.close();
            }
        } catch (IOException e) {
            System.out.println("Openning output file erorr");
        }
    }

    private static BufferedReader openReader(String[] args) throws FileNotFoundException, InputMismatchException, IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), "UTF8"));
        
        return reader;
    }
    
    private static BufferedWriter openWriter(String[] args) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(args[1]), "UTF8"));
        
        return writer;
    }

    private static void addWordToMap(String word, Map<String, Integer> countMap) {
        word = word.toLowerCase();
        int count = 1 + countMap.getOrDefault(word, 0);

        countMap.put(word, count);
    }

    private static void printResult(Map<String, Integer> countMap, BufferedWriter writer) throws IOException {
            
        for (String word : countMap.keySet()) {
            writer.write(word + " " + countMap.get(word).toString() + "\n");
        } 
    }

    private static void statInputWords(Map<String, Integer> countMap, BufferedReader reader) throws IOException {
        StringBuilder word = new StringBuilder();

        char[] buffer = new char[1024];
        int read = reader.read(buffer);
        int ind = 0;

        while (read >= 0 && ind < read) {
            char symbol = (char)buffer[ind++];

            if (Character.isLetter(symbol) || Character.getType(symbol) == Character.DASH_PUNCTUATION || symbol == '\'') {
                word.append(symbol);

            } else if (!word.isEmpty()){
                parseWord(word.toString(), countMap);
                word.setLength(0);
            } 

            if (ind == read) {
                ind = 0;
                read = reader.read(buffer);

                if (read == 0 && !word.isEmpty()) {
                    parseWord(word.toString(), countMap);
                }
            }
        }
    }

    private static void parseWord(String word, Map<String, Integer> countMap) {
        if (word.length() < 3) {
            addWordToMap(word, countMap);
        }
        else 
        for (int i = 0; i <= word.length() - 3; i++) {
            addWordToMap(word.substring(i, i + 3), countMap);
        }
    }

} 