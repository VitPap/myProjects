using Itmo.ObjectOrientedProgramming.Lab3.Core;

namespace Itmo.ObjectOrientedProgramming.Lab3.Entities;

public class Message(string header, string body, int importanceLevel) : IMessage
{
    public string Header { get; } = header;

    public string Body { get; } = body;

    public int ImportanceLevel { get; } = importanceLevel;
}
