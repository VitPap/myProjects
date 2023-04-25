package md2html;
import java.io.*;


public class Md2Html {
    public static void main(String[] args) {
        Scanner scan = null;
        StringBuilder answer = new StringBuilder();

        try {
            scan = new Scanner(args[0], "UTF-8");
        } catch (IOException e) {
            System.out.println("Error in opening scanner " + e.getMessage());
        }

        converter(scan, answer);

        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(args[1]), "UTF8"));
            writer.write(answer.toString());
            closeWriter(writer);
        } catch(FileNotFoundException e) {
            System.out.println("Writing file not Found " + e.getMessage());
        } catch(IOException e) {
            System.out.println("Writing file found, but there is error in opening" + e.getMessage());
        } finally {
            closeWriter(writer);
        }
    }

    private static void converter(Scanner scan, StringBuilder answer) {
        try {
            while (scan.hasNextLine()) {
                Paragraph parag = new Paragraph();

                while (scan.hasNextLine()) {
                    String line = scan.nextLine();
                    if (line.length() == 0 && !parag.isEmpty()) {
                        scan.goNextLine();
                        break;
                    } else if (line.length() != 0) {
                        if (!parag.isEmpty()) {
                            parag.addSeparator();
                        }
                        parag.add(line);
                    }
                    scan.goNextLine();
                }
                parag.closeParag(scan.hasNextLine());
                answer.append(parag);
            }

            closeScanner(scan);
        } catch (IOException e) {
            System.out.println("Error in reading file " + e.getMessage());
        } finally {
            closeScanner(scan);
        }
    }
    private static void closeScanner(Scanner scan) {
        try {
            scan.close();
        } catch (IOException e) {
            System.out.println("Error in closing scanner " + e.getMessage());
        }
    }

    private static void closeWriter(BufferedWriter writer) {
        try {
            writer.close();
        } catch (IOException e) {
            System.out.println("Error closing writer " + e.getMessage());
        }
    }
}