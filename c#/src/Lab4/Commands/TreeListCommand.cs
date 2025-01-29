using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class TreeListCommand : ICommand
{
    private readonly VirtualDirectory _rootDirectory;
    private readonly int _depth;
    private readonly string _directorySymbol;
    private readonly string _fileSymbol;

    public string Result { get; private set; } = string.Empty;

    public TreeListCommand(
        VirtualDirectory rootDirectory,
        int depth = 1,
        string directorySymbol = "DIR",
        string fileSymbol = "FILE")
    {
        _rootDirectory = rootDirectory;
        _depth = depth;
        _directorySymbol = directorySymbol;
        _fileSymbol = fileSymbol;
    }

    public void Execute(IFileSystem fileSystem)
    {
        var visitor = new VisitorContext(_depth, _directorySymbol, _fileSymbol);

        _rootDirectory.Accept(visitor, 0);

        Result = string.Join(Environment.NewLine, visitor.GetOutput());
    }
}