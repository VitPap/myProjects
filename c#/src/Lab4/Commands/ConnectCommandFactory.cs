namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class ConnectCommandFactory : ICommandFactory
{
    public string CommandName => "connect";

    public ICommand Create(string[] args)
    {
        if (args.Length < 2)
        {
            throw new ArgumentException("Usage: connect [Address] [-m Mode]");
        }

        string address = args[1];
        string mode = args.Length > 2 ? args[2] : "local";
        return new ConnectCommand(address, mode);
    }
}