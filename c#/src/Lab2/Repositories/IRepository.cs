using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Repositories;

public interface IRepository<T> where T : Entity
{
    void Add(T item);

    T GetById(Guid id);

    IEnumerable<T> GetAll();
}