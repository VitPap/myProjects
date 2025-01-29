namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ChangeDirectoryCommandFactory : ICommandFactory
{
    public string CommandName => "tree.goto";

    public ICommand Create(string[] args)
    {
        if (args.Length < 2)
        {
            throw new ArgumentException("Usage: tree.goto [Path]");
        }

        return new ChangeDirectoryCommand(args[1]);
    }
}
