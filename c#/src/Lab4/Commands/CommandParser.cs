namespace Itmo.ObjectOrientedProgramming.Lab4.Commands;

public class CommandParser
{
    private readonly List<ICommandFactory> _factories = new();

    public CommandParser()
    {
        _factories.Add(new ConnectCommandFactory());
        _factories.Add(new DisconnectCommandFactory());
        _factories.Add(new ChangeDirectoryCommandFactory());
        _factories.Add(new ListDirectoryCommandFactory());
        _factories.Add(new ShowFileCommandFactory());
    }

    public ICommand Parse(string input)
    {
        string[] parts = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length == 0)
        {
            throw new ArgumentException("No command provided.");
        }

        ICommandFactory? factory = _factories.FirstOrDefault(f => f.CommandName == parts[0]);
        if (factory == null)
        {
            throw new ArgumentException($"Unknown command: {parts[0]}");
        }

        return factory.Create(parts);
    }
}
