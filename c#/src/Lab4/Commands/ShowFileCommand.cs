using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ShowFileCommand : ICommand
{
    private readonly string _path;

    public string Result { get; private set; } = string.Empty;

    public ShowFileCommand(string path)
    {
        _path = path;
    }

    public void Execute(IFileSystem fileSystem)
    {
        string content = fileSystem.ShowFileContent(_path);
        Result = $"Contents of {_path}:\n{content}";
    }
}
