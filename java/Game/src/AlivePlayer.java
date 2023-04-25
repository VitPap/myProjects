
public class AlivePlayer extends Player{
    public AlivePlayer(int playerNumber) {
        this.playerNumber = playerNumber;
    }

    public void makeStep(Field field, GetNumber getter) {
        System.out.println("Enter your turn(rowPosition, columnPosition)");
        int posX = getter.getNum() - 1;
        int posY = getter.getNum() - 1;

        if (posX < 0 || posX >= field.rows || posY < 0 || posY >= field.columns) {
            System.out.println("Wrong coordinates");
            makeStep(field, getter);
        } else if (field.isClearCoin(posX, posY)) {
            field.setCoin(posX, posY, playerNumber);
        } else {
            System.out.println("Already filled place");
            makeStep(field, getter);
        }
    }
}
