namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public interface ICommandFactory
{
    string CommandName { get; }

    ICommand Create(string[] args);
}
