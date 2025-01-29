using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;
using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;

public interface IAccountRepository
{
    Account GetAccount(string? accountNumber, string? pin);

    void SaveAccount(Account account);

    void CreateAccount(Account account);

    void DeleteAccount(string accountNumber);

    ReadOnlyCollection<string>? GetOperationHistory(string accountNumber);
}