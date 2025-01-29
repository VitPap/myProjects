using Crayon;

namespace Itmo.ObjectOrientedProgramming.Lab3.Integrations;

public class DisplayDriver
{
    private readonly string _filePath;

    public DisplayDriver(string filePath)
    {
        _filePath = filePath;
    }

    public void Clear()
    {
        Console.Clear();
    }

    public string GetColoredText(string text, string color)
    {
        return color switch
        {
            "Red" => Output.Red(text),
            "Green" => Output.Green(text),
            "Blue" => Output.Blue(text),
            "Yellow" => Output.Yellow(text),
            _ => text,
        };
    }

    public void WriteToConsole(string text)
    {
        Console.WriteLine(text);
    }

    public void WriteToFile(string text)
    {
        File.AppendAllText(_filePath, text + Environment.NewLine);
    }
}