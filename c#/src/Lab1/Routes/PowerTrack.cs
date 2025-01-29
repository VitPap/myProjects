namespace Itmo.ObjectOrientedProgramming.Lab1.Routes;

public class PowerTrack : ITrack
{
    private double Length { get; }

    private double Force { get; }

    public PowerTrack(double length, double force)
    {
        if (length <= 0)
        {
            throw new ArgumentException("Track length must be positive.");
        }

        Length = length;
        Force = force;
    }

    public ResultRoute Traverse(Train train)
    {
        ResultTrain forceResult = train.ApplyForce(Force);

        if (forceResult is ResultTrain.LimitReached limitReached)
        {
            return new ResultRoute.ForceLimitReached(limitReached.Limit);
        }

        ResultTrain calculateResult = train.CalculateTimeForDistance(Length);

        if (calculateResult is ResultTrain.Success success)
        {
            return new ResultRoute.Success(success.Time);
        }

        return new ResultRoute.Failure();
    }
}