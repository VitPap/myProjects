namespace Itmo.ObjectOrientedProgramming.Lab4.Core;

public interface IVisitor
{
    void Visit(VirtualFile file, int depth);

    void Visit(VirtualDirectory directory, int depth);
}
