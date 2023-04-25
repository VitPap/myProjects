package markup;

import java.util.List;

public class OrderedList extends EmptyList {
    public OrderedList(List<ListItem> list) {
        super(list);
        texBegin = "\\begin{enumerate}";
        texEnd = "\\end{enumerate}";
    }
}
