using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Factories;
using Itmo.ObjectOrientedProgramming.Lab2.Repositories;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Managers;

public class LectureMaterialManager
{
    private readonly LectureMaterialFactory _factory;
    private readonly IRepository<LectureMaterial> _repository;

    public LectureMaterialManager(LectureMaterialFactory factory, IRepository<LectureMaterial> repository)
    {
        _factory = factory;
        _repository = repository;
    }

    public ResultLectureMaterial CreateLectureMaterial(string title, string briefDescription, string content)
    {
        ResultLectureMaterial lectureMaterialResult = _factory.Create(title, briefDescription, content);
        if (lectureMaterialResult is ResultLectureMaterial.Success success)
        {
            _repository.Add(success.LectureMaterial);
        }

        return lectureMaterialResult;
    }

    public LectureMaterial GetLectureMaterialById(Guid id)
    {
        return _repository.GetById(id);
    }

    public IEnumerable<LectureMaterial> GetAllLectureMaterials()
    {
        return _repository.GetAll();
    }
}