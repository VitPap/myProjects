import java.util.InputMismatchException;
import java.util.Scanner;

public class GetNumber {
    private final Scanner scan;

    public GetNumber() {
        scan = new Scanner(System.in);
    }

    public int getNum(){
        int res = -1;

        try {
            res = scan.nextInt();
        } catch (InputMismatchException e) {
            System.err.println("Wrong input format " + e.getMessage());
            scan.close();
        }
        return res;
    }

    public void close() {
        scan.close();
    }
}
