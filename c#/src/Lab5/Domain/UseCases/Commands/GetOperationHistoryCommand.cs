using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;

public class GetOperationHistoryCommand : ICommand
{
    private readonly IAccountRepository _repository;
    private readonly string _accountNumber;

    public IReadOnlyList<string> History { get; private set; } = Array.Empty<string>();

    public GetOperationHistoryCommand(IAccountRepository repository, string accountNumber)
    {
        _repository = repository ?? throw new ArgumentNullException(nameof(repository));
        _accountNumber = accountNumber ?? throw new ArgumentNullException(nameof(accountNumber));
    }

    public void Execute()
    {
        History = _repository.GetOperationHistory(_accountNumber) ?? throw new InvalidOperationException("No history available.");
    }
}