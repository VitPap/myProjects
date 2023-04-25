package md2html;

import java.util.Objects;

public class Element{
    protected StringBuilder answer;
    private final String type;
    private Element curElem;
    public Element(String type) {
        this.type = type;
        answer = new StringBuilder();
    }

    public void newElem(String type) {
        if (curElem == null) {
            curElem = new Element(type);
        } else {
            curElem.newElem(type);
        }
    }
    public void closeElem(String type) {
        if (Objects.equals(curElem.getType(), type)) {
            answer.append(curElem);
            curElem = null;
        } else {
            curElem.closeElem(type);
        }
    }
    public String toString() {
        return "<" + type + ">" + answer.toString() + "</" + type + ">";
    }

    public void add(char ch) {
        if (curElem == null) {
            answer.append(ch);
        } else {
            curElem.add(ch);
        }
    }

    public void add(String str) {
        if (curElem == null) {
            answer.append(str);
        } else {
            curElem.add(str);
        }
    }

    public String getType() {
        return type;
    }
    public boolean isEmpty() {
        return answer.length() == 0 && curElem == null;
    }
}
