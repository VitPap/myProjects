using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Entities.Grading;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Factories;

public class SubjectFactory : AuthorableEntityFactory<Subject>
{
    public SubjectFactory(User author) : base(author) { }

    public ResultSubject Create(string name, GradingFormat gradingFormat)
    {
        if (string.IsNullOrWhiteSpace(name))
        {
            return new ResultSubject.ValidationError("Название не может быть пустым.");
        }

        var subject = new Subject(name, gradingFormat, Author);
        return new ResultSubject.Success(subject);
    }
}