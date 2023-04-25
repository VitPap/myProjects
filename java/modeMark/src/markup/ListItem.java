package markup;

import java.util.List;

public class ListItem implements Struct{
    List<BaseInter> list;
    public ListItem(List<BaseInter> list) {
        this.list = list;
    }
    public void toTex(StringBuilder stringBuilder) {
        stringBuilder.append("\\item ");
        for (BaseInter baseInter : list) {
            baseInter.toTex(stringBuilder);
        }
    }
}
