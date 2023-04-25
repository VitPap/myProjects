package markup;
import java.util.List;
public class Emphasis extends MarkElement{
    public Emphasis(List<MarkInterface> list) {
        super(list);
        markRealize = "*";
        texBegin = "\\emph{";
        texEnd = "}";
    }
}