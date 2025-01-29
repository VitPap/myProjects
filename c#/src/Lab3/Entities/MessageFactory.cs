using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Entities;

public class MessageFactory
{
    public IMessage CreateMessage(string header, string body, int importanceLevel)
    {
        return new Message(header, body, importanceLevel);
    }
}