package expression;

import java.util.Objects;

abstract class Operation implements FullExpression{
    private final FullExpression first;
    private final FullExpression second;
    protected char operator;
    protected boolean isOrder;
    protected int priority;

    public Operation(FullExpression first, FullExpression second) {
        this.first = first;
        this.second = second;
    }

    protected abstract int calc(int x, int y);
    protected abstract double calc(double x, double y);
    @Override
    public double evaluate(double x) {
        return calc(first.evaluate(x), second.evaluate(x));
    }
    @Override
    public int evaluate(int x) {
        return calc(first.evaluate(x), second.evaluate(x));
    }
    @Override
    public int evaluate(int x, int y, int z) {
        return calc(first.evaluate(x, y, z), second.evaluate(x, y, z));
    }

    @Override
    public String toString() {
        return "(" + first.toString() + " " + operator + " " + second.toString() + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null || obj.getClass() != getClass()) {
            return false;
        }
        Operation current = (Operation) obj;

        return first.equals(current.first) && second.equals(current.second);
    }

    @Override
    public String toMiniString() {
        return makeSingleOperation(first, true) + " " + operator + " " + makeSingleOperation(second, false);
    }

    private String makeSingleOperation(FullExpression obj, boolean isFirst) {
        String res = obj.toMiniString();

        if (obj instanceof Operation) {
            Operation oper = (Operation) obj;

            if (!isFirst) {
                if (oper.priority == 0) {
                    res = (operator == '+' ? res : "(" + res + ")");
                } else {
                    if (!oper.isOrder) {
                        res = (operator == '/' ? "(" + res + ")" : res);
                    } else {
                        res = (priority == 1 ? "(" + res + ")" : res);
                    }
                }
            } else {
                if (oper.priority == 0) {
                    res = (priority == 0 ? res : "(" + res + ")");
                }
            }
        }

        return res;
    }

    @Override
    public int hashCode() {
        return Objects.hash(toString());
    }
}
