public class Field {
    public int rows, columns;
    public int countFreeCoins;
    private int turnRow, turnCol;
    private final char[][] field;
    public Field(int rows, int columns) {
        this.rows = rows;
        this.columns = columns;
        turnCol = turnRow = -1;
        field = new char[rows][columns];
        countFreeCoins = rows * columns;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                field[i][j] = '.';
            }
        }
    }

    public char[][] getField() {
        return field;
    }
    public void printField() {
        System.out.println("Current field");
        for (int i = 0; i < rows + 2; i++) {
            System.out.print("_");
        }
        System.out.println();
        for (int i = 0; i < rows; i++) {
            System.out.print("|");
            for (int j = 0; j < columns; j++) {
                System.out.print(field[i][j]);
            }
            System.out.print("|");
            System.out.println();
        }

        for (int i = 0; i < rows + 2; i++) {
            System.out.print("-");
        }
        System.out.println();
    }

    public boolean isEnd() {
        if (turnCol == -1 || turnRow == -1) {
            return  false;
        }


        int[][] a = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, 1}, {1, -1}, {-1, -1}, {1, 1}};

        for (int id = 0; id < 8; id++) {
            int cnt = 0;
            int posX = turnRow, posY = turnCol;

            while (posX >= 0 && posX < rows && posY >= 0 && posY < columns &&
                    cnt < 4 && field[posX][posY] == field[turnRow][turnCol]) {

                cnt++;
                posX += a[id][0];
                posY += a[id][1];
            }

            if (cnt == 4) {
                return true;
            }
        }

        return countFreeCoins == 0;
    }

    public void setCoin(int posX, int posY, int playerId) {
        turnRow = posX;
        turnCol = posY;
        field[turnRow][turnCol] = (char)(playerId + '0');
        countFreeCoins--;
    }

    public boolean isClearCoin(int posX, int posY) {
        return field[posX][posY] == '.';
    }

    public char getWinner() {
        return field[turnRow][turnCol];
    }
}
