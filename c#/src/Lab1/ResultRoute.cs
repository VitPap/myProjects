namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract record ResultRoute
{
    private ResultRoute() { }

    public sealed record Success(double Time) : ResultRoute;

    public sealed record Failure() : ResultRoute;

    public sealed record SpeedLimitReached(double Limit) : ResultRoute;

    public sealed record ForceLimitReached(double Limit) : ResultRoute;
}
