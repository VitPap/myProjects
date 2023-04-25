public class RandomPlayer extends Player{

    public RandomPlayer(int playerNumber) {
        this.playerNumber = playerNumber;
    }

    public void makeStep(Field field, GetNumber getter) {
        randomStep(field);
    }

}
