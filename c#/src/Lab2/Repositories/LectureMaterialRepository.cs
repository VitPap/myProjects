using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Repositories;

public sealed class LectureMaterialRepository : Repository<LectureMaterial>
{
    public static LectureMaterialRepository Instance { get; } = new LectureMaterialRepository();

    private LectureMaterialRepository() { }
}