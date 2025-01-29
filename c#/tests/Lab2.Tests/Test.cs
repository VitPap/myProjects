using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Entities.Grading;
using Itmo.ObjectOrientedProgramming.Lab2.Factories;
using Itmo.ObjectOrientedProgramming.Lab2.Managers;
using Itmo.ObjectOrientedProgramming.Lab2.Repositories;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;
using Xunit;

namespace Lab2.Tests;

public class Test
{
    [Fact]
    public void CreateLabWork_Success()
    {
        // Arrange
        var author = new User("Автор");
        var labWorkRepository = new Repository<LabWork>();
        var labWorkFactory = new LabWorkFactory(author);
        var labWorkManager = new LabWorkManager(labWorkFactory, labWorkRepository);

        // Act
        ResultLabWork labWorkResult = labWorkManager.CreateLabWork("Лаба", "Описание", "Критерии", 20);

        // Assert
        Assert.IsType<ResultLabWork.Success>(labWorkResult);
        Assert.Single(labWorkRepository.GetAll());
    }

    [Fact]
    public void UpdateLabWork_Unauthorized()
    {
        // Arrange
        var author = new User("Автор");
        var nonAuthor = new User("Не автор");
        var labWorkRepository = new Repository<LabWork>();
        var labWorkFactory = new LabWorkFactory(author);
        var labWorkManager = new LabWorkManager(labWorkFactory, labWorkRepository);

        ResultLabWork labWorkResult = labWorkManager.CreateLabWork("Лаба", "Описание", "Критерии", 20);
        LabWork labWork = ((ResultLabWork.Success)labWorkResult).LabWork;

        // Act
        ResultLabWork updateResult = labWork.Update("Новое описание", "Новые критерии", nonAuthor);

        // Assert
        Assert.IsType<ResultLabWork.Unauthorized>(updateResult);
        var unauthorizedResult = (ResultLabWork.Unauthorized)updateResult;
        Assert.Equal("Изменение лабораторной не автором", unauthorizedResult.Message);
    }

    [Fact]
    public void CloneLabWork_Success()
    {
        // Arrange
        var author = new User("Автор");
        var newAuthor = new User("Новый автор");
        var labWorkRepository = new Repository<LabWork>();
        var labWorkFactory = new LabWorkFactory(author);
        var labWorkManager = new LabWorkManager(labWorkFactory, labWorkRepository);

        ResultLabWork labWorkResult = labWorkManager.CreateLabWork("Лаба", "Описание", "Критерии", 20);
        LabWork labWork = ((ResultLabWork.Success)labWorkResult).LabWork;

        // Act
        LabWork clonedLabWork = labWork.Clone(newAuthor);

        labWorkRepository.Add(clonedLabWork);

        LabWork retrievedClonedLabWork = labWorkRepository.GetById(clonedLabWork.Id);

        // Assert
        Assert.NotNull(retrievedClonedLabWork);
        Assert.NotNull(retrievedClonedLabWork.BasedOnLabWorkId);
        Assert.Equal(labWork.Id, retrievedClonedLabWork.BasedOnLabWorkId);
        Assert.Equal(newAuthor, retrievedClonedLabWork.Author);
    }

    [Fact]
    public void CreateSubject_WithInvalidTotalPoints_ShouldFail()
    {
        // Arrange
        var author = new User("Автор");
        var subjectRepository = new Repository<Subject>();
        var subjectFactory = new SubjectFactory(author);
        var subjectManager = new SubjectManager(subjectFactory, subjectRepository);
        var labWorkRepository = new Repository<LabWork>();
        var labWorkFactory = new LabWorkFactory(author);
        var labWorkManager = new LabWorkManager(labWorkFactory, labWorkRepository);
        var gradingFormat = new ExamFormat(70);

        ResultSubject subjectResult = subjectManager.CreateSubject("Неверный предмет", gradingFormat);
        Subject subject = ((ResultSubject.Success)subjectResult).Subject;

        ResultLabWork labWorkResult = labWorkManager.CreateLabWork("Лаба", "Описание", "Критерии", 20);
        LabWork labWork = ((ResultLabWork.Success)labWorkResult).LabWork;

        // Act
        subject.AddLabWork(labWork);
        ResultSubject validateResult = subject.ValidateTotalPoints();

        // Assert
        Assert.IsType<ResultSubject.ValidationError>(validateResult);
    }

    [Fact]
    public void AddSecondLabWork_WithInvalidTotalPoints_ShouldFail()
    {
        // Arrange
        var author = new User("Автор");
        var subjectRepository = new Repository<Subject>();
        var subjectFactory = new SubjectFactory(author);
        var subjectManager = new SubjectManager(subjectFactory, subjectRepository);
        var labWorkRepository = new Repository<LabWork>();
        var labWorkFactory = new LabWorkFactory(author);
        var labWorkManager = new LabWorkManager(labWorkFactory, labWorkRepository);
        var gradingFormat = new ExamFormat(70);

        ResultSubject subjectResult = subjectManager.CreateSubject("Неверный предмет", gradingFormat);
        Subject subject = ((ResultSubject.Success)subjectResult).Subject;

        ResultLabWork labWorkResult1 = labWorkManager.CreateLabWork("Лаба 1", "Описание", "Критерии", 20);
        LabWork labWork1 = ((ResultLabWork.Success)labWorkResult1).LabWork;
        subject.AddLabWork(labWork1);

        ResultLabWork labWorkResult2 = labWorkManager.CreateLabWork("Лаба 2", "Описание 2", "Критерии 2", 30);
        LabWork labWork2 = ((ResultLabWork.Success)labWorkResult2).LabWork;

        // Act
        subject.AddLabWork(labWork2);
        ResultSubject validateResult = subject.ValidateTotalPoints();

        // Assert
        Assert.IsType<ResultSubject.ValidationError>(validateResult);
    }

    [Fact]
    public void ChangeGradingFormat_WithInvalidTotalPoints_ShouldFail()
    {
        // Arrange
        var author = new User("Автор");
        var subjectRepository = new Repository<Subject>();
        var subjectFactory = new SubjectFactory(author);
        var subjectManager = new SubjectManager(subjectFactory, subjectRepository);
        var labWorkRepository = new Repository<LabWork>();
        var labWorkFactory = new LabWorkFactory(author);
        var labWorkManager = new LabWorkManager(labWorkFactory, labWorkRepository);
        var gradingFormat = new ExamFormat(70);

        ResultSubject subjectResult = subjectManager.CreateSubject("Предмет", gradingFormat);
        Subject subject = ((ResultSubject.Success)subjectResult).Subject;

        ResultLabWork labWorkResult1 = labWorkManager.CreateLabWork("Лаба 1", "Описание", "Критерии", 20);
        LabWork labWork1 = ((ResultLabWork.Success)labWorkResult1).LabWork;
        ResultLabWork labWorkResult2 = labWorkManager.CreateLabWork("Лаба 2", "Описание 2", "Критерии 2", 30);
        LabWork labWork2 = ((ResultLabWork.Success)labWorkResult2).LabWork;

        subject.AddLabWork(labWork1);
        subject.AddLabWork(labWork2);

        // Act
        subject.GradingFormat = new ExamFormat(30);
        ResultSubject validateResult = subject.ValidateTotalPoints();

        // Assert
        Assert.IsType<ResultSubject.ValidationError>(validateResult);
    }

    [Fact]
    public void UpdateSubject_Unauthorized()
    {
        // Arrange
        var author = new User("Автор");
        var nonAuthor = new User("Не автор");
        var subjectRepository = new Repository<Subject>();
        var subjectFactory = new SubjectFactory(author);
        var subjectManager = new SubjectManager(subjectFactory, subjectRepository);
        var labWorkRepository = new Repository<LabWork>();
        var labWorkFactory = new LabWorkFactory(author);
        var labWorkManager = new LabWorkManager(labWorkFactory, labWorkRepository);
        var gradingFormat = new ExamFormat(70);

        ResultSubject subjectResult = subjectManager.CreateSubject("Предмет", gradingFormat);
        Subject subject = ((ResultSubject.Success)subjectResult).Subject;

        ResultLabWork labWorkResult1 = labWorkManager.CreateLabWork("Лаба 1", "Описание", "Критерии", 20);
        LabWork labWork1 = ((ResultLabWork.Success)labWorkResult1).LabWork;
        subject.AddLabWork(labWork1);

        // Act
        ResultSubject updateResult = subject.Update("Новое название предмета", nonAuthor);

        // Assert
        Assert.IsType<ResultSubject.Unauthorized>(updateResult);
        Assert.Equal("Предмет изменяет не автор", ((ResultSubject.Unauthorized)updateResult).Message);
    }

    [Fact]
    public void CloneSubject_Success()
    {
        // Arrange
        var author = new User("Автор");
        var newAuthor = new User("Новый автор");
        var subjectRepository = new Repository<Subject>();
        var subjectFactory = new SubjectFactory(author);
        var subjectManager = new SubjectManager(subjectFactory, subjectRepository);
        var gradingFormat = new ExamFormat(70);

        ResultSubject subjectResult = subjectManager.CreateSubject("Предмет", gradingFormat);
        Subject subject = ((ResultSubject.Success)subjectResult).Subject;

        Subject clonedSubject = subject.Clone(newAuthor);

        subjectRepository.Add(clonedSubject);

        // Act
        Subject retrievedClonedSubject = subjectManager.GetSubjectById(clonedSubject.Id);

        // Assert
        Assert.NotNull(retrievedClonedSubject.BasedOnSubjectId);
        Assert.Equal(subject.Id, retrievedClonedSubject.BasedOnSubjectId);
    }
}
