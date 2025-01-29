using Itmo.ObjectOrientedProgramming.Lab5.Domain.Ports;
using Itmo.ObjectOrientedProgramming.Lab5.Domain.UseCases.Commands;
using Itmo.ObjectOrientedProgramming.Lab5.Infrastructure.Database;
using Itmo.ObjectOrientedProgramming.Lab5.Infrastructure.Repositories;
using Itmo.ObjectOrientedProgramming.Lab5.Share;
using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab5.Application;

public class Program
{
    public static void Main()
    {
        try
        {
            Collection<KeyValuePair<string, string>> config = ConfigLoader.LoadConfig("dbconfig.txt");

            string host = ConfigLoader.GetConfigValue(config, "Host");
            string port = ConfigLoader.GetConfigValue(config, "Port");
            string database = ConfigLoader.GetConfigValue(config, "Database");
            string username = ConfigLoader.GetConfigValue(config, "Username");
            string password = ConfigLoader.GetConfigValue(config, "Password");
            string adminPassword = ConfigLoader.GetConfigValue(config, "AdminPassword");

            string connectionString = $"Host={host};Port={port};Database={database};Username={username};Password={password}";

            Npgsql.NpgsqlConnection dbConnection;
            try
            {
                var databaseConnection = DatabaseConnection.GetInstance(connectionString);
                if (databaseConnection == null)
                {
                    throw new InvalidOperationException("Failed to initialize the database connection instance.");
                }

                dbConnection = databaseConnection.Connection;
                if (dbConnection == null)
                {
                    throw new InvalidOperationException("Failed connection.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error initializing database connection: {ex.Message}");
                throw;
            }

            IAccountRepository accountRepository = new PostgresAccountRepository(dbConnection);
            var commandFactory = new CommandFactory();
            var atm = new AtmFacade(accountRepository, commandFactory);

            Console.WriteLine("Welcome to the ATM!");

            while (true)
            {
                Console.WriteLine("Select mode:");
                Console.WriteLine("1. User Mode");
                Console.WriteLine("2. Admin Mode");
                Console.WriteLine("3. Exit");

                string? mode = Console.ReadLine()?.Trim();

                switch (mode)
                {
                    case "1":
                        UserMode(atm);
                        break;

                    case "2":
                        AdminMode(adminPassword, accountRepository);
                        break;

                    case "3":
                        return;

                    default:
                        Console.WriteLine("Invalid mode. Try again.");
                        break;
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Critical error: {ex.Message}");
        }
    }

    public static void UserMode(AtmFacade atm)
    {
        while (true)
        {
            Console.WriteLine("1. Check Balance");
            Console.WriteLine("2. Deposit");
            Console.WriteLine("3. Withdraw");
            Console.WriteLine("4. View Operation History");
            Console.WriteLine("5. Exit to Main Menu");

            string? choice = Console.ReadLine()?.Trim();

            try
            {
                switch (choice)
                {
                    case "1":
                        string accountNumber = GetValidInput("Enter account number:");
                        string pin = GetValidInput("Enter PIN:");

                        decimal balance = atm.CheckBalance(accountNumber, pin);
                        Console.WriteLine($"Your balance: {balance}");
                        break;

                    case "2":
                        accountNumber = GetValidInput("Enter account number:");
                        pin = GetValidInput("Enter PIN:");
                        decimal depositAmount = GetValidDecimal("Enter deposit amount:");

                        atm.Deposit(accountNumber, pin, depositAmount);
                        Console.WriteLine("Deposit successful.");
                        break;

                    case "3":
                        accountNumber = GetValidInput("Enter account number:");
                        pin = GetValidInput("Enter PIN:");
                        decimal withdrawAmount = GetValidDecimal("Enter withdrawal amount:");

                        atm.Withdraw(accountNumber, pin, withdrawAmount);
                        Console.WriteLine("Withdrawal successful.");
                        break;

                    case "4":
                        accountNumber = GetValidInput("Enter account number:");
                        pin = GetValidInput("Enter PIN:");

                        IReadOnlyList<string>? history = atm.GetOperationHistory(accountNumber, pin);

                        if (history == null)
                        {
                            throw new InvalidOperationException("Error: Unable to retrieve operation history.");
                        }
                        else if (history.Count == 0)
                        {
                            Console.WriteLine("No operation history available.");
                        }
                        else
                        {
                            Console.WriteLine("Operation History:");
                            foreach (string record in history)
                            {
                                Console.WriteLine(record);
                            }
                        }

                        break;

                    case "5":
                        return;

                    default:
                        Console.WriteLine("Invalid choice. Please select a valid option.");
                        break;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
        }
    }

    public static void AdminMode(string adminPassword, IAccountRepository accountRepository)
    {
        try
        {
            string inputPassword = GetValidInput("Enter admin password:");
            if (inputPassword != adminPassword)
            {
                Console.WriteLine("Invalid password. Exiting admin mode.");
                return;
            }

            Console.WriteLine("Welcome to Admin Mode!");

            while (true)
            {
                Console.WriteLine("1. Create Account");
                Console.WriteLine("2. Delete Account");
                Console.WriteLine("3. Exit to Main Menu");

                string? choice = Console.ReadLine()?.Trim();

                try
                {
                    switch (choice)
                    {
                        case "1":
                            string newAccountNumber = GetValidInput("Enter new account number:");
                            string newPin = GetValidInput("Enter new PIN:");
                            decimal initialBalance = GetValidDecimal("Enter initial balance:");

                            accountRepository.CreateAccount(new Domain.Entities.Account(newAccountNumber, newPin, initialBalance));
                            Console.WriteLine("Account created successfully.");
                            break;

                        case "2":
                            try
                            {
                                string accountNumberToDelete = GetValidInput("Enter account number to delete:");
                                accountRepository.DeleteAccount(accountNumberToDelete);
                                Console.WriteLine($"Account {accountNumberToDelete} deleted successfully.");
                            }
                            catch (InvalidOperationException ex)
                            {
                                Console.WriteLine($"Error: {ex.Message}");
                            }
                            catch (Exception ex)
                            {
                                Console.WriteLine($"Unexpected error: {ex.Message}");
                            }

                            break;

                        case "3":
                            return;

                        default:
                            Console.WriteLine("Invalid choice. Please select a valid option.");
                            break;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }

    private static string GetValidInput(string prompt)
    {
        Console.WriteLine(prompt);
        string? input = Console.ReadLine()?.Trim();
        if (string.IsNullOrWhiteSpace(input))
            throw new ArgumentException("Input cannot be empty. Please try again.");
        return input;
    }

    private static decimal GetValidDecimal(string prompt)
    {
        Console.WriteLine(prompt);
        if (!decimal.TryParse(Console.ReadLine()?.Trim(), out decimal result) || result < 0)
            throw new ArgumentException("Invalid amount. Please enter a valid non-negative number.");
        return result;
    }
}
