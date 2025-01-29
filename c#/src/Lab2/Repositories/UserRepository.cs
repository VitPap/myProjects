using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Repositories;

public sealed class UserRepository : Repository<User>
{
    public static UserRepository Instance { get; } = new UserRepository();

    private UserRepository() { }
}