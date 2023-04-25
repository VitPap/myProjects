
public class PerfectPlayer extends Player{

    public PerfectPlayer(int playerNumber) {
        this.playerNumber = playerNumber;
    }
    public void makeStep(Field field,  GetNumber getter) {
        int findX = -1, findY = -1;

        char[][] fl = field.getField();
        int[][] a = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
        for (int i = 0; i < fl.length && findX == -1; i++) {
            for (int j = 0; j < fl.length && findX == -1; j++) {
                for (int id = 0; id < 8; id++) {
                    int cnt = 0;
                    int posX = i, posY = j;
                    int clearCoinX = -1, clearCoinY = -1;

                    while (posX >= 0 && posX < fl.length && posY >= 0 && posY < fl[i].length && cnt < 4) {

                        if (fl[posX][posY] != fl[i][j]) {
                            if (clearCoinY != -1 || fl[posX][posY] != '.') {
                                break;
                            }

                            clearCoinY = posY;
                            clearCoinX = posX;
                        }

                        cnt++;
                        posX += a[id][0];
                        posY += a[id][1];
                    }

                    if (cnt == 4) {
                        findX = clearCoinX;
                        findY = clearCoinY;
                        break;
                    }
                }
            }
        }

        if (findX != -1) {
            field.setCoin(findX, findY, playerNumber);
        } else {
            for (int needCnt = 3; needCnt >= 0; needCnt--) {
                for (int i = 0; i < fl.length && findX == -1; i++) {
                    for (int j = 0; j < fl.length && findX == -1; j++) {
                        for (int id = 0; id < 8; id++) {
                            int cnt = 0, realCnt = 0;
                            int posX = i, posY = j;
                            int clearCoinX = -1, clearCoinY = -1;

                            while (posX >= 0 && posX < fl.length && posY >= 0 && posY < fl[i].length && cnt < 4) {
                                if (fl[posX][posY] != Character.forDigit(playerNumber, 10)) {
                                    if (fl[posX][posY] != '.') {
                                        break;
                                    }
                                    clearCoinY = posY;
                                    clearCoinX = posX;
                                } else {
                                    realCnt++;
                                }
                                cnt++;
                                posX += a[id][0];
                                posY += a[id][1];
                            }

                            if (cnt == 4 && realCnt == needCnt) {
                                findX = clearCoinX;
                                findY = clearCoinY;
                                break;
                            }
                        }
                    }
                }
            }
            if (findX == -1) {
                randomStep(field);
            } else {
                field.setCoin(findX, findY, playerNumber);
            }
        }
    }


}
