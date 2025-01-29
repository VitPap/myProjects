using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

public class CreateAccountCommand : ICommand
{
    private readonly IAccountRepository _repository;
    private readonly Account _account;

    public CreateAccountCommand(IAccountRepository repository, Account account)
    {
        _repository = repository ?? throw new ArgumentNullException(nameof(repository));
        _account = account ?? throw new ArgumentNullException(nameof(account));
    }

    public void Execute()
    {
        _repository.CreateAccount(_account);
    }
}
