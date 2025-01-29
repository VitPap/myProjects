using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Integrations;

public class MessengerRecipient : IRecipient
{
    private readonly Messenger _messenger;

    public string Name { get; } = "Мессенджер";

    public MessengerRecipient(Messenger messenger)
    {
        _messenger = messenger ?? throw new ArgumentNullException(nameof(messenger));
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");
        _messenger.Send(message.Header, message.Body);
    }

    public void ReceiveMessage(IMessage message)
    {
        SendMessage(message);
    }
}