using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ConnectCommand : ICommand
{
    private readonly string _address;
    private readonly string _mode;

    public string Result { get; private set; } = string.Empty;

    public ConnectCommand(string address, string mode)
    {
        _address = address;
        _mode = mode;
    }

    public void Execute(IFileSystem fileSystem)
    {
        fileSystem.Connect(_address, _mode);
        Result = $"Connected to {_address} in {_mode} mode.";
    }
}
