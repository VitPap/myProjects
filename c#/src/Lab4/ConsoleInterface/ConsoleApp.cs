using Itmo.ObjectOrientedProgramming.Lab4.Commands;
using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.ConsoleInterface;

public class ConsoleApp
{
    private readonly CommandParser _parser;
    private readonly IFileSystem _fileSystem;

    public ConsoleApp(CommandParser parser, IFileSystem fileSystem)
    {
        _parser = parser;
        _fileSystem = fileSystem;
    }

    public void Run()
    {
        Console.WriteLine("Enter 'exit' to quit");
        while (true)
        {
            Console.Write("> ");
            string? input = Console.ReadLine();
            if (input == "exit")
            {
                break;
            }

            try
            {
                if (input != null)
                {
                    ICommand command = _parser.Parse(input);
                    command.Execute(_fileSystem);
                    Console.WriteLine(command.Result);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
        }
    }
}