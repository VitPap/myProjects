import java.util.Scanner;
import java.util.Arrays;

public class Reverse {

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        String[] strArray = new String[1];
        int[] numbers = new int[1];

        int n = 0;
        int countLines = 0;

        while (scanner.hasNextLine()) {
            if (countLines == strArray.length) {
                strArray = growArray(strArray);
            }

            strArray[countLines++] = scanner.nextLine();
        }

        for (int i = countLines - 1; i >= 0; i--) {
            scanner = new Scanner(strArray[i]);
            n = 0;
            
            while (scanner.hasNextInt()) {
                if (n == numbers.length) {
                    numbers = growArray(numbers);
                }

                numbers[n++] = scanner.nextInt();
            }
            
            for (int j = n - 1; j >= 0; j--) {
                System.out.print(numbers[j] + " ");
            }

            System.out.println();
        }   

        scanner.close();
    }   

    private static int[] growArray(int[] arr) {
        return Arrays.copyOf(arr, arr.length * 2);
    }

    private static String[] growArray(String[] arr) {
        return Arrays.copyOf(arr, arr.length * 2);
    }
} 