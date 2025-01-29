using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class LectureMaterial : Entity, IAuthorable
{
    public User Author { get; private set; }

    public Guid? BasedOnLectureMaterialId { get; private set; }

    public LectureMaterial(string title, string briefDescription, string content, User author)
    {
        if (string.IsNullOrWhiteSpace(title))
        {
            throw new ArgumentException("Пустое имя", nameof(title));
        }

        if (string.IsNullOrWhiteSpace(briefDescription))
        {
            throw new ArgumentException("Пустое краткое описание", nameof(briefDescription));
        }

        if (string.IsNullOrWhiteSpace(content))
        {
            throw new ArgumentException("Пустой контент", nameof(content));
        }

        Id = Guid.NewGuid();
        _title = title;
        _briefDescription = briefDescription;
        _content = content;
        Author = author;
    }

    public ResultLectureMaterial Update(string newBriefDescription, string newContent, User user)
    {
        if (user.Id != Author.Id)
        {
            return new ResultLectureMaterial.Unauthorized("Изменение лекционных материалов не автором");
        }

        _briefDescription = newBriefDescription;
        _content = newContent;

        return new ResultLectureMaterial.Success(this);
    }

    public LectureMaterial Clone(User newAuthor)
    {
        var clone = new LectureMaterial(_title, _briefDescription, _content, newAuthor)
        {
            Id = Guid.NewGuid(),
            BasedOnLectureMaterialId = Id,
        };

        return clone;
    }

    private readonly string _title;

    private string _briefDescription;

    private string _content;
}