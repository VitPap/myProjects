import java.util.ArrayList;

public class Main {
    public static void main(String args[]) {
        GetNumber getter = new GetNumber();

        int rows = 0, columns = 0;

        while (rows <= 0 || columns <= 0) {
            System.out.println("Enter size of field(rows,columns):");
            rows = getter.getNum();
            columns = getter.getNum();

            if (rows <= 0 || columns <= 0) {
                System.out.println("Wrong size of field");
            }
        }

        Field field = new Field(rows, columns);

        int playerNumber = 0;
        while (playerNumber <= 0) {
            System.out.println("Enter number of players:");
            playerNumber = getter.getNum();

            if (playerNumber <= 0) {
                System.out.println("Wrong number of players");
            }
        }

        ArrayList<Player> players = new ArrayList<>();

        for (int i = 1; i <= playerNumber; i++) {
            System.out.println("Enter type of player #" + i + "(1 - random, 2 - perfect, 3 - alive)");
            int playerType = getter.getNum();

            if (playerType < 1 || playerType > 3) {
                System.out.println("Wrong type of player!");
                i--;
                continue;
            }

            if (playerType == 1) {
                players.add(new RandomPlayer(i));
            } else if (playerType == 3) {
                players.add(new AlivePlayer(i));
            } else {
                players.add(new PerfectPlayer(i));
            }
        }
        field.printField();

        int playerTurn = 0;

        while (!field.isEnd()) {
            System.out.println("Turn of player " + players.get(playerTurn).playerNumber);
            players.get(playerTurn).makeStep(field, getter);
            field.printField();
            playerTurn = (playerTurn + 1) % players.size();
        }

        if (field.countFreeCoins == 0) {
            System.out.println("It`s just DRAW");
        } else {
            System.out.println("Player " + field.getWinner() + " wins this game!");
        }

        getter.close();
    }
}