using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Repositories;

public class Repository<T> : IRepository<T> where T : Entity
{
    private readonly Dictionary<Guid, T> _items = new Dictionary<Guid, T>();

    public void Add(T item)
    {
        if (item == null)
        {
            throw new ArgumentNullException(nameof(item), "Добавление null в репозиторий.");
        }

        _items[item.Id] = item;
    }

    public T GetById(Guid id)
    {
        if (_items.ContainsKey(id))
        {
            T item = _items[id];

            return item;
        }
        else
        {
            throw new Exception($"Нет объекта с ID {id}");
        }
    }

    public IEnumerable<T> GetAll()
    {
        return _items.Values;
    }
}
