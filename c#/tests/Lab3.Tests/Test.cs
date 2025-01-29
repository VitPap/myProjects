using Itmo.ObjectOrientedProgramming.Lab3.Core;
using Itmo.ObjectOrientedProgramming.Lab3.Core.Filter;
using Itmo.ObjectOrientedProgramming.Lab3.Core.Logger;
using Itmo.ObjectOrientedProgramming.Lab3.Entities;
using Itmo.ObjectOrientedProgramming.Lab3.Integrations;
using Moq;
using Xunit;

namespace Lab3.Tests;

public class Test
{
    [Fact]
    public void UserReceivesMessage_MessageIsUnreadByDefault()
    {
        var user = new User("Тестовый пользователь");
        var userRecipient = new UserRecipient(user);
        var message = new Message("Заголовок сообщения", "Тело сообщения", 1);

        userRecipient.SendMessage(message);

        Assert.Contains(message, user.Messages);
        Assert.False(user.IsMessageRead(message));
    }

    [Fact]
    public void UserMarksUnreadMessageAsRead_StatusChangesToRead()
    {
        var user = new User("Тестовый пользователь");
        var userRecipient = new UserRecipient(user);
        var message = new Message("Заголовок сообщения", "Тело сообщения", 1);

        userRecipient.SendMessage(message);
        user.MarkMessageAsRead(message);

        Assert.True(user.IsMessageRead(message));
    }

    [Fact]
    public void UserMarksAlreadyReadMessage_ThrowsError()
    {
        var user = new User("Тестовый пользователь");
        var userRecipient = new UserRecipient(user);
        var message = new Message("Заголовок сообщения", "Тело сообщения", 1);

        userRecipient.SendMessage(message);
        user.MarkMessageAsRead(message);

        Assert.Throws<InvalidOperationException>(() => user.MarkMessageAsRead(message));
    }

    [Fact]
    public void FilterBlocksMessagesBelowThreshold()
    {
        var mockRecipient = new Mock<IRecipient>();
        var filter = new FilterDecorator(mockRecipient.Object, 2);
        var importantMessage = new Message("Важное сообщение", "Тело важного сообщения", 3);
        var trivialMessage = new Message("Маловажное сообщение", "Тело маловажного сообщения", 1);

        filter.SendMessage(importantMessage);
        filter.SendMessage(trivialMessage);

        mockRecipient.Verify(r => r.SendMessage(importantMessage), Times.Once);
        mockRecipient.Verify(r => r.SendMessage(trivialMessage), Times.Never);
    }

    [Fact]
    public void LoggerWritesLogWhenMessageReceived()
    {
        var mockLogger = new Mock<ILogger>();
        var mockRecipient = new Mock<IRecipient>();
        var loggerDecorator = new LoggerDecorator(mockRecipient.Object, mockLogger.Object);
        var message = new Message("Заголовок лога", "Тело лога", 2);

        loggerDecorator.SendMessage(message);

        mockLogger.Verify(logger => logger.Log("Лог: Заголовок лога"), Times.Once);
        mockRecipient.Verify(recipient => recipient.SendMessage(message), Times.Once);
    }

    [Fact]
    public void MessengerRecipient_SendMessage_ShouldCallWriteLineWithFormattedMessage()
    {
        var mockOutput = new Mock<IOutput>();
        var messenger = new Messenger(mockOutput.Object);
        var messengerRecipient = new MessengerRecipient(messenger);
        var message = new Message("Заголовок сообщения", "Тело сообщения", 1);

        messengerRecipient.SendMessage(message);

        string expectedMessage = "[Мессенджер] Заголовок сообщения: Тело сообщения";
        mockOutput.Verify(output => output.WriteLine(expectedMessage), Times.Once);
    }

    [Fact]
    public void GroupRecipientWithImportanceFilter_MessageDeliveredOnce()
    {
        var user1 = new User("Пользователь 1");
        var userRecipient1 = new UserRecipient(user1);
        var user2 = new User("Пользователь 2");
        var userRecipient2 = new UserRecipient(user2);
        var filteredUser2 = new FilterDecorator(userRecipient2, 2);

        var group = new GroupRecipient();
        group.AddRecipient(userRecipient1);
        group.AddRecipient(filteredUser2);

        var messageBelowThreshold = new Message("Низкая важность", "Тело сообщения низкой важности", 1);
        var messageAboveThreshold = new Message("Высокая важность", "Тело сообщения высокой важности", 3);

        group.SendMessage(messageBelowThreshold);
        group.SendMessage(messageAboveThreshold);

        Assert.Contains(messageAboveThreshold, user1.Messages);
        Assert.Contains(messageAboveThreshold, user2.Messages);
        Assert.DoesNotContain(messageBelowThreshold, user2.Messages);
    } /////////////

    [Fact]
    public void DisplayRecipient_ClearsMessageBeforeDisplaying()
    {
        var mockDriver = new Mock<DisplayDriver>("testOutput.txt");
        var displayRecipient = new DisplayRecipient(mockDriver.Object);
        var message = new Message("Тест", "Сообщение", 1);

        displayRecipient.SendMessage(message);
    }

    [Fact]
    public void Topic_AddRecipient_RecipientAddedSuccessfully()
    {
        var topic = new Topic("Тестовый топик");
        var mockRecipient = new Mock<IRecipient>();

        topic.AddRecipient(mockRecipient.Object);

        Assert.Contains(mockRecipient.Object, topic.Recipients);
    }

    [Fact]
    public void Topic_SendMessage_MessageDeliveredToAllRecipients()
    {
        var topic = new Topic("Тестовый топик");
        var mockRecipient1 = new Mock<IRecipient>();
        var mockRecipient2 = new Mock<IRecipient>();
        var message = new Message("Заголовок", "Тело", 1);

        topic.AddRecipient(mockRecipient1.Object);
        topic.AddRecipient(mockRecipient2.Object);
        topic.SendMessage(message);

        mockRecipient1.Verify(r => r.SendMessage(message), Times.Once);
        mockRecipient2.Verify(r => r.SendMessage(message), Times.Once);
    }

    [Fact]
    public void MessageFactory_CreatesMessageSuccessfully()
    {
        var factory = new MessageFactory();
        IMessage message = factory.CreateMessage("Заголовок", "Тело", 3);

        Assert.NotNull(message);
        Assert.Equal("Заголовок", message.Header);
        Assert.Equal("Тело", message.Body);
        Assert.Equal(3, message.ImportanceLevel);
    }

    [Fact]
    public void GroupRecipient_AddRecipient_RecipientAddedToGroup()
    {
        var groupRecipient = new GroupRecipient();
        var mockRecipient = new Mock<IRecipient>();

        groupRecipient.AddRecipient(mockRecipient.Object);
    }

    [Fact]
    public void GroupRecipient_SendMessage_MessageDeliveredToAllGroupRecipients()
    {
        var groupRecipient = new GroupRecipient();
        var mockRecipient1 = new Mock<IRecipient>();
        var mockRecipient2 = new Mock<IRecipient>();
        var message = new Message("Заголовок", "Тело", 1);

        groupRecipient.AddRecipient(mockRecipient1.Object);
        groupRecipient.AddRecipient(mockRecipient2.Object);
        groupRecipient.SendMessage(message);

        mockRecipient1.Verify(r => r.SendMessage(message), Times.Once);
        mockRecipient2.Verify(r => r.SendMessage(message), Times.Once);
    }

    [Fact]
    public void DisplayDriver_WritesColoredTextToConsoleAndFile()
    {
        string filePath = "testOutput.txt";
        var driver = new DisplayDriver(filePath);

        string coloredText = driver.GetColoredText("Тестовое сообщение", "Red");

        Assert.Equal("\u001b[31mТестовое сообщение\u001b[0m", coloredText);

        driver.WriteToConsole("Тестовое сообщение");
        driver.WriteToFile("Тестовое сообщение");

        Assert.True(System.IO.File.Exists(filePath));
#pragma warning disable CA1307
        Assert.Contains("Тестовое сообщение", System.IO.File.ReadAllText(filePath));
#pragma warning restore CA1307
    }
}
