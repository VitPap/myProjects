namespace Itmo.ObjectOrientedProgramming.Lab4.Core;

public class VirtualFile : IVirtualFileSystemItem
{
    public string Name { get; }

    public string Content { get; private set; }

    public VirtualFile(string name, string content = "")
    {
        Name = name;
        Content = content;
    }

    public void WriteContent(string content) => Content = content;

    public void Accept(IVisitor visitor, int depth)
    {
        visitor.Visit(this, depth);
    }
}