package md2html;

public class Link extends Element{
    private String link;

    public Link() {
        super("a");
    }

    public void addLink(String link) {
        this.link = link;
    }
    public String toString() {
        return "<a href='" + link + "'>" + answer.toString() + "</a>";
    }
}
