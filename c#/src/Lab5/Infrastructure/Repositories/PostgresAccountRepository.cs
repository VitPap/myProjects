using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;
using Npgsql;
using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab5.Infrastructure.Repositories;

public class PostgresAccountRepository : IAccountRepository
{
    private readonly NpgsqlConnection _connection;

    public PostgresAccountRepository(NpgsqlConnection connection)
    {
        _connection = connection;
    }

    public Account GetAccount(string? accountNumber, string? pin)
    {
        var command = new NpgsqlCommand("SELECT * FROM accounts WHERE account_number = @accountNumber AND pin = @pin", _connection);
        command.Parameters.AddWithValue("accountNumber", accountNumber ?? throw new ArgumentNullException(nameof(accountNumber)));
        command.Parameters.AddWithValue("pin", pin ?? throw new ArgumentNullException(nameof(pin)));

        using NpgsqlDataReader reader = command.ExecuteReader();

        return reader.Read()
            ? new Account(
                reader["account_number"].ToString() ?? throw new InvalidOperationException(),
                reader["pin"].ToString() ?? throw new InvalidOperationException(),
                decimal.Parse(reader["balance"].ToString() ?? throw new InvalidOperationException()))
            : throw new Exception("Account not found.");
    }

    public void SaveAccount(Account account)
    {
        var updateCommand = new NpgsqlCommand("UPDATE accounts SET balance = @balance WHERE account_number = @accountNumber", _connection);
        updateCommand.Parameters.AddWithValue("balance", account.GetBalance());
        updateCommand.Parameters.AddWithValue("accountNumber", account.AccountNumber);
        updateCommand.ExecuteNonQuery();

        foreach (string operation in account.GetOperationHistory())
        {
            AddOperation(account.AccountNumber, operation);
        }
    }

    public void CreateAccount(Account account)
    {
        var command = new NpgsqlCommand("INSERT INTO accounts (account_number, pin, balance) VALUES (@accountNumber, @pin, @balance)", _connection);
        command.Parameters.AddWithValue("accountNumber", account.AccountNumber);
        command.Parameters.AddWithValue("pin", account.Pin);
        command.Parameters.AddWithValue("balance", account.GetBalance());
        command.ExecuteNonQuery();
    }

    public ReadOnlyCollection<string>? GetOperationHistory(string accountNumber)
    {
        var command = new NpgsqlCommand(
            "SELECT operation_type, amount, operation_date FROM operations WHERE account_id = " +
            "(SELECT id FROM accounts WHERE account_number = @accountNumber) ORDER BY operation_date DESC",
            _connection);
        command.Parameters.AddWithValue("accountNumber", accountNumber);

        using NpgsqlDataReader reader = command.ExecuteReader();
        var history = new List<string>();

        while (reader.Read())
        {
            string operationType = reader.GetString(0);
            decimal amount = reader.GetDecimal(1);
            DateTime date = reader.GetDateTime(2);
            history.Add($"{date}: {operationType} {amount}");
        }

        return new ReadOnlyCollection<string>(history);
    }

    public void DeleteAccount(string accountNumber)
    {
        using var command = new NpgsqlCommand("DELETE FROM accounts WHERE account_number = @accountNumber", _connection);
        command.Parameters.AddWithValue("accountNumber", accountNumber ?? throw new ArgumentNullException(nameof(accountNumber)));

        int rowsAffected = command.ExecuteNonQuery();
        if (rowsAffected == 0)
        {
            throw new InvalidOperationException("Account not found or already deleted.");
        }
    }

    public void AddOperation(string accountNumber, string operation)
    {
        var accountIdCommand = new NpgsqlCommand("SELECT id FROM accounts WHERE account_number = @accountNumber", _connection);
        accountIdCommand.Parameters.AddWithValue("accountNumber", accountNumber);

        int accountId;
        using (NpgsqlDataReader reader = accountIdCommand.ExecuteReader())
        {
            if (!reader.Read())
                throw new InvalidOperationException($"Account with account number {accountNumber} not found.");
            accountId = reader.GetInt32(0);
        }

        string[] operationParts = operation.Split(':');
        if (operationParts.Length != 2)
            throw new InvalidOperationException($"Invalid operation format: {operation}");

        string operationType = operationParts[0].Trim();
        if (!decimal.TryParse(operationParts[1].Trim(), out decimal amount))
            throw new InvalidOperationException($"Invalid operation amount: {operationParts[1].Trim()}");

        var insertCommand = new NpgsqlCommand(
            "INSERT INTO operations (account_id, operation_type, amount, operation_date) VALUES (@accountId, @operationType, @amount, @operationDate)",
            _connection);
        insertCommand.Parameters.AddWithValue("accountId", accountId);
        insertCommand.Parameters.AddWithValue("operationType", operationType);
        insertCommand.Parameters.AddWithValue("amount", amount);
        insertCommand.Parameters.AddWithValue("operationDate", DateTime.UtcNow);

        insertCommand.ExecuteNonQuery();
    }
}