using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class DisconnectCommand : ICommand
{
    public string Result { get; private set; } = string.Empty;

    public void Execute(IFileSystem fileSystem)
    {
        fileSystem.Disconnect();
        Result = "Disconnected from the file system.";
    }
}
