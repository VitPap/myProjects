namespace Itmo.ObjectOrientedProgramming.Lab3.Core;

public interface IRecipient
{
    string Name { get; }

    void SendMessage(IMessage message);

    void ReceiveMessage(IMessage message);
}
