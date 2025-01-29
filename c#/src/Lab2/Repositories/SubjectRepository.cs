using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Repositories;

public sealed class SubjectRepository : Repository<Subject>
{
    public static SubjectRepository Instance { get; } = new SubjectRepository();

    private SubjectRepository() { }
}