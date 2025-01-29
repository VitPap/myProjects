namespace Itmo.ObjectOrientedProgramming.Lab3.Core.Filter;

public class FilterDecorator : IRecipient
{
    private readonly IRecipient _innerRecipient;
    private readonly int _importanceThreshold;

    public string Name => _innerRecipient.Name;

    public FilterDecorator(IRecipient innerRecipient, int importanceThreshold)
    {
        _innerRecipient = innerRecipient ?? throw new ArgumentNullException(nameof(innerRecipient), "Адресат не может быть null.");
        if (importanceThreshold < 0)
        {
            throw new ArgumentOutOfRangeException(nameof(importanceThreshold), "Уровень важности должен быть >= 0.");
        }

        _importanceThreshold = importanceThreshold;
    }

    public void SendMessage(IMessage message)
    {
        ArgumentNullException.ThrowIfNull(message, "Сообщение не может быть null.");
        if (message.ImportanceLevel >= _importanceThreshold)
        {
            _innerRecipient.SendMessage(message);
        }
    }

    public void ReceiveMessage(IMessage message)
    {
        SendMessage(message);
    }
}