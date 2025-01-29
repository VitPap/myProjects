using Itmo.ObjectOrientedProgramming.Lab5.Application;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.Entities;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;
using Moq;
using Xunit;

namespace Lab5.Tests;

public class Test
{
    private readonly Mock<IAccountRepository> _mockRepository;
    private readonly Mock<ICommandFactory> _mockCommandFactory;
    private readonly AtmFacade _atmFacade;

    public Test()
    {
        _mockRepository = new Mock<IAccountRepository>();
        _mockCommandFactory = new Mock<ICommandFactory>();
        _atmFacade = new AtmFacade(_mockRepository.Object, _mockCommandFactory.Object);
    }

    [Fact]
    public void Withdraw_WithSufficientBalance_UpdatesBalance()
    {
        var account = new Account("1234567890", "1234", 1000m);
        var withdrawCommand = new WithdrawCommand(account, 200m);

        _mockRepository.Setup(r => r.GetAccount("1234567890", "1234")).Returns(account);
        _mockCommandFactory.Setup(f => f.CreateWithdrawCommand(account, 200m)).Returns(withdrawCommand);

        _atmFacade.Withdraw("1234567890", "1234", 200m);

        Assert.Equal(800m, account.GetBalance());
        _mockRepository.Verify(r => r.SaveAccount(It.Is<Account>(a => a.GetBalance() == 800m)), Times.Once);
    }

    [Fact]
    public void Withdraw_WithInsufficientBalance_ThrowsException()
    {
        var account = new Account("1234567890", "1234", 100m);
        var withdrawCommand = new WithdrawCommand(account, 200m);

        _mockRepository.Setup(r => r.GetAccount("1234567890", "1234")).Returns(account);
        _mockCommandFactory.Setup(f => f.CreateWithdrawCommand(account, 200m)).Returns(withdrawCommand);

        Assert.Throws<InvalidOperationException>(() => _atmFacade.Withdraw("1234567890", "1234", 200m));
        _mockRepository.Verify(r => r.SaveAccount(It.IsAny<Account>()), Times.Never);
    }

    [Fact]
    public void Deposit_UpdatesBalance()
    {
        var account = new Account("1234567890", "1234", 500m);
        var depositCommand = new DepositCommand(account, 300m);

        _mockRepository.Setup(r => r.GetAccount("1234567890", "1234")).Returns(account);
        _mockCommandFactory.Setup(f => f.CreateDepositCommand(account, 300m)).Returns(depositCommand);

        _atmFacade.Deposit("1234567890", "1234", 300m);

        Assert.Equal(800m, account.GetBalance());
        _mockRepository.Verify(r => r.SaveAccount(It.Is<Account>(a => a.GetBalance() == 800m)), Times.Once);
    }

    [Fact]
    public void CheckBalance_ShouldReturnCorrectBalance()
    {
        var account = new Account("1234567890", "1234", 1500m);
        var checkBalanceCommand = new CheckBalanceCommand(account);

        _mockRepository.Setup(r => r.GetAccount("1234567890", "1234")).Returns(account);
        _mockCommandFactory.Setup(f => f.CreateCheckBalanceCommand(account)).Returns(checkBalanceCommand);

        decimal balance = _atmFacade.CheckBalance("1234567890", "1234");

        Assert.Equal(1500m, balance);
    }
}