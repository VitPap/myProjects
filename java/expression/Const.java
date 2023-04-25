package expression;

import java.util.Objects;

public class Const implements FullExpression {
    private final int iValue;
    private final boolean isDouble;
    private final double dValue;

    public Const(double value) {
        dValue = value;
        iValue = (int)value;
        isDouble = true;
    }

    public Const(int value) {
        iValue = value;
        dValue = value;
        isDouble = false;
    }

    public double evaluate(double x) {
        return dValue;
    }

    public int evaluate(int x) {
        return iValue;
    }

    public String toMiniString() {
        return this.toString();
    }

    public int evaluate(int x, int y, int z) {
        return iValue;
    }

    public String toString() {
        return (isDouble ? Double.toString(dValue) : Integer.toString(iValue));
    }

    public boolean equals(Object obj) {
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }

        return (isDouble ? dValue == ((Const) obj).dValue : iValue == ((Const) obj).iValue);
    }

    @Override
    public int hashCode() {
        return (isDouble ? Objects.hashCode(dValue) : Objects.hashCode(iValue));
    }
}
