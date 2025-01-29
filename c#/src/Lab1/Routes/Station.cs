namespace Itmo.ObjectOrientedProgramming.Lab1.Routes;

public class Station : ITrack
{
    private double MaxAllowedSpeed { get; }

    private double UnboardingTime { get; }

    public Station(double maxAllowedSpeed, double unboardingTime)
    {
        if (unboardingTime < 0)
        {
            throw new ArgumentException("Unboarding time cannot be negative.");
        }

        if (maxAllowedSpeed <= 0)
        {
            throw new ArgumentException("Max allowed speed should be positive.");
        }

        MaxAllowedSpeed = maxAllowedSpeed;
        UnboardingTime = unboardingTime;
    }

    public ResultRoute Traverse(Train train)
    {
        if (train.Speed > MaxAllowedSpeed)
        {
            return new ResultRoute.SpeedLimitReached(train.Speed);
        }

        return new ResultRoute.Success(UnboardingTime);
    }
}