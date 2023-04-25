package expression;

public class Multiply extends Operation {
    public Multiply(FullExpression first, FullExpression second) {
        super(first, second);
        operator = '*';
        isOrder = false;
        priority = 1;
    }
    protected int calc(int x, int y) {
        return x * y;
    }

    protected double calc(double x, double y) {
        return x * y;
    }
}
