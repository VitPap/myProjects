using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Repositories;

public sealed class EducationalProgramRepository : Repository<EducationalProgram>
{
    public static EducationalProgramRepository Instance { get; } = new EducationalProgramRepository();

    private EducationalProgramRepository() { }
}