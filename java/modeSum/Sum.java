public class Sum {

    public static void main(String args[]) {
        int result = 0;
        
        for (int i = 0; i < args.length; i = i + 1) {
            result = result + calc_row(args[i]);
        }
        System.out.println(result);
    }

    private static int calc_row(String str){
        int sum = 0;
        int currentNumber = 0;
        int coef = 1;

        for (int i = 0; i < str.length(); i = i + 1) {
            char currentChar = str.charAt(i);
            
            if (currentChar == '+' || currentChar == '-' || Character.isWhitespace(currentChar)) {
                sum = sum + coef * currentNumber;
                currentNumber = 0;
                coef = 1;
                
                if (currentChar == '-') {
                    coef = -1;
                }

            } else {
                currentNumber = currentNumber * 10 + (currentChar - '0');
            }

        }
        sum = sum + coef * currentNumber;

        return sum;
    }

    
} 