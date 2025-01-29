using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Factories;

public interface IEntityFactory<out T> where T : Entity
{
    T Create(params object[] args);
}