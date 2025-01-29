namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ShowFileCommandFactory : ICommandFactory
{
    public string CommandName => "file.show";

    public ICommand Create(string[] args)
    {
        if (args.Length < 2)
        {
            throw new ArgumentException("Usage: file.show [Path]");
        }

        string path = args[1];

        return new ShowFileCommand(path);
    }
}
