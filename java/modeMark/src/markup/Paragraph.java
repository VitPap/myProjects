package markup;

import java.util.List;
public class Paragraph implements BaseInter {
    List <MarkInterface> list;
    public Paragraph(List<MarkInterface> list) {
        this.list = list;
    }

    public void toMarkdown(StringBuilder stringBuilder) {
        for (MarkInterface markInterface : list) {
            markInterface.toMarkdown(stringBuilder);
        }
    }

    public void toTex(StringBuilder stringBuilder) {
        for (Struct struct : list) {
            struct.toTex(stringBuilder);
        }
    }
}