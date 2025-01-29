using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Utilities;

public abstract record ResultLabWork
{
    private ResultLabWork() { }

    public sealed record Success(LabWork LabWork) : ResultLabWork;

    public sealed record Unauthorized(string Message) : ResultLabWork;

    public sealed record NotFound(string Message) : ResultLabWork;

    public sealed record ValidationError(string Message) : ResultLabWork;
}