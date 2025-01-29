namespace Itmo.ObjectOrientedProgramming.Lab4.Core;

public interface IVirtualFileSystemItem
{
    string Name { get; }

    void Accept(IVisitor visitor, int depth);
}