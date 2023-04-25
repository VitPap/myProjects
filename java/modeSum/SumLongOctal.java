public class SumLongOctal {

    public static void main(String args[]) {
        long result = 0;
        
        for (int i = 0; i < args.length; i++) {
            result += calcRow(args[i]);
        }
        System.out.println(result);
    }

    private static long calcRow(String str) {
        long sum = 0;
        int from = -1;

        for (int i = 0; i <= str.length(); i++) {

            if (i != str.length() && !Character.isWhitespace(str.charAt(i)) && from == -1) {
                from = i;
            } else if ((i == str.length() || Character.isWhitespace(str.charAt(i))) && from != -1) {
                sum += parsed(str.substring(from, i));
                
                from = -1;
            } 
        }

        return sum;
    }  

    private static long parsed(String number) {
        if (Character.toLowerCase(number.charAt(number.length() - 1)) == 'o') {
            return Long.parseLong(number.substring(0, number.length() - 1), 8);
        } else {
            return Long.parseLong(number);
        }
    }
} 