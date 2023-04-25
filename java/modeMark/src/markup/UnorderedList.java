package markup;

import java.util.List;

public class UnorderedList extends EmptyList{

    public UnorderedList(List<ListItem> list) {
        super(list);
        texBegin = "\\begin{itemize}";
        texEnd = "\\end{itemize}";
    }
}
