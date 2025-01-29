using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab5.Share;

public static class ConfigLoader
{
    public static Collection<KeyValuePair<string, string>> LoadConfig(string filePath)
    {
        var config = new Collection<KeyValuePair<string, string>>();

        foreach (string line in File.ReadAllLines(filePath))
        {
            string[] parts = line.Split('=', 2);
            if (parts.Length == 2)
            {
                config.Add(new KeyValuePair<string, string>(parts[0].Trim(), parts[1].Trim()));
            }
        }

        return config;
    }

    public static string GetConfigValue(Collection<KeyValuePair<string, string>> config, string key)
    {
        foreach (KeyValuePair<string, string> kvp in config)
        {
            if (kvp.Key == key)
            {
                return kvp.Value;
            }
        }

        throw new KeyNotFoundException($"Key '{key}' not found in configuration.");
    }
}