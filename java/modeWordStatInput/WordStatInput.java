import java.util.LinkedHashMap;

import java.lang.StringBuilder;

import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class WordStatInput {

    public static void main(String args[]) {
        try {
            LinkedHashMap<String, Integer> countMap = new LinkedHashMap<String, Integer>();
            statInputWords(args, countMap);    

            try {
                printResult(args, countMap);
            } catch (IOException e) {
                System.out.println("Output file writing error " + e.getMessage());   
            }
        } catch (IOException e) {
            System.out.println("Input file reading error " + e.getMessage());   
        }
    }
    
    private static void addWordToMap(String word, LinkedHashMap<String, Integer> countMap) {
        word = word.toLowerCase();
        int count = 1;

        if (countMap.containsKey(word)) {
            count += countMap.get(word);
        }

        countMap.put(word, count);
    }

    private static void printResult(String[] args, LinkedHashMap<String, Integer> countMap) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(args[1]), "UTF8"));
        
        for (String word : countMap.keySet()) {
            writer.write(word + " " + countMap.get(word).toString() + "\n");
        }

        writer.close();  
    }

    private static void statInputWords(String[] args, LinkedHashMap<String, Integer> countMap) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), "UTF8"));
        StringBuilder word = new StringBuilder();

        int read = reader.read();

        while (read >= 0) {
            char symbol = (char)read;

            read = reader.read();

            if (Character.isLetter(symbol) || Character.getType(symbol) == Character.DASH_PUNCTUATION || symbol == '\'') {
                word.append(symbol);
                if (read < 0) {
                    addWordToMap(word.toString(), countMap);  
                }
            } else if (!word.isEmpty()){
                addWordToMap(word.toString(), countMap);  
                word.setLength(0);
            } 
        }

        reader.close();
    }

} 