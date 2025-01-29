using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class LabWork : Entity, IAuthorable
{
    public int Points { get; set; }

    public string Description { get; set; }

    public string EvaluationCriteria { get; set; }

    public User Author { get; private set; }

    public Guid? BasedOnLabWorkId { get; private set; }

    public LabWork(string title, string description, string evaluationCriteria, int points, User author)
    {
        Id = Guid.NewGuid();
        _title = title;
        Description = description;
        EvaluationCriteria = evaluationCriteria;
        Points = points;
        Author = author;
    }

    public ResultLabWork Update(string newDescription, string newEvaluationCriteria, User user)
    {
        if (user.Id != Author.Id)
        {
            return new ResultLabWork.Unauthorized("Изменение лабораторной не автором");
        }

        Description = newDescription;
        EvaluationCriteria = newEvaluationCriteria;

        return new ResultLabWork.Success(this);
    }

    public LabWork Clone(User newAuthor)
    {
        var clone = new LabWork(_title, Description, EvaluationCriteria, Points, newAuthor)
        {
            Id = Guid.NewGuid(),
            BasedOnLabWorkId = this.Id,
        };

        return clone;
    }

    private readonly string _title;
}