using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

public class CheckBalanceCommand : ICommand
{
    private readonly Account _account;

    public decimal Result { get; private set; }

    public CheckBalanceCommand(Account account)
    {
        _account = account ?? throw new ArgumentNullException(nameof(account));
    }

    public void Execute()
    {
        Result = _account.GetBalance();
    }
}