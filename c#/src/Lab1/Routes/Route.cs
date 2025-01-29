namespace Itmo.ObjectOrientedProgramming.Lab1.Routes;

public class Route
{
    private readonly List<ITrack> _tracks;
    private readonly double _maxAllowedSpeed;

    public Route(IEnumerable<ITrack> tracks, double maxAllowedSpeed)
    {
        IEnumerable<ITrack> enumerable = tracks.ToList();
        if (tracks == null || !enumerable.Any())
        {
            throw new ArgumentException("Tracks should not be empty.");
        }

        if (maxAllowedSpeed <= 0)
        {
            throw new ArgumentException("Max speed must be positive.");
        }

        _tracks = enumerable.ToList();
        _maxAllowedSpeed = maxAllowedSpeed;
        foreach (ITrack track in _tracks)
        {
            if (track == null)
            {
                throw new ArgumentException("Tracks cannot be null.");
            }
        }
    }

    public ResultRoute Traverse(Train train)
    {
        double totalTime = 0;

        foreach (ITrack track in _tracks)
        {
            ResultRoute result = track.Traverse(train);

            if (result is ResultRoute.Success success)
            {
                totalTime += success.Time;
            }
            else
            {
                return result;
            }
        }

        if (train.Speed > _maxAllowedSpeed)
        {
            return new ResultRoute.SpeedLimitReached(train.Speed);
        }

        return new ResultRoute.Success(totalTime);
    }
}