using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Entities;

public class GroupRecipient : IRecipient
{
    private readonly List<IRecipient> _recipients = new();

    public string Name { get; } = "Групповой адресат";

    public void AddRecipient(IRecipient recipient)
    {
        ArgumentNullException.ThrowIfNull(recipient, "Добавляемый адресат не может быть null.");
        _recipients.Add(recipient);
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");

        foreach (IRecipient recipient in _recipients)
        {
            recipient.SendMessage(message);
        }
    }

    public void ReceiveMessage(IMessage message)
    {
        SendMessage(message);
    }
}