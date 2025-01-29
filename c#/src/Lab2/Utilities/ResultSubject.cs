using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Utilities;

public abstract record ResultSubject
{
    private ResultSubject() { }

    public sealed record Success(Subject Subject) : ResultSubject;

    public sealed record Unauthorized(string Message) : ResultSubject;

    public sealed record NotFound(string Message) : ResultSubject;

    public sealed record ValidationError(string Message) : ResultSubject;
}