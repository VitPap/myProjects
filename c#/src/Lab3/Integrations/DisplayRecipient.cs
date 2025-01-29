using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Integrations;

public class DisplayRecipient : IRecipient
{
    private readonly DisplayDriver _driver;
    private readonly string _currentColor;

    public string Name { get; } = "Дисплей";

    public DisplayRecipient(DisplayDriver driver)
    {
        _driver = driver ?? throw new ArgumentNullException(nameof(driver));
        _currentColor = "White";
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");
        string formattedMessage = $"{message.Header}: {message.Body}";
        string coloredMessage = _driver.GetColoredText(formattedMessage, _currentColor);
        _driver.WriteToConsole(coloredMessage);
        _driver.WriteToFile(formattedMessage);
    }

    public void ReceiveMessage(IMessage message)
    {
        SendMessage(message);
    }
}