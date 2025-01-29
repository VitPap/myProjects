using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class EducationalProgram : Entity
{
    public string Name { get; private set; }

    public User Manager { get; private set; }

    public EducationalProgram(string name, User manager)
    {
        Id = Guid.NewGuid();
        Name = name;
        Manager = manager;
        _subjectsBySemester = new Dictionary<int, List<Subject>>();
    }

    public ResultEducationalProgram AddSubject(int semester, Subject subject)
    {
        if (semester <= 0 || semester > 12)
        {
            return new ResultEducationalProgram.ValidationError("Номер семестра должен быть в диапазоне от 1 до 12");
        }

        if (!_subjectsBySemester.ContainsKey(semester))
        {
            _subjectsBySemester[semester] = new List<Subject>();
        }

        _subjectsBySemester[semester].Add(subject);

        return new ResultEducationalProgram.Success(this);
    }

    private readonly Dictionary<int, List<Subject>> _subjectsBySemester;
}