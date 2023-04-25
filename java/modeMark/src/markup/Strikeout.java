package markup;
import java.util.List;

public class Strikeout extends MarkElement{
    public Strikeout(List<MarkInterface> list) {
        super(list);
        markRealize = "~";
        texBegin = "\\textst{";
        texEnd = "}";
    }
}