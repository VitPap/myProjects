import java.util.LinkedHashMap;

import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileNotFoundException;

public class WordStatInput {
    public static void main(String args[]) {
        LinkedHashMap<String, Integer> countMap = new LinkedHashMap<String, Integer>();
        
        statInputWords(args[0], countMap); 

        printResult(args[1], countMap);
    }
    
    private static void addWordToMap(String word, LinkedHashMap<String, Integer> countMap) {
        word = word.toLowerCase();
        int count = 1;

        if (countMap.containsKey(word)) {
            count += countMap.get(word);
        }

        countMap.put(word, count);
    }

    private static void printResult(String fileName, LinkedHashMap<String, Integer> countMap) {
        BufferedWriter writer = tryOpenWriter(fileName);
        
        try {
            for (String word : countMap.keySet()) {
                writer.write(word + " " + countMap.get(word).toString());
                writer.write(System.lineSeparator());
            }
        } catch (IOException e) {
            System.out.println("Error with writing " + e.getMessage());
        } finally {
            tryCloseWriter(writer);
        }
        
        tryCloseWriter(writer);
    }

    private static void statInputWords(String fileName, LinkedHashMap<String, Integer> countMap) {
        Scaner scan = tryOpenScanner(fileName);
        StringBuilder word = new StringBuilder();
        
        try {
            while (scan.hasNext()) { 
                String str = scan.next();
                for (int i = 0; i < str.length(); i++) {
                    char symbol = str.charAt(i); 
                    if (Character.isLetter(symbol) || Character.getType(symbol) == Character.DASH_PUNCTUATION || symbol == '\'') {
                        word.append(symbol);
                    } else if (!word.isEmpty()){
                        addWordToMap(word.toString(), countMap);  
                        word.setLength(0);
                    }
                } 

                if (!word.isEmpty()){
                    addWordToMap(word.toString(), countMap);  
                    word.setLength(0);
                }
            }
        } catch (IOException e) {
            System.out.println("Error with reading scanner " + e.getMessage());
        } finally {
            tryCloseScanner(scan);
        }
        tryCloseScanner(scan);
    }

    private static BufferedWriter tryOpenWriter(String fileName) {
        BufferedWriter writer = null;

        try {
            writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(fileName), "UTF8"));
        } catch(FileNotFoundException e) {
            System.out.println("Writing file not Found " + e.getMessage());
        } catch(IOException e) {
            System.out.println("Writing file found, but there is error in openning" + e.getMessage());
        }

        return writer;
    }

    private static Scaner tryOpenScanner(String fileName) {
        Scaner scan = null;

        try {
            scan = new Scaner(fileName, "UTF8");
        } catch(FileNotFoundException e) {
            System.out.println("Reading file not Found " + e.getMessage());
        } catch(IOException e) {
            System.out.println("Reading file found, but there is error in openning" + e.getMessage());
        }

        return scan;
    }

    private static void tryCloseWriter(BufferedWriter writer) {
        try {
            writer.close();
        } catch (IOException e) {
            System.out.println("Error with closing writing file " + e.getMessage());
        }
    }

    private static void tryCloseScanner(Scaner scan) {
        try {
            scan.close();
        } catch (IOException e) {
            System.out.println("Error with closing scanner " + e.getMessage());
        }
    }

    
} 