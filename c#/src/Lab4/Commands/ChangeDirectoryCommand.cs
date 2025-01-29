using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ChangeDirectoryCommand : ICommand
{
    private readonly string _path;

    public string Result { get; private set; } = string.Empty;

    public ChangeDirectoryCommand(string path)
    {
        _path = path;
    }

    public void Execute(IFileSystem fileSystem)
    {
        fileSystem.ChangeDirectory(_path);
        Result = $"Changed directory to {_path}.";
    }
}
