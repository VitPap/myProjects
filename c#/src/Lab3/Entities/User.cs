using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Entities;

public class User
{
    public string Name { get; }

    private readonly List<MessageStatus> _messages = new();

    public IReadOnlyCollection<IMessage> Messages => _messages.ConvertAll(ms => ms.Message).AsReadOnly();

    public User(string name)
    {
        Name = name ?? throw new ArgumentNullException(nameof(name));
    }

    public void ReceiveMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");
        if (!_messages.Exists(ms => ms.Message == message))
        {
            _messages.Add(new MessageStatus(message, false));
        }
    }

    public void MarkMessageAsRead(IMessage message)
    {
        MessageStatus messageStatus = _messages.Find(ms => ms.Message == message)
                            ?? throw new InvalidOperationException("Сообщение не найдено.");

        if (messageStatus.IsRead)
        {
            throw new InvalidOperationException("Сообщение уже отмечено как прочитанное.");
        }

        messageStatus.IsRead = true;
    }

    public bool IsMessageRead(IMessage message)
    {
        MessageStatus? messageStatus = _messages.Find(ms => ms.Message == message);
        return messageStatus != null && messageStatus.IsRead;
    }

    private class MessageStatus
    {
        public IMessage Message { get; }

        public bool IsRead { get; set; }

        public MessageStatus(IMessage message, bool isRead)
        {
            Message = message ?? throw new ArgumentNullException(nameof(message));
            IsRead = isRead;
        }
    }
}