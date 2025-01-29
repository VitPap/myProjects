using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ListDirectoryCommand : ICommand
{
    public int Depth { get; }

    public string Result { get; private set; } = string.Empty;

    public ListDirectoryCommand(int depth)
    {
        Depth = depth;
    }

    public void Execute(IFileSystem fileSystem)
    {
        IEnumerable<FileSystemItem> items = fileSystem.ListDirectory(".", Depth);
        foreach (FileSystemItem item in items)
        {
            string type = item.IsDirectory ? "DIR " : "FILE";
            Result = string.Join(Environment.NewLine, $"{type}: {item.Path}");
        }
    }
}
