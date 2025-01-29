namespace Itmo.ObjectOrientedProgramming.Lab1.Routes;

public class MagneticTrack : ITrack
{
    private double Length { get; }

    public MagneticTrack(double length)
    {
        if (length <= 0)
        {
            throw new ArgumentException("Negative track length");
        }

        Length = length;
    }

    public ResultRoute Traverse(Train train)
    {
        train.ApplyForce(0);

        ResultTrain calculateResult = train.CalculateTimeForDistance(Length);

        return calculateResult is ResultTrain.Success success ? new ResultRoute.Success(success.Time) : (ResultRoute)new ResultRoute.Failure();
    }
}