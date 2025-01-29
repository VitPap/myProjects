namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ListDirectoryCommandFactory : ICommandFactory
{
    public string CommandName => "tree.list";

    public ICommand Create(string[] args)
    {
        if (args.Length < 1)
        {
            throw new ArgumentException("Usage: tree.list {-d Depth}");
        }

        int depth = args.Length > 1 && args[1].StartsWith("-d")
            ? int.Parse(args[1].Substring(2))
            : 1;

        return new ListDirectoryCommand(depth);
    }
}
