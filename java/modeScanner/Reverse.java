import java.io.IOException;

import java.util.Arrays;

public class Reverse {

    public static void main(String[] args){
        Scaner scanner = null;
        
        try {
            scanner = new Scaner(System.in);
        } catch (IOException e) {
            System.out.println("Error with opening scanner system.in " + e.getMessage());
        }

        String[] strArray = new String[1];
        int[] numbers = new int[1];

        int n;
        int countLines = 0;

        try {
            while (scanner.hasNextLine()) {
                
                if (countLines == strArray.length) {
                    strArray = growArray(strArray);
                }
                
                strArray[countLines++] = scanner.nextLine();
            }
        } catch (IOException e) {
            System.out.println("Error with reading scanner " + e.getMessage());
        } finally {
            closeScanner(scanner);
        }
        closeScanner(scanner);

        for (int i = countLines - 1; i >= 0; i--) {
            Scaner scan = null;

            try {
                scan = new Scaner(strArray[i]);
            } catch (IOException e) {
                System.out.println("Error with opening scanner string " + e.getMessage());
            } 

            n = 0;
            
            try {    
                while (scan.hasNextInt()) {
                    if (n == numbers.length) {
                        numbers = growArray(numbers);
                    }

                    numbers[n++] = scan.nextInt();
                }
            } catch (IOException e) {
                System.out.println("Error with opening scanner string " + e.getMessage());
            } finally {
                closeScanner(scan);
            }
            closeScanner(scan);

            for (int j = n - 1; j >= 0; j--) {
                System.out.print(numbers[j] + " ");
            }

            System.out.println();
        }   
    }   

    private static int[] growArray(int[] arr) {
        return Arrays.copyOf(arr, arr.length * 2);
    }

    private static String[] growArray(String[] arr) {
        return Arrays.copyOf(arr, arr.length * 2);
    }

    private static void closeScanner(Scaner scan) {
        try {
            scan.close();
        } catch (IOException e) {
            System.out.println("Error with closing scanner " + e.getMessage());
        }
    }

} 