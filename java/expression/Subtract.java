package expression;

public class Subtract extends Operation {
    public Subtract(FullExpression first, FullExpression second) {
        super(first, second);
        operator = '-';
        priority = 0;
        isOrder = true;
    }

    protected int calc(int x, int y) {
        return x - y;
    }

    protected double calc(double x, double y) {
        return x - y;
    }
}
