package markup;
import java.util.List;

public class Strong extends MarkElement{
    public Strong(List<MarkInterface> list) {
        super(list);
        markRealize = "__";
        texBegin = "\\textbf{";
        texEnd = "}";
    }
}