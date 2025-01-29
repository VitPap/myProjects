using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Repositories;

public sealed class LabWorkRepository : Repository<LabWork>
{
    public static LabWorkRepository Instance { get; } = new LabWorkRepository();

    private LabWorkRepository() { }
}