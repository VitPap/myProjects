using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public interface ICommand
{
    void Execute(IFileSystem fileSystem);

    string Result { get; }
}