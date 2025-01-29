using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

public class DepositCommand : ICommand
{
    private readonly Account _account;
    private readonly decimal _amount;

    public DepositCommand(Account account, decimal amount)
    {
        _account = account;
        _amount = amount;
    }

    public void Execute()
    {
        _account.Deposit(_amount);
    }
}