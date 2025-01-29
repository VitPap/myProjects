using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Factories;

public abstract class AuthorableEntityFactory<T> where T : Entity, IAuthorable
{
    protected User Author { get; }

    protected AuthorableEntityFactory(User author)
    {
        Author = author;
    }
}