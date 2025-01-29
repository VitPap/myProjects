using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

public class DeleteAccountCommand : ICommand
{
    private readonly IAccountRepository _repository;
    private readonly string _accountNumber;

    public DeleteAccountCommand(IAccountRepository repository, string accountNumber)
    {
        _repository = repository;
        _accountNumber = accountNumber;
    }

    public void Execute()
    {
        _repository.DeleteAccount(_accountNumber);
    }
}