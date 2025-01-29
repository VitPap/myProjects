using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

namespace Itmo.ObjectOrientedProgramming.Lab5.Application;

public class AtmFacade
{
    private readonly IAccountRepository _accountRepository;
    private readonly ICommandFactory _commandFactory;

    public AtmFacade(IAccountRepository accountRepository, ICommandFactory commandFactory)
    {
        _accountRepository = accountRepository ?? throw new ArgumentNullException(nameof(accountRepository));
        _commandFactory = commandFactory ?? throw new ArgumentNullException(nameof(commandFactory));
    }

    public void Deposit(string? accountNumber, string? pin, decimal amount)
    {
        if (amount <= 0) throw new ArgumentException("Deposit amount must be greater than zero.");
        ValidateAccountCredentials(accountNumber, pin);

        Domain.Entities.Account account = _accountRepository.GetAccount(accountNumber, pin);
        ICommand command = _commandFactory.CreateDepositCommand(account, amount);
        command.Execute();
        _accountRepository.SaveAccount(account);
    }

    public void Withdraw(string? accountNumber, string? pin, decimal amount)
    {
        if (amount <= 0) throw new ArgumentException("Withdrawal amount must be greater than zero.");
        ValidateAccountCredentials(accountNumber, pin);

        Domain.Entities.Account account = _accountRepository.GetAccount(accountNumber, pin)
                      ?? throw new InvalidOperationException("Account not found.");

        ICommand command = _commandFactory.CreateWithdrawCommand(account, amount)
                      ?? throw new InvalidOperationException("Failed to create withdraw command.");

        command.Execute();
        _accountRepository.SaveAccount(account);
    }

    public decimal CheckBalance(string accountNumber, string pin)
    {
        ValidateAccountCredentials(accountNumber, pin);
        Account account = _accountRepository.GetAccount(accountNumber, pin);
        ICommand command = _commandFactory.CreateCheckBalanceCommand(account);
        command.Execute();
        return ((CheckBalanceCommand)command).Result;
    }

    public void CreateAccount(string accountNumber, string pin, decimal initialBalance)
    {
        if (string.IsNullOrWhiteSpace(accountNumber))
            throw new ArgumentException("Account number cannot be null or empty.");
        if (string.IsNullOrWhiteSpace(pin) || pin.Length != 4 || !int.TryParse(pin, out _))
            throw new ArgumentException("Invalid PIN format.");
        if (initialBalance < 0)
            throw new ArgumentException("Initial balance cannot be negative.");

        var account = new Account(accountNumber, pin, initialBalance);

        ICommand command = _commandFactory.CreateCreateAccountCommand(_accountRepository, account)
                           ?? throw new InvalidOperationException("Command creation failed.");
        command.Execute();
    }

    public void DeleteAccount(string accountNumber)
    {
        ICommand command = _commandFactory.CreateDeleteAccountCommand(_accountRepository, accountNumber);
        command.Execute();
    }

    public IReadOnlyList<string>? GetOperationHistory(string accountNumber, string pin)
    {
        ValidateAccountCredentials(accountNumber, pin);
        ICommand command = _commandFactory.CreateGetOperationHistoryCommand(_accountRepository, accountNumber);
        command.Execute();
        return ((GetOperationHistoryCommand)command).History;
    }

    private void ValidateAccountCredentials(string? accountNumber, string? pin)
    {
        if (string.IsNullOrWhiteSpace(accountNumber)) throw new ArgumentException("Account number cannot be empty.");
        if (string.IsNullOrWhiteSpace(pin) || pin.Length != 4 || !int.TryParse(pin, out _))
            throw new ArgumentException("PIN must be a 4-digit number.");
    }
}