using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Entities;

public class Topic : ITopic
{
    public string Name { get; }

    public IList<IRecipient> Recipients { get; }

    public Topic(string name)
    {
        Name = name ?? throw new ArgumentNullException(nameof(name));
        Recipients = [];
    }

    public void AddRecipient(IRecipient recipient)
    {
        ArgumentNullException.ThrowIfNull(recipient, "Добавляемый адресат не может быть null.");
        if (!Recipients.Contains(recipient))
        {
            Recipients.Add(recipient);
        }
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");
        if (Recipients.Count == 0)
        {
            throw new InvalidOperationException("Нет доступных адресатов для отправки сообщения.");
        }

        foreach (IRecipient recipient in Recipients)
        {
            recipient.SendMessage(message);
        }
    }
}