using Itmo.ObjectOrientedProgramming.Lab4.Commands;
using Itmo.ObjectOrientedProgramming.Lab4.Core;
using Itmo.ObjectOrientedProgramming.Lab4.FileSystem;
using Xunit;

namespace Lab4.Tests;

public class Test
{
    [Fact]
    public void CommandParser_ShouldParseConnectCommand()
    {
        // Arrange
        var parser = new CommandParser();

        // Act
        ICommand command = parser.Parse("connect / local");

        // Assert
        Assert.IsType<ConnectCommand>(command);
        var connectCommand = (ConnectCommand)command;
        Assert.NotNull(connectCommand);
    }

    [Fact]
    public void CommandParser_ShouldThrowOnInvalidCommand()
    {
        // Arrange
        var parser = new CommandParser();

        // Act & Assert
        Assert.Throws<ArgumentException>(() => parser.Parse("invalid_command"));
    }

    [Fact]
    public void CommandParser_ShouldThrowOnMissingArguments()
    {
        // Arrange
        var parser = new CommandParser();

        // Act & Assert
        Assert.Throws<ArgumentException>(() => parser.Parse("connect"));
    }

    [Fact]
    public void InMemoryFileSystem_ShouldChangeDirectory()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var subDirectory = new VirtualDirectory("subdir");
        root.AddDirectory(subDirectory);

        // Act
        fileSystem.ChangeDirectory("subdir");

        // Assert
        Assert.Throws<DirectoryNotFoundException>(() => fileSystem.ChangeDirectory("nonexistent"));
    }

    [Fact]
    public void InMemoryFileSystem_ShouldListDirectoriesAndFiles()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        root.AddDirectory(new VirtualDirectory("subdir1"));
        root.AddFile(new VirtualFile("file1.txt"));

        // Act
        var items = fileSystem.ListDirectory("/", 1).ToList();

        // Assert
        Assert.Equal(2, items.Count);

        Assert.Contains(items, i => i.IsDirectory && i.Path == "subdir1");
        Assert.Contains(items, i => !i.IsDirectory && i.Path == "file1.txt");

        Assert.DoesNotContain(items, i => i.IsDirectory && i.Path == "/");
    }

    [Fact]
    public void InMemoryFileSystem_ShouldShowFileContent()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "Hello, World!");
        root.AddFile(file);

        // Act
        string content = fileSystem.ShowFileContent("/file1.txt");

        // Assert
        Assert.Equal("Hello, World!", content);
        Assert.Throws<FileNotFoundException>(() => fileSystem.ShowFileContent("/nonexistent.txt"));
    }

    [Fact]
    public void InMemoryFileSystem_ShouldMoveAndCopyFiles()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "Content");
        root.AddFile(file);
        var subDirectory = new VirtualDirectory("subdir");
        root.AddDirectory(subDirectory);

        // Act
        fileSystem.CopyFile("/file1.txt", "/subdir/copied_file.txt");
        fileSystem.MoveFile("/file1.txt", "/subdir/moved_file.txt");

        // Assert
        VirtualFile? copiedFile = subDirectory.Files.FirstOrDefault(f => f.Name == "copied_file.txt");
        VirtualFile? movedFile = subDirectory.Files.FirstOrDefault(f => f.Name == "moved_file.txt");
        Assert.NotNull(copiedFile);
        Assert.NotNull(movedFile);
        Assert.Equal("Content", copiedFile.Content);
        Assert.Equal("Content", movedFile.Content);
        Assert.Throws<FileNotFoundException>(() => fileSystem.MoveFile("/file1.txt", "/subdir/new_file.txt"));
    }

    [Fact]
    public void InMemoryFileSystem_ShouldRenameFile()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "Content");
        root.AddFile(file);

        // Act
        fileSystem.RenameFile("/file1.txt", "renamed_file.txt");

        // Assert
        Assert.Contains(root.Files, f => f.Name == "renamed_file.txt");
        Assert.DoesNotContain(root.Files, f => f.Name == "file1.txt");
        Assert.Throws<FileNotFoundException>(() => fileSystem.RenameFile("/nonexistent.txt", "new_name.txt"));
    }

    [Fact]
    public void ListDirectoryCommandFactory_ShouldCreateCommandWithDefaultDepth()
    {
        // Arrange
        var factory = new ListDirectoryCommandFactory();

        // Act
        ICommand command = factory.Create(["tree.list"]);

        // Assert
        Assert.IsType<ListDirectoryCommand>(command);
        Assert.Equal(1, ((ListDirectoryCommand)command).Depth);
    }

    [Fact]
    public void ListDirectoryCommandFactory_ShouldCreateCommandWithCustomDepth()
    {
        // Arrange
        var factory = new ListDirectoryCommandFactory();

        // Act
        ICommand command = factory.Create(["tree.list", "-d3"]);

        // Assert
        Assert.IsType<ListDirectoryCommand>(command);
        Assert.Equal(3, ((ListDirectoryCommand)command).Depth);
    }

    [Fact]
    public void InMemoryFileSystem_ShouldDeleteFile()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "Content");
        root.AddFile(file);

        // Act
        fileSystem.DeleteFile("/file1.txt");

        // Assert
        Assert.DoesNotContain(root.Files, f => f.Name == "file1.txt");
        Assert.Throws<FileNotFoundException>(() => fileSystem.DeleteFile("/file1.txt"));
    }

    [Fact]
    public void VisitorContext_ShouldTraverseTreeCorrectly()
    {
        // Arrange
        var root = new VirtualDirectory("root");
        var subdir = new VirtualDirectory("subdir");
        root.AddDirectory(subdir);
        root.AddFile(new VirtualFile("file.txt"));

        // Act
        var visitor = new VisitorContext(2, "DIR", "FILE");
        root.Accept(visitor, 0);
        var output = visitor.GetOutput().ToList();

        // Assert
        Assert.Contains("DIR: root", output);
        Assert.Contains("--DIR: subdir", output);
        Assert.Contains("--FILE: file.txt", output);
    } ////////

    [Fact]
    public void ChangeDirectoryCommand_ShouldExecuteCorrectly()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        var command = new ChangeDirectoryCommand("subdir");
        VirtualDirectory root = fileSystem.Root;
        var subdir = new VirtualDirectory("subdir");
        root.AddDirectory(subdir);

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.Equal("Changed directory to subdir.", command.Result);
    }

    [Fact]
    public void DeleteFileCommand_ShouldExecuteCorrectly()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "Content");
        root.AddFile(file);
        var command = new DeleteFileCommand("/file1.txt");

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.Equal("Deleted file: /file1.txt", command.Result);
        Assert.Throws<FileNotFoundException>(() => fileSystem.ShowFileContent("/file1.txt"));
    }

    [Fact]
    public void ShowFileCommand_ShouldDisplayContent()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "Hello, World!");
        root.AddFile(file);
        var command = new ShowFileCommand("/file1.txt");

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.Equal("Contents of /file1.txt:\nHello, World!", command.Result);
    }

    [Fact]
    public void CopyFileCommand_ShouldCopyFileCorrectly()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "File content");
        root.AddFile(file);
        var command = new CopyFileCommand("/file1.txt", "/copied_file.txt");

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.Contains(root.Files, f => f.Name == "copied_file.txt");
        Assert.Equal("File content", root.Files.First(f => f.Name == "copied_file.txt").Content);
    }

    [Fact]
    public void MoveFileCommand_ShouldMoveFileCorrectly()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "File content");
        root.AddFile(file);
        var subdir = new VirtualDirectory("subdir");
        root.AddDirectory(subdir);
        var command = new MoveFileCommand("/file1.txt", "/subdir/file1.txt");

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.DoesNotContain(root.Files, f => f.Name == "file1.txt");
        Assert.Contains(subdir.Files, f => f.Name == "file1.txt");
    }

    [Fact]
    public void RenameFileCommand_ShouldRenameFileCorrectly()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        VirtualDirectory root = fileSystem.Root;
        var file = new VirtualFile("file1.txt", "Content");
        root.AddFile(file);
        var command = new RenameFileCommand("/file1.txt", "renamed_file.txt");

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.Contains(root.Files, f => f.Name == "renamed_file.txt");
        Assert.DoesNotContain(root.Files, f => f.Name == "file1.txt");
    }

    [Fact]
    public void DisconnectCommand_ShouldDisconnectFileSystem()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        var command = new DisconnectCommand();

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.Equal("Disconnected from the file system.", command.Result);
    }

    [Fact]
    public void ConnectCommand_ShouldConnectToFileSystem()
    {
        // Arrange
        var fileSystem = new InMemoryFileSystem();
        var command = new ConnectCommand("/", "local");

        // Act
        command.Execute(fileSystem);

        // Assert
        Assert.Equal("Connected to / in local mode.", command.Result);
    }

    [Fact]
    public void TreeListCommand_ShouldTraverseAndListCorrectly()
    {
        // Arrange
        var root = new VirtualDirectory("root");
        var subdir = new VirtualDirectory("subdir");
        root.AddDirectory(subdir);
        root.AddFile(new VirtualFile("file.txt"));
        var command = new TreeListCommand(root, 2);

        // Act
        command.Execute(new InMemoryFileSystem());
    }
}
