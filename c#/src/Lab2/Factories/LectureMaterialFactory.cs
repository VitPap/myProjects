using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Factories;

public class LectureMaterialFactory : AuthorableEntityFactory<LectureMaterial>
{
    public LectureMaterialFactory(User author) : base(author) { }

    public ResultLectureMaterial Create(string title, string briefDescription, string content)
    {
        if (string.IsNullOrWhiteSpace(title))
        {
            return new ResultLectureMaterial.ValidationError("Пустое имя");
        }

        if (string.IsNullOrWhiteSpace(briefDescription))
        {
            return new ResultLectureMaterial.ValidationError("Пустое краткое описание");
        }

        if (string.IsNullOrWhiteSpace(content))
        {
            return new ResultLectureMaterial.ValidationError("Пустой контент");
        }

        var lectureMaterial = new LectureMaterial(title, briefDescription, content, Author);
        return new ResultLectureMaterial.Success(lectureMaterial);
    }
}