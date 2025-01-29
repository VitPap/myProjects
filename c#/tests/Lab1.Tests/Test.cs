using Itmo.ObjectOrientedProgramming.Lab1;
using Itmo.ObjectOrientedProgramming.Lab1.Routes;
using Xunit;

namespace Lab1.Tests;

public class Test
{
    private Train CreateTestTrain()
    {
        return new Train(1000, 1500, 0.1);
    }

    private const double MaxSpeedForRoute = 30.0;
    private const double MaxSpeedForStation = 10.0;

    [Fact]
    public void Scenario1()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new PowerTrack(50, 500),
            new MagneticTrack(100),
        };

        var route = new Route(tracks, MaxSpeedForRoute);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.Success>(result);
    }

    [Fact]
    public void Scenario2()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new PowerTrack(500, 1200),
            new MagneticTrack(100),
        };

        var route = new Route(tracks, MaxSpeedForRoute);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.SpeedLimitReached>(result);
    }

    [Fact]
    public void Scenario3()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new PowerTrack(2498, 500),
            new MagneticTrack(100),
            new Station(50, 2),
            new MagneticTrack(100),
        };

        var route = new Route(tracks, 50);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.Success>(result);
    }

    [Fact]
    public void Scenario4()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new PowerTrack(50, 1200),
            new Station(MaxSpeedForStation, 0),
            new MagneticTrack(50),
        };

        var route = new Route(tracks, MaxSpeedForRoute);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.SpeedLimitReached>(result);
    }

    [Fact]
    public void Scenario5()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new PowerTrack(50, 1200),
            new MagneticTrack(100),
            new Station(30, 0),
            new MagneticTrack(50),
        };

        var route = new Route(tracks, 10);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.SpeedLimitReached>(result);
    }

    [Fact]
    public void Scenario6()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new PowerTrack(50, 1200),
            new MagneticTrack(100),
            new PowerTrack(50, -800),
            new Station(MaxSpeedForStation, 0),
            new MagneticTrack(100),
            new PowerTrack(500, 1200),
            new MagneticTrack(100),
            new PowerTrack(250, -1000),
        };

        var route = new Route(tracks, MaxSpeedForRoute);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.Success>(result);
    }

    [Fact]
    public void Scenario7()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new MagneticTrack(100),
        };

        var route = new Route(tracks, MaxSpeedForRoute);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.Failure>(result);
    }

    [Fact]
    public void Scenario8()
    {
        // Arrange
        Train train = CreateTestTrain();
        var tracks = new List<ITrack>
        {
            new PowerTrack(100, 500),
            new PowerTrack(100, -1000),
        };

        var route = new Route(tracks, MaxSpeedForRoute);

        // Act
        ResultRoute result = route.Traverse(train);

        // Assert
        Assert.IsType<ResultRoute.Failure>(result);
    }
}
