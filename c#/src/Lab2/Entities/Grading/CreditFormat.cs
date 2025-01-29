namespace Itmo.ObjectOrientedProgramming.Lab2.Entities.Grading;

public class CreditFormat : GradingFormat
{
    public int MinimumPoints { get; private set; }

    public CreditFormat(int minimumPoints)
    {
        MinimumPoints = minimumPoints;
    }

    public override int TotalPoints => 100;
}