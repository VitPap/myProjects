namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class User : Entity
{
    public string Name { get; private set; }

    public User(string name)
    {
        if (string.IsNullOrWhiteSpace(name))
        {
            throw new ArgumentException("Пустое имя", nameof(name));
        }

        Id = Guid.NewGuid();
        Name = name;
    }
}