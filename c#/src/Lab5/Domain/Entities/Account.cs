namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;

public class Account
{
    public string AccountNumber { get; }

    public string Pin { get; }

    private decimal Balance { get; set; }

    private readonly List<string> _operationHistory;

    public Account(string accountNumber, string pin, decimal initialBalance)
    {
        AccountNumber = accountNumber;
        Pin = pin;
        Balance = initialBalance;
        _operationHistory = new List<string>();
    }

    public decimal GetBalance() => Balance;

    public void Deposit(decimal amount)
    {
        Balance += amount;
        Notify($"Deposited: {amount}");
    }

    public void Withdraw(decimal amount)
    {
        if (amount > Balance)
            throw new InvalidOperationException("Insufficient funds.");
        Balance -= amount;
        Notify($"Withdrawn: {amount}");
    }

    public IReadOnlyList<string> GetOperationHistory() => _operationHistory.AsReadOnly();

    private void Notify(string message)
    {
        _operationHistory.Add(message);
    }
}