using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Integrations;

public class Messenger
{
    private readonly IOutput _output;

    public Messenger(IOutput output)
    {
        _output = output ?? throw new ArgumentNullException(nameof(output));
    }

    public void Send(string header, string body)
    {
        ArgumentNullException.ThrowIfNull(header, "Заголовок не может быть null.");
        ArgumentNullException.ThrowIfNull(body, "Тело сообщения не может быть null.");

        string formattedMessage = $"[Мессенджер] {header}: {body}";
        _output.WriteLine(formattedMessage);
    }
}