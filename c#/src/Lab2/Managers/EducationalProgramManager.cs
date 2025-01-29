using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Factories;
using Itmo.ObjectOrientedProgramming.Lab2.Repositories;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Managers;

public class EducationalProgramManager
{
    private readonly EducationalProgramFactory _factory;
    private readonly IRepository<EducationalProgram> _repository;

    public EducationalProgramManager(EducationalProgramFactory factory, IRepository<EducationalProgram> repository)
    {
        _factory = factory;
        _repository = repository;
    }

    public ResultEducationalProgram CreateEducationalProgram(string name)
    {
        ResultEducationalProgram eduProgramResult = _factory.Create(name);
        if (eduProgramResult is ResultEducationalProgram.Success success)
        {
            _repository.Add(success.EducationalProgram);
        }

        return eduProgramResult;
    }

    public EducationalProgram GetEducationalProgramById(Guid id)
    {
        return _repository.GetById(id);
    }

    public IEnumerable<EducationalProgram> GetAllEducationalPrograms()
    {
        return _repository.GetAll();
    }
}