namespace Itmo.ObjectOrientedProgramming.Lab3.Core;

public interface IMessage
{
    string Header { get; }

    string Body { get; }

    int ImportanceLevel { get; }
}