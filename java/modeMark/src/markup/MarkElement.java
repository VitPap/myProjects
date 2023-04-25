package markup;

import java.util.List;
public abstract class MarkElement implements MarkInterface {
    List<MarkInterface> list;
    String markRealize;
    String texBegin;
    String texEnd;
    public MarkElement(List<MarkInterface> list) {
        this.list = list;
    }
    public void toMarkdown(StringBuilder stringBuilder) {
        stringBuilder.append(markRealize);

        for (MarkInterface markInterface : list) {
            markInterface.toMarkdown(stringBuilder);
        }
        stringBuilder.append(markRealize);
    }

    public void toTex(StringBuilder stringBuilder) {
        stringBuilder.append(texBegin);
        for (Struct struct : list) {
            struct.toTex(stringBuilder);
        }

        stringBuilder.append(texEnd);
    }
}