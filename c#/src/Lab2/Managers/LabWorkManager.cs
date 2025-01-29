using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Factories;
using Itmo.ObjectOrientedProgramming.Lab2.Repositories;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Managers;

public class LabWorkManager
{
    private readonly LabWorkFactory _factory;
    private readonly IRepository<LabWork> _repository;

    public LabWorkManager(LabWorkFactory factory, IRepository<LabWork> repository)
    {
        _factory = factory;
        _repository = repository;
    }

    public ResultLabWork CreateLabWork(string title, string description, string evaluationCriteria, int points)
    {
        ResultLabWork labWorkResult = _factory.Create(title, description, evaluationCriteria, points);
        if (labWorkResult is ResultLabWork.Success success)
        {
            _repository.Add(success.LabWork);
        }

        return labWorkResult;
    }

    public LabWork GetLabWorkById(Guid id)
    {
        return _repository.GetById(id);
    }

    public IEnumerable<LabWork> GetAllLabWorks()
    {
        return _repository.GetAll();
    }
}