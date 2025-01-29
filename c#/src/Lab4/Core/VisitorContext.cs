using System.Text;

namespace Itmo.ObjectOrientedProgramming.Lab4.Core;

public class VisitorContext : IVisitor
{
    private readonly StringBuilder _output = new();
    private readonly int _maxDepth;
    private readonly string _directorySymbol;
    private readonly string _fileSymbol;

    public VisitorContext(int maxDepth, string directorySymbol = "DIR", string fileSymbol = "FILE")
    {
        _maxDepth = maxDepth;
        _directorySymbol = directorySymbol;
        _fileSymbol = fileSymbol;
    }

    public IEnumerable<string> GetOutput() =>
        _output.ToString().Split(Environment.NewLine, StringSplitOptions.RemoveEmptyEntries);

    public void Visit(VirtualFile file, int depth)
    {
        _output.AppendLine($"{new string('-', depth * 2)}{_fileSymbol}: {file.Name}");
    }

    public void Visit(VirtualDirectory directory, int depth)
    {
        _output.AppendLine($"{new string('-', depth * 2)}{_directorySymbol}: {directory.Name}");

        if (depth >= _maxDepth)
        {
            return;
        }

        foreach (VirtualDirectory subdirectory in directory.Subdirectories)
        {
            subdirectory.Accept(this, depth + 1);
        }

        foreach (VirtualFile file in directory.Files)
        {
            file.Accept(this, depth + 1);
        }
    }
}