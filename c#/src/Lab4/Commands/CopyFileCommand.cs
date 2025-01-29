using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class CopyFileCommand : ICommand
{
    private readonly string _sourcePath;
    private readonly string _destinationPath;

    public string Result { get; private set; } = string.Empty;

    public CopyFileCommand(string sourcePath, string destinationPath)
    {
        _sourcePath = sourcePath;
        _destinationPath = destinationPath;
    }

    public void Execute(IFileSystem fileSystem)
    {
        fileSystem.CopyFile(_sourcePath, _destinationPath);
        Result = $"Copied file from {_sourcePath} to {_destinationPath}.";
    }
}
