import java.util.Scanner;
import java.util.Arrays;

public class ReverseAvg {

    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);
        int[][] matrix = new int[1][1];
        long[] arr = new long[1];
        int[] kol = new int[1];

        int countLines = 0;

        while (scan.hasNextLine()) {
            if (countLines == matrix.length) {
                matrix = growArray(matrix);
            }
    
            Scanner rowScanner = new Scanner(scan.nextLine());

            int countColumns = 0;

            while (rowScanner.hasNextInt()) {
                if (countColumns == arr.length) {
                    arr = growArray(arr);
                    kol = growArray(kol);
                }

                if (countColumns == matrix[countLines].length) {
                    matrix[countLines] = growArray(matrix[countLines]);
                }

                matrix[countLines][countColumns] = rowScanner.nextInt();
                arr[countColumns] += matrix[countLines][countColumns];
                kol[countColumns++]++;
            }
            matrix[countLines] = Arrays.copyOf(matrix[countLines], countColumns);

            countLines++;  
            rowScanner.close(); 
        }
        
        scan.close();

        for (int i = 0; i < countLines; i++) {
            long sumRow = calcRow(matrix[i]);
            
            int countColumns = 0;

            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print((arr[countColumns] - matrix[i][j] + sumRow) / (matrix[i].length + kol[countColumns] - 1) + " ");    
                countColumns++;
            }

            System.out.println();    
        }
    }   

    private static long calcRow(int[] row) {
        long result = 0; 
    
        for (int i = 0; i < row.length; i++) {
            result += row[i];
        }

        return result;
    }

    private static int[] growArray(int[] arr) {
        return Arrays.copyOf(arr, arr.length * 2);
    }

    private static long[] growArray(long[] arr) {
        return Arrays.copyOf(arr, arr.length * 2);
    }

    private static int[][] growArray(int[][] arr) {
        arr = Arrays.copyOf(arr, arr.length * 2);

        for (int i = arr.length / 2; i < arr.length; i++) {
            arr[i] = new int[1];
        }

        return arr;
    }
} 