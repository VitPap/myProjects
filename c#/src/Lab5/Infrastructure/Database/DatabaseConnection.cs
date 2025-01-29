using Npgsql;

namespace Itmo.ObjectOrientedProgramming.Lab5.Infrastructure.Database;

public class DatabaseConnection
{
    private static DatabaseConnection? _instance;

    public NpgsqlConnection Connection { get; }

    private DatabaseConnection(string connectionString)
    {
        Connection = new NpgsqlConnection(connectionString);
        Connection.Open();
    }

    public static DatabaseConnection? GetInstance(string connectionString)
    {
        _instance ??= new DatabaseConnection(connectionString);

        return _instance;
    }
}