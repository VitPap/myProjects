using Itmo.ObjectOrientedProgramming.Lab4.Core;

namespace Itmo.ObjectOrientedProgramming.Lab4.FileSystem;

public class InMemoryFileSystem : IFileSystem
{
    public VirtualDirectory Root { get; } = new("/");

    private VirtualDirectory _currentDirectory;

    public InMemoryFileSystem()
    {
        _currentDirectory = Root;
    }

    public void Connect(string address, string mode)
    {
        if (mode != "local")
        {
            throw new NotSupportedException("Only local mode is supported.");
        }

        if (address != "/")
        {
            throw new DirectoryNotFoundException($"Directory '{address}' not found.");
        }

        _currentDirectory = Root;
    }

    public void Disconnect()
    {
        _currentDirectory = Root;
    }

    public void ChangeDirectory(string path)
    {
        if (!Path.IsPathRooted(path))
        {
            string[] segments = path.Split('/', StringSplitOptions.RemoveEmptyEntries);
            VirtualDirectory current = _currentDirectory;

            foreach (string segment in segments)
            {
                if (segment == ".")
                {
                    continue;
                }

                if (segment == "..")
                {
                    if (current.Parent != null)
                    {
                        current = current.Parent;
                    }
                    else
                    {
                        throw new InvalidOperationException("Cannot navigate above the root directory.");
                    }
                }
                else
                {
                    VirtualDirectory? next = current.Subdirectories.FirstOrDefault(d => d.Name == segment);
                    if (next == null)
                    {
                        throw new DirectoryNotFoundException($"Directory '{segment}' not found.");
                    }

                    current = next;
                }
            }

            _currentDirectory = current;
        }
        else
        {
            VirtualDirectory? target = GetDirectoryByPath(path);
            if (target == null)
            {
                throw new DirectoryNotFoundException($"Directory '{path}' not found.");
            }

            _currentDirectory = target;
        }
    }

    public IEnumerable<FileSystemItem> ListDirectory(string path, int depth)
    {
        VirtualDirectory? target = GetDirectoryByPath(path);
        if (target == null)
        {
            throw new DirectoryNotFoundException($"Directory '{path}' not found.");
        }

        var result = new List<FileSystemItem>();

        TraverseDirectory(target, depth, 0, result);

        return result;
    }

    public string ShowFileContent(string path)
    {
        VirtualFile? file = GetFileByPath(path);
        if (file == null)
        {
            throw new FileNotFoundException($"File '{path}' not found.");
        }

        return file.Content;
    }

    public void MoveFile(string sourcePath, string destinationPath)
    {
        VirtualFile? file = GetFileByPath(sourcePath);
        if (file == null)
        {
            throw new FileNotFoundException($"File '{sourcePath}' not found.");
        }

        VirtualDirectory? destinationDirectory = GetDirectoryByPath(GetDirectoryName(destinationPath));
        if (destinationDirectory == null)
        {
            throw new DirectoryNotFoundException($"Destination directory '{destinationPath}' not found.");
        }

        if (destinationDirectory.Files.Any(f => f.Name == GetFileName(destinationPath)))
        {
            throw new InvalidOperationException(
                $"A file with the name '{GetFileName(destinationPath)}' already exists in the destination directory.");
        }

        destinationDirectory.AddFile(new VirtualFile(GetFileName(destinationPath), file.Content));
        DeleteFile(sourcePath);
    }

    public void CopyFile(string sourcePath, string destinationPath)
    {
        VirtualFile? file = GetFileByPath(sourcePath);
        if (file == null)
        {
            throw new FileNotFoundException($"File '{sourcePath}' not found.");
        }

        VirtualDirectory? destinationDirectory = GetDirectoryByPath(GetDirectoryName(destinationPath));
        if (destinationDirectory == null)
        {
            throw new DirectoryNotFoundException($"Destination directory '{destinationPath}' not found.");
        }

        if (destinationDirectory.Files.Any(f => f.Name == GetFileName(destinationPath)))
        {
            throw new InvalidOperationException(
                $"A file with the name '{GetFileName(destinationPath)}' already exists in the destination directory.");
        }

        destinationDirectory.AddFile(new VirtualFile(GetFileName(destinationPath), file.Content));
    }

    public void DeleteFile(string path)
    {
        VirtualDirectory? directory = GetDirectoryByPath(GetDirectoryName(path));
        if (directory == null)
        {
            throw new DirectoryNotFoundException($"Directory '{GetDirectoryName(path)}' not found.");
        }

        VirtualFile? file = directory.Files.FirstOrDefault(f => f.Name == GetFileName(path));
        if (file == null)
        {
            throw new FileNotFoundException($"File '{path}' not found.");
        }

        directory.Files.Remove(file);
    }

    public void RenameFile(string path, string newName)
    {
        VirtualFile? file = GetFileByPath(path);
        if (file == null)
        {
            throw new FileNotFoundException($"File '{path}' not found.");
        }

        VirtualDirectory? directory = GetDirectoryByPath(GetDirectoryName(path));

        if (directory == null)
        {
            throw new DirectoryNotFoundException($"Directory '{GetDirectoryName(path)}' not found.");
        }

        if (directory.Files.Any(f => f.Name == newName))
        {
            throw new InvalidOperationException($"A file with the name '{newName}' already exists in the directory.");
        }

        directory.Files.Remove(file);
        directory.AddFile(new VirtualFile(newName, file.Content));
    }

    private static string GetDirectoryName(string path)
    {
        int lastSlashIndex = path.LastIndexOf('/');
        return lastSlashIndex > 0 ? path.Substring(0, lastSlashIndex) : "/";
    }

    private static string GetFileName(string path)
    {
        int lastSlashIndex = path.LastIndexOf('/');
        return path.Substring(lastSlashIndex + 1);
    }

    private static void TraverseDirectory(VirtualDirectory directory, int maxDepth, int currentDepth, List<FileSystemItem> result)
    {
        if (currentDepth > maxDepth)
        {
            return;
        }

        foreach (VirtualDirectory subdirectory in directory.Subdirectories)
        {
            result.Add(new FileSystemItem(subdirectory.Name, true));
            TraverseDirectory(subdirectory, maxDepth, currentDepth + 1, result);
        }

        foreach (VirtualFile file in directory.Files)
        {
            result.Add(new FileSystemItem(file.Name, false));
        }
    }

    private VirtualDirectory? GetDirectoryByPath(string path)
    {
        if (path == "/")
        {
            return Root;
        }

        string[] parts = path.Split('/', StringSplitOptions.RemoveEmptyEntries);
        VirtualDirectory? current = Root;

        foreach (string part in parts)
        {
            current = current.Subdirectories.FirstOrDefault(d => d.Name == part);
            if (current == null)
            {
                return null;
            }
        }

        return current;
    }

    private VirtualFile? GetFileByPath(string path)
    {
        VirtualDirectory? directory = GetDirectoryByPath(GetDirectoryName(path));
        if (directory == null)
        {
            return null;
        }

        return directory.Files.FirstOrDefault(f => f.Name == GetFileName(path));
    }
}
