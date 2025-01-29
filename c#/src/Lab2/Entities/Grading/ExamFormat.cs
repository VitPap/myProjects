namespace Itmo.ObjectOrientedProgramming.Lab2.Entities.Grading;

public class ExamFormat : GradingFormat
{
    private readonly int _examPoints;

    public ExamFormat(int examPoints)
    {
        _examPoints = examPoints;
    }

    public override int TotalPoints => _examPoints;
}