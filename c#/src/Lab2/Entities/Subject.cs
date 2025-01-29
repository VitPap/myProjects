using Itmo.ObjectOrientedProgramming.Lab2.Entities.Grading;
using Itmo.ObjectOrientedProgramming.Lab2.Utilities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class Subject : Entity, IAuthorable
{
        public User Author { get; private set; }

        public string Name { get; set; }

        public GradingFormat GradingFormat { get; set; }

        public Guid? BasedOnSubjectId { get; private set; }

        public Subject(string name, GradingFormat gradingFormat, User author)
        {
            if (string.IsNullOrWhiteSpace(name))
            {
                throw new ArgumentException("Пустое название", nameof(name));
            }

            Id = Guid.NewGuid();
            Name = name;
            GradingFormat = gradingFormat ?? throw new ArgumentException("null grading format");
            Author = author;
            LabWorks = new List<LabWork>();
            _lectureMaterials = new List<LectureMaterial>();
        }

        public ResultSubject AddLabWork(LabWork labWork)
        {
            LabWorks.Add(labWork);
            return new ResultSubject.Success(this);
        }

        public ResultSubject AddLectureMaterial(LectureMaterial lectureMaterial)
        {
            _lectureMaterials.Add(lectureMaterial);
            return new ResultSubject.Success(this);
        }

        public ResultSubject Update(string newName, User user)
        {
            if (user.Id != Author.Id)
            {
                return new ResultSubject.Unauthorized("Предмет изменяет не автор");
            }

            Name = newName;
            return new ResultSubject.Success(this);
        }

        public Subject Clone(User newAuthor)
        {
            var clone = new Subject(Name, GradingFormat, newAuthor)
            {
                Id = Guid.NewGuid(),
                BasedOnSubjectId = this.Id,
            };

            clone.LabWorks = new List<LabWork>(LabWorks);
            clone._lectureMaterials = new List<LectureMaterial>(_lectureMaterials);

            return clone;
        }

        public ResultSubject ValidateTotalPoints()
        {
            int totalLabPoints = LabWorks.Sum(lw => lw.Points);
            int totalPoints = totalLabPoints + GradingFormat.TotalPoints;

            if (totalPoints != 100)
            {
                return new ResultSubject.ValidationError($"Суммарное количество баллов не равняется 100. Текущее количество: {totalPoints}");
            }

            return new ResultSubject.Success(this);
        }

        internal List<LabWork> LabWorks { get; set; }

        private List<LectureMaterial> _lectureMaterials;
}