package expression;

public class Divide extends Operation{
    public Divide(FullExpression first, FullExpression second) {
        super(first, second);
        operator = '/';
        priority = 1;
        isOrder = true;
    }

    protected int calc(int x, int y) {
        return x / y;
    }

    protected double calc(double x, double y) {
        return x / y;
    }
}
