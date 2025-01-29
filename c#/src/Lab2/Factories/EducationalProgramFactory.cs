using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Factories;

public class EducationalProgramFactory
{
    private readonly User _manager;

    public EducationalProgramFactory(User manager)
    {
        _manager = manager;
    }

    public ResultEducationalProgram Create(string name)
    {
        if (string.IsNullOrWhiteSpace(name))
        {
            return new ResultEducationalProgram.ValidationError("Пустое название");
        }

        var eduProgram = new EducationalProgram(name, _manager);
        return new ResultEducationalProgram.Success(eduProgram);
    }
}