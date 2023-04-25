import java.io.IOException;

import java.util.Arrays;

public class ReverseOctAbc {

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
    
        for (int i = countLines - 1; i >= 0; i--) {
            Scaner scan = null;

            try {
                scan = new Scaner(strArray[i]);
            } catch (IOException e) {
                System.out.println("Error with opening scanner string " + e.getMessage());
            }

            n = 0;
            
            try {
                while (scan.hasNext()) {
                    if (n == numbers.length) {
                        numbers = growArray(numbers);
                    }

                    String num = (scan.next()).toLowerCase();

                    int coef = 1;

                    if (num.charAt(0) == '-') {
                        coef = -1;
                        num = num.substring(1);
                    }

                    if (num.charAt(num.length() - 1) == 'o') {
                        numbers[n] = OctalConvertToInt(num);
                    } else if (Character.isLetter(num.charAt(0))) {
                        numbers[n] = decimalConvertToInt(num);
                    } else {
                        numbers[n] = stringToInt(num);
                    }

                    numbers[n++] *= coef;
                }
            } catch (IOException e) {
                System.out.println("Error with reading scanner " + e.getMessage());
            } finally {
                closeScanner(scan);
            }

            for (int j = n - 1; j >= 0; j--) {
                
                System.out.print(numbers[j] + " ");
            }

            System.out.println();
        }   
    }   

    private static int decimalConvertToInt(String str) {
        int res = 0;
    
        for (int i = 0; i < str.length(); i++) {
            int x = charCode(str.charAt(i));
            res *= 10;
            if (x >= 10) {
                res *= 10;
            }

            res += x;
        }

        return res;
    }

    private static int stringToInt(String str) {
        return (int)Long.parseLong(str);
    }

    private static int OctalConvertToInt(String str) {
        return (int)Long.parseLong(str.substring(0, str.length() - 1), 8);
    }

    private static int charCode(char c) {
        return ((int)c) - 97;
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