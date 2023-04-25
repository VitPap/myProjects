
public abstract class Player {
    public int playerNumber;
    public abstract void makeStep(Field field, GetNumber getter);

    public void randomStep(Field field) {
        int k = (int)(Math.random() * (field.countFreeCoins + 1));

        for (int x = 0; x < field.rows && k >= 0; x++) {
            for (int y = 0; y < field.columns && k >= 0; y++) {
                if (field.isClearCoin(x, y)) {
                    if (k == 0) {
                        field.setCoin(x, y, playerNumber);
                    }
                    k--;
                }
            }
        }
    }
}
