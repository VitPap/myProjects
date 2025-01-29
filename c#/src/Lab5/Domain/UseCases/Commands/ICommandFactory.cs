using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

public interface ICommandFactory
{
    ICommand CreateDepositCommand(Account account, decimal amount);

    ICommand CreateWithdrawCommand(Account account, decimal amount);

    ICommand CreateCheckBalanceCommand(Account account);

    ICommand CreateCreateAccountCommand(IAccountRepository repository, Account account);

    ICommand CreateDeleteAccountCommand(IAccountRepository repository, string accountNumber);

    ICommand CreateGetOperationHistoryCommand(IAccountRepository repository, string accountNumber);
}