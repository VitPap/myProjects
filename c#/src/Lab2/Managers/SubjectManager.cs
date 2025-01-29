using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Entities.Grading;
using Itmo.ObjectOrientedProgramming.Lab2.Factories;
using Itmo.ObjectOrientedProgramming.Lab2.Repositories;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Managers;

public class SubjectManager
{
    private readonly SubjectFactory _factory;
    private readonly IRepository<Subject> _repository;

    public SubjectManager(SubjectFactory factory, IRepository<Subject> repository)
    {
        _factory = factory;
        _repository = repository;
    }

    public ResultSubject CreateSubject(string name, GradingFormat gradingFormat)
    {
        ResultSubject subjectResult = _factory.Create(name, gradingFormat);
        if (subjectResult is ResultSubject.Success success)
        {
            _repository.Add(success.Subject);
        }

        return subjectResult;
    }

    public Subject GetSubjectById(Guid id)
    {
        return _repository.GetById(id);
    }

    public IEnumerable<Subject> GetAllSubjects()
    {
        return _repository.GetAll();
    }
}