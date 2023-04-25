package md2html;

import java.util.ArrayList;

public class Paragraph {
    private final ArrayList<Element> list;
    private int hCount;
    private boolean isLastBackSlash;
    private boolean isLastEmpty;
    private boolean isMarkStart;
    private boolean isStrongMarkStart;
    private boolean isStrikeStart;
    private boolean isCodeStart;
    private boolean isLinkStart;
    private boolean isLinkText;
    private int markCount;
    private int strikeCount;
    private String closeStr;
    private Element curElem;
    private Element saveElem;
    private StringBuilder linkText;
    public Paragraph() {
        list = new ArrayList<>();
        curElem = new Text();
    }

    public void closeParag(boolean isExistLine) {
        curElem.add(closeStr);
        if (isExistLine) {
            curElem.add(System.lineSeparator());
        }
        list.add(curElem);
    }
    public void addSeparator() {
        if (isLinkText) {
            linkText.append(System.lineSeparator());
        } else {
            curElem.add(System.lineSeparator());
        }
    }

    public boolean isEmpty() {
        return curElem.isEmpty() && list.isEmpty() && saveElem == null;
    }

    public void add(String line) {
        for (int i = 0; i < line.length(); i++) {
            char ch = line.charAt(i);
            if (this.isEmpty() && ch == '#') {
                hCount++;
            } else {
                if (this.isEmpty() && (hCount == 0 || !isEmpty(ch))) {
                    adding("<p>");
                    closeStr = "</p>";
                }
                if (hCount != 0) {
                    if (!isEmpty(ch)) {
                        while (hCount != 0) {
                            hCount--;
                            adding('#');
                        }
                    } else {
                        adding("<h" + hCount + ">");
                        closeStr = "</h" + hCount + ">";
                        hCount = 0;
                        continue;
                    }
                }
                parse(ch, line, i);
            }
        }
    }

    private void parse(char ch, String line, int i) {
        if (isLinkText) {
            if (ch == ')') {
                isLinkText = false;
                Link link = new Link();
                link.addLink(linkText.toString());
                link.add(curElem.toString());
                curElem = saveElem;
                curElem.add(link.toString());
            }
            if (ch != '(') {
                linkText.append(ch);
            }

            return;
        }

        switch (ch) {
            case ']', '[' -> editLink();
            case '\\' -> editSlash(line, i);
            case '*', '_' -> editMark(ch, line, i);
            case '`' -> editCode();
            case '-' -> editStrike(line, i);
            case '<', '>', '&' -> editSpecial(ch);
            default -> adding(ch);
        }
    }
    private void editLink() {
        if (!isLinkStart) {
            saveElem = curElem;
            curElem = new Text();
        } else {
            isLinkText = true;
            linkText = new StringBuilder();
        }

        isLinkStart = !isLinkStart;
    }
    private void editSlash(String line, int i) {
        if (i + 1 == line.length() || !isMark(line.charAt(i + 1))) {
            adding('\\');
        } else {
            isLastBackSlash = true;
        }
    }
    private void editSpecial(char ch) {
        switch (ch) {
            case '<' -> adding("&lt;");
            case '>' -> adding("&gt;");
            case '&' -> adding("&amp;");
        }
    }
    private void editCode() {
        if (!isCodeStart) {
            curElem.newElem("code");
        } else {
            curElem.closeElem("code");
        }
        isCodeStart = !isCodeStart;
    }
    private void editStrike(String line, int i) {
        strikeCount++;
        strikeCount %= 2;
        if (strikeCount == 0) {
            return;
        }
        if (i + 1 == line.length() || line.charAt(i + 1) != '-') {
            adding('-');
            return;
        }

        if (isStrikeStart) {
            curElem.closeElem("s");
        }  else {
            curElem.newElem("s");
        }
        isStrikeStart = !isStrikeStart;
    }
    private void editMark(char ch, String line, int i) {
        markCount++;
        if (isLastBackSlash) {
            adding(ch);
        } else {
            if (isLastEmpty && (i + 1 == line.length() || isEmpty(line.charAt(i + 1)))) {
                while (markCount != 0) {
                    markCount--;
                    adding(ch);
                }
            } else if (i + 1 == line.length() || ch != line.charAt(i + 1) || !isMark(line.charAt(i + 1))) {
                if (markCount == 2) {
                    if (isStrongMarkStart) {
                        curElem.closeElem("strong");
                    } else {
                        curElem.newElem("strong");
                    }
                    markCount = 0;
                    isStrongMarkStart = !isStrongMarkStart;
                } else {
                    if (isMarkStart) {
                        curElem.closeElem("em");
                    } else {
                        curElem.newElem("em");
                    }
                    markCount = 0;
                    isMarkStart = !isMarkStart;
                }
            }
        }
    }

    private boolean isEmpty(char ch) {
        return Character.isWhitespace(ch);
    }
    private void adding(char ch) {
        curElem.add(ch);
        isLastBackSlash = false;
        isLastEmpty = Character.isWhitespace(ch);
        markCount = 0;
    }
    private void adding(String str) {
        curElem.add(str);
        isLastBackSlash = false;
        isLastEmpty = false;
        markCount = 0;
    }
    private boolean isMark(char ch) {
        return ch == '*' || ch == '_';
    }
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (Element cur : list) {
            str.append(cur.toString());
        }

        return str.toString();
    }
}
