using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Entities;

public class UserRecipient : IRecipient
{
    private readonly User _user;

    public string Name => _user.Name;

    public UserRecipient(User user)
    {
        _user = user ?? throw new ArgumentNullException(nameof(user));
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");
        _user.ReceiveMessage(message);
    }

    public void ReceiveMessage(IMessage message)
    {
        SendMessage(message);
    }
}