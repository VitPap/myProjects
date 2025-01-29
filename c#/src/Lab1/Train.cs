namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Train
    {
        public double Speed { get; private set; }

        private double Mass { get; }

        private double MaxForce { get; }

        private double Acceleration { get; set; }

        private double Precision { get; }

        public Train(double mass, double maxForce, double precision)
        {
            if (mass <= 0)
            {
                throw new ArgumentException("Mass must be positive.");
            }

            if (maxForce <= 0)
            {
                throw new ArgumentException("Max force must be positive.");
            }

            if (precision <= 0)
            {
                throw new ArgumentException("Precision must be positive.");
            }

            Mass = mass;
            MaxForce = maxForce;
            Precision = precision;
            Speed = 0;
            Acceleration = 0;
        }

        public ResultTrain ApplyForce(double force)
        {
            if (Math.Abs(force) > MaxForce)
            {
                return new ResultTrain.LimitReached(force);
            }

            Acceleration = force / Mass;

            return new ResultTrain.Success(0);
        }

        public ResultTrain CalculateTimeForDistance(double distance)
        {
            double remainingDistance = distance;
            double totalTime = 0;

            while (remainingDistance > 0)
            {
                double newSpeed = Speed + (Acceleration * Precision);
                if (newSpeed < 0)
                {
                    return new ResultTrain.Failure();
                }

                double coveredDistance = newSpeed * Precision;
                remainingDistance -= coveredDistance;
                totalTime += Precision;

                Speed = newSpeed;

                if (Speed == 0 && Acceleration == 0)
                {
                    break;
                }
            }

            if (remainingDistance > 0)
            {
                return new ResultTrain.Failure();
            }

            return new ResultTrain.Success(totalTime);
        }
    }