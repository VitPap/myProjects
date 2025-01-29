namespace Itmo.ObjectOrientedProgramming.Lab3.Core;

public interface ITopic
{
    string Name { get; }

    IList<IRecipient> Recipients { get; }

    void SendMessage(IMessage message);
}
