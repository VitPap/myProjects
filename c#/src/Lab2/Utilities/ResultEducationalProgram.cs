using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Utilities;

public abstract record ResultEducationalProgram
{
    private ResultEducationalProgram() { }

    public sealed record Success(EducationalProgram EducationalProgram) : ResultEducationalProgram;

    public sealed record ValidationError(string Message) : ResultEducationalProgram;
}