using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Factories;

public class LabWorkFactory : AuthorableEntityFactory<LabWork>
{
    public LabWorkFactory(User author) : base(author) { }

    public ResultLabWork Create(string title, string description, string evaluationCriteria, int points)
    {
        if (string.IsNullOrWhiteSpace(title))
        {
            return new ResultLabWork.ValidationError("Пустое имя");
        }

        if (string.IsNullOrWhiteSpace(description))
        {
            return new ResultLabWork.ValidationError("Пустое описание");
        }

        if (string.IsNullOrWhiteSpace(evaluationCriteria))
        {
            return new ResultLabWork.ValidationError("Пустой критерий оценивания");
        }

        if (points <= 0)
        {
            return new ResultLabWork.ValidationError("Отрицательное кол-во баллов");
        }

        var labWork = new LabWork(title, description, evaluationCriteria, points, Author);
        return new ResultLabWork.Success(labWork);
    }
}