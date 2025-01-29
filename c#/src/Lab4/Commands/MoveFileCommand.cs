using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class MoveFileCommand : ICommand
{
    private readonly string _sourcePath;
    private readonly string _destinationPath;

    public string Result { get; private set; } = string.Empty;

    public MoveFileCommand(string sourcePath, string destinationPath)
    {
        _sourcePath = sourcePath;
        _destinationPath = destinationPath;
    }

    public void Execute(IFileSystem fileSystem)
    {
        fileSystem.MoveFile(_sourcePath, _destinationPath);
        Result = $"Moved file from {_sourcePath} to {_destinationPath}.";
    }
}
