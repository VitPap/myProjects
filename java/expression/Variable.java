package expression;

import java.util.Objects;

public class Variable implements FullExpression {
    private String value;

    public Variable(String value) {
        this.value = value;
    }
    public double evaluate(double x) {
        return x;
    }

    public int evaluate(int x) {
        return x;
    }

    public String toMiniString() {
        return value;
    }

    public String toString() {
        return value;
    }
    public int evaluate(int x, int y, int z) {
        return (value == "x" ? x : (value == "y" ? y : z));
    }

    public boolean equals(Object obj) {
        return ((obj == null || getClass() != obj.getClass() ? false : value == ((Variable) obj).value));
    }
    @Override
    public int hashCode() {
        return Objects.hash(value);
    }
}
