package markup;

public class Text implements MarkInterface {
    public final String text;

    public Text(String text) {
        this.text = text;
    }

    @Override
    public void toMarkdown(StringBuilder stringBuilder) {
        stringBuilder.append(text);
    }
    @Override
    public void toTex(StringBuilder stringBuilder) {
        stringBuilder.append(text);
    }
}