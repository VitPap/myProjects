using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Utilities;

public abstract record ResultLectureMaterial
{
    private ResultLectureMaterial() { }

    public sealed record Success(LectureMaterial LectureMaterial) : ResultLectureMaterial;

    public sealed record Unauthorized(string Message) : ResultLectureMaterial;

    public sealed record NotFound(string Message) : ResultLectureMaterial;

    public sealed record ValidationError(string Message) : ResultLectureMaterial;
}