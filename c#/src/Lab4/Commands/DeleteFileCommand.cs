using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class DeleteFileCommand : ICommand
{
    private readonly string _path;

    public string Result { get; private set; } = string.Empty;

    public DeleteFileCommand(string path)
    {
        _path = path;
    }

    public void Execute(IFileSystem fileSystem)
    {
        fileSystem.DeleteFile(_path);
        Result = $"Deleted file: {_path}";
    }
}
