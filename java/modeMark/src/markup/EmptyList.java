package markup;

import java.util.List;

public abstract class EmptyList implements BaseInter {
    List<ListItem> list;
    String texBegin;
    String texEnd;
    public EmptyList(List<ListItem> list) {
        this.list = list;
    }

    public void toTex(StringBuilder stringBuilder) {
        stringBuilder.append(texBegin);
        for (ListItem listItem : list) {
            listItem.toTex(stringBuilder);
        }
        stringBuilder.append(texEnd);
    }

}
