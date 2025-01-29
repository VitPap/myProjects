namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract record ResultTrain
{
    private ResultTrain() { }

    public sealed record Success(double Time) : ResultTrain;

    public sealed record Failure() : ResultTrain;

    public sealed record LimitReached(double Limit) : ResultTrain;
}