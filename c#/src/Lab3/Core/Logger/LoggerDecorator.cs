namespace Itmo.ObjectOrientedProgramming.Lab3.Core.Logger;

public class LoggerDecorator : IRecipient
{
    private readonly IRecipient _innerRecipient;
    private readonly ILogger _logger;

    public string Name => _innerRecipient.Name;

    public LoggerDecorator(IRecipient innerRecipient, ILogger logger)
    {
        _innerRecipient = innerRecipient ?? throw new ArgumentNullException(nameof(innerRecipient), "Адресат не может быть null.");
        _logger = logger ?? throw new ArgumentNullException(nameof(logger), "Логгер не может быть null.");
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");
        _logger.Log($"Лог: {message.Header}");
        _innerRecipient.SendMessage(message);
    }

    public void ReceiveMessage(IMessage message)
    {
        SendMessage(message);
    }
}