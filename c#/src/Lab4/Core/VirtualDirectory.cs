using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab4.Core;

public class VirtualDirectory : IVirtualFileSystemItem
{
    public string Name { get; }

    public VirtualDirectory? Parent { get; private set; }

    public Collection<VirtualDirectory> Subdirectories { get; } = new Collection<VirtualDirectory>();

    public Collection<VirtualFile> Files { get; } = new Collection<VirtualFile>();

    public VirtualDirectory(string name, VirtualDirectory? parent = null)
    {
        Name = name;
        Parent = parent;
    }

    public void AddFile(VirtualFile file)
    {
        if (Files.Any(f => f.Name == file.Name))
        {
            throw new InvalidOperationException($"A file with the name '{file.Name}' already exists in the directory '{Name}'.");
        }

        Files.Add(file);
    }

    public void AddDirectory(VirtualDirectory directory)
    {
        if (Subdirectories.Any(d => d.Name == directory.Name))
        {
            throw new InvalidOperationException($"A directory with the name '{directory.Name}' already exists in the directory '{Name}'.");
        }

        directory.Parent = this;
        Subdirectories.Add(directory);
    }

    public void Accept(IVisitor visitor, int depth)
    {
        visitor.Visit(this, depth);
    }
}