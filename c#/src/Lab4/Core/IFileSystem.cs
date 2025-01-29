namespace Itmo.ObjectOrientedProgramming.Lab4.Core;

public interface IFileSystem
{
    void Connect(string address, string mode);

    void Disconnect();

    void ChangeDirectory(string path);

    IEnumerable<FileSystemItem> ListDirectory(string path, int depth);

    string ShowFileContent(string path);

    void MoveFile(string sourcePath, string destinationPath);

    void CopyFile(string sourcePath, string destinationPath);

    void DeleteFile(string path);

    void RenameFile(string path, string newName);
}
