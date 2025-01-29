namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class DisconnectCommandFactory : ICommandFactory
{
    public string CommandName => "disconnect";

    public ICommand Create(string[] args)
    {
        if (args.Length != 1)
        {
            throw new ArgumentException("Usage: disconnect");
        }

        return new DisconnectCommand();
    }
}
