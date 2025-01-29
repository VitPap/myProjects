using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class RenameFileCommand : ICommand
{
    private readonly string _path;
    private readonly string _newName;

    public string Result { get; private set; } = string.Empty;

    public RenameFileCommand(string path, string newName)
    {
        _path = path;
        _newName = newName;
    }

    public void Execute(IFileSystem fileSystem)
    {
        fileSystem.RenameFile(_path, _newName);
        Result = $"Renamed file {_path} to {_newName}.";
    }
}
