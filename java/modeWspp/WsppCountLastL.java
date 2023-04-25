import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;


public class WsppCountLastL {
    public static void main(String[] args) {
        Map<String, StatWord> countMap = new LinkedHashMap<>();

        Scannerr scan = openScanner(args[0]);
        try {
            statInputWords(countMap, scan);
        } catch (IOException e) {
            System.out.println("File reading error " + e.getMessage()) ;
        } finally {
            closeScanner(scan);
        }

        BufferedWriter writer = openWriter(args[1]);
        try {   
            printResult(countMap, writer);
        } catch (IOException e) {
            System.out.println("Output file writing error " + e.getMessage());
        } finally {
            closeWriter(writer);
        }
    }


    private static void addWordToMap(
            int countWords,
            int countLine,
            String word,
            Map<String, StatWord> countMap
    ) {
        word = word.toLowerCase();

        StatWord list;
        if (countMap.containsKey(word)) {
            list = countMap.get(word);
        } else {
            list = new StatWord(word);
        }
        list.first.add(countWords);
        list.second.add(countLine);
        countMap.put(word, list);
    }

    private static void printResult(
            Map<String, StatWord> countMap,
            BufferedWriter writer
    ) throws IOException {
        ArrayList<StatWord> list = new ArrayList<>(countMap.values());
        Collections.sort(list);

        for (StatWord current : list) {
            IntList indList = current.first;
            IntList lineList = current.second;
            String word = current.word;

            writer.write(word + " " + indList.length());

            for (int j = 0; j < indList.length(); j++) {
                if (j + 1 == indList.length() || (lineList.get(j) != lineList.get(j + 1))) {
                    writer.write(" " + indList.get(j));
                }
            }

            writer.newLine();
        }
    }

    private static void statInputWords(
            Map<String, StatWord> countMap,
            Scannerr fileScanner
    ) throws IOException {
        int countLine = 0;
        do {
            countLine++;
            int countWords = 0;

            while (fileScanner.hasNext()) {
                countWords++;
                addWordToMap(countWords, countLine, fileScanner.next(), countMap);
            }
        } while (fileScanner.moveToNextLine());
    }

    private static BufferedWriter openWriter(String fileName) {
        BufferedWriter writer = null;

        try {
            writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(fileName), "UTF8"));
        } catch(FileNotFoundException e) {
            System.out.println("Writing file not Found " + e.getMessage());
        } catch(IOException e) {
            System.out.println("Writing file found, but there is error in opening" + e.getMessage());
        }

        return writer;
    }

    private static Scannerr openScanner(String fileName) {
        Scannerr scan = null;

        try {
            scan = new Scannerr(fileName, "UTF8");
        } catch(FileNotFoundException e) {
            System.out.println("Reading file not Found " + e.getMessage());
        } catch(IOException e) {
            System.out.println("Reading file found, but there is error in opening" + e.getMessage());
        }

        return scan;
    }

    private static void closeWriter(BufferedWriter writer) {
        try {
            writer.close();
        } catch (IOException e) {
            System.out.println("Error with closing writing file " + e.getMessage());
        }
    }

    private static void closeScanner(Scannerr scan) {
        try {
            scan.close();
        } catch (IOException e) {
            System.out.println("Error with closing scanner " + e.getMessage());
        }
    }
} 
