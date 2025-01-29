using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

public class CommandFactory : ICommandFactory
{
    public ICommand CreateDepositCommand(Account account, decimal amount)
    {
        ArgumentNullException.ThrowIfNull(account);
        if (amount <= 0) throw new ArgumentException("Amount must be greater than zero.", nameof(amount));
        return new DepositCommand(account, amount);
    }

    public ICommand CreateWithdrawCommand(Account account, decimal amount)
    {
        ArgumentNullException.ThrowIfNull(account);
        if (amount <= 0) throw new ArgumentException("Amount must be greater than zero.", nameof(amount));
        return new WithdrawCommand(account, amount);
    }

    public ICommand CreateCheckBalanceCommand(Account account)
    {
        ArgumentNullException.ThrowIfNull(account);
        return new CheckBalanceCommand(account);
    }

    public ICommand CreateCreateAccountCommand(IAccountRepository repository, Account account)
    {
        ArgumentNullException.ThrowIfNull(repository);
        ArgumentNullException.ThrowIfNull(account);
        return new CreateAccountCommand(repository, account);
    }

    public ICommand CreateDeleteAccountCommand(IAccountRepository repository, string accountNumber)
    {
        ArgumentNullException.ThrowIfNull(repository);
        if (string.IsNullOrWhiteSpace(accountNumber)) throw new ArgumentException("Account number cannot be empty.", nameof(accountNumber));
        return new DeleteAccountCommand(repository, accountNumber);
    }

    public ICommand CreateGetOperationHistoryCommand(IAccountRepository repository, string accountNumber)
    {
        ArgumentNullException.ThrowIfNull(repository);
        if (string.IsNullOrWhiteSpace(accountNumber)) throw new ArgumentException("Account number cannot be empty.", nameof(accountNumber));
        return new GetOperationHistoryCommand(repository, accountNumber);
    }
}
