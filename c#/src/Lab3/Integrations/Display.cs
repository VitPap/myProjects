using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Integrations;

public class Display : IRecipient
{
    private readonly DisplayDriver _driver;
    private string _currentMessage;
    private string _currentColor;

    public string Name { get; } = "Дисплей";

    public Display(DisplayDriver driver)
    {
        _driver = driver ?? throw new ArgumentNullException(nameof(driver));
        _currentMessage = string.Empty;
        _currentColor = "White";
    }

    public void SetColor(string color)
    {
        _currentColor = color;
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message);

        Clear();
        _currentMessage = $"{message.Header}: {message.Body}";
        string coloredMessage = _driver.GetColoredText(_currentMessage, _currentColor);
        _driver.WriteToConsole(coloredMessage);
        _driver.WriteToFile(_currentMessage);
    }

    public void ReceiveMessage(IMessage message)
    {
        SendMessage(message);
    }

    private void Clear()
    {
        _currentMessage = string.Empty;
        _driver.Clear();
    }
}