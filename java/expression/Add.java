package expression;

public class Add extends Operation {
    public Add(FullExpression first, FullExpression second) {
        super(first, second);
        operator = '+';
        priority = 0;
        isOrder = false;
    }

    protected int calc(int x, int y) {
        return x + y;
    }

    protected double calc(double x, double y) {
        return x + y;
    }
}
