#include "SandPile.h"

void MakeMatrixSize(std::ifstream& input, Matrix& main_matrix) {
    bool first_was = false;
    bool second_was = false;
    int value = 0;
    input.clear();
    input.seekg(0);
    while (input) {
        char symbol = input.get();
        if (symbol == EOF) {
            break;
        }

        if (symbol == '\n' || symbol == '\r') {
            first_was = second_was = false;
            value = 0;
            continue;
        }

        if (isdigit(symbol)) {
            value = (value * 10) + static_cast<int>(symbol - '0');
        } else {
            if (!first_was) {
                if (main_matrix.row_size < value) {
                    main_matrix.row_size = value;
                }
                second_was = false;
                first_was = true;
                value = 0;
            } else if (!second_was) {
                if (main_matrix.column_size < value) {
                    main_matrix.column_size = value;
                }
                second_was = true;
            }
        }
    }
    main_matrix.column_size++;
    main_matrix.row_size++;
    main_matrix.main_matrix = new int* [main_matrix.column_size];

    for (int i = 0; i < main_matrix.column_size; i++) {
        main_matrix.main_matrix[i] = new int[main_matrix.row_size];
        for (int j = 0; j < main_matrix.row_size; j++) {
            main_matrix.main_matrix[i][j] = 0;
        }
    }
}

void FillMatrix(std::ifstream& input, Matrix& main_matrix) {
    input.clear();
    input.seekg(0);
    int pos_x = 0;
    int pos_y = 0;
    bool first_was = false;
    bool second_was = false;
    while (input) {
        char symbol = input.get();
        if (symbol == EOF) {
            break;
        }

        if (symbol == '\n' || symbol == '\r') {
            pos_x = pos_y = 0;
            first_was = second_was = false;
            continue;
        }

        if (isdigit(symbol)) {
            int num = static_cast<int>(symbol - '0');
            if (!first_was) {
                pos_x = (pos_x * 10) + num;
            }
            else if (!second_was) {
                pos_y = (pos_y * 10) + num;
            } else {
                main_matrix.main_matrix[pos_y][pos_x] *= 10;
                main_matrix.main_matrix[pos_y][pos_x] += num;
            }
        } else {
            if (!first_was) {
                first_was = true;
                second_was = false;
            } else if (!second_was) {
                second_was = true;
            }
        }
    }
}

int** Resize(int** matrix, Matrix& main_matrix, int &right, int &down, int &left, int &up) {
    for (int i = 0; i < main_matrix.column_size && right == 0; i++) {
        right = main_matrix.main_matrix[i][main_matrix.row_size - 1] >= 4;
    }

    for (int i = 0; i < main_matrix.row_size && up == 0; i++) {
        up = main_matrix.main_matrix[0][i] >= 4;
    }
    for (int i = 0; i < main_matrix.column_size && left == 0; i++) {
        left = main_matrix.main_matrix[i][0] >= 4;
    }
    for (int i = 0; i < main_matrix.row_size && down == 0; i++) {
        down = main_matrix.main_matrix[main_matrix.column_size - 1][i] >= 4;
    }

    main_matrix.column_size += up + down;
    main_matrix.row_size += left + right;
    
    int** nw_matrix = new int* [main_matrix.column_size];
    for (int16_t i = 0; i < main_matrix.column_size; i++) {
        nw_matrix[i] = new int[main_matrix.row_size];
    }

    for (int16_t i = 0; i < main_matrix.row_size && down; i++) {
        nw_matrix[main_matrix.column_size - 1][i] = 0;
    }

    for (int16_t i = 0; i < main_matrix.column_size && left; i++) {
        nw_matrix[i][0] = 0;
    }

    for (int16_t i = 0; i < main_matrix.row_size && up; i++) {
        nw_matrix[0][i] = 0;
    }

    for (int16_t i = 0; i < main_matrix.column_size && right; i++) {
        nw_matrix[i][main_matrix.row_size - 1] = 0;
    }

    for (int16_t i = up; i < main_matrix.column_size - down; i++) {
        for (int16_t j = left; j < main_matrix.row_size - right; j++) {
            nw_matrix[i][j] = matrix[i - up][j - left];
        }
        delete[] matrix[i - up];
    }
    delete[] matrix;
    return nw_matrix;
}

void Collapse(bool& is_collapsed, Matrix& main_matrix) {
    is_collapsed = false;

    int** nw_matrix = new int* [main_matrix.column_size];
    for (int16_t i = 0; i < main_matrix.column_size; i++) {
        nw_matrix[i] = new int[main_matrix.row_size];
        for (int j = 0; j < main_matrix.row_size; j++) {
            nw_matrix[i][j] = 0;
        }
    }

    int16_t x_cur = main_matrix.row_size;
    int16_t y_cur = main_matrix.column_size;
    int up = 0;
    int right = 0;
    int left = 0;
    int down = 0;

    nw_matrix = Resize(nw_matrix, main_matrix, right, down, left, up);

    for (int16_t i = 0; i < y_cur; i++) {
        for (int16_t j = 0; j < x_cur; j++) {
            if (main_matrix.main_matrix[i][j] >= 4) {
                is_collapsed = true;
                nw_matrix[i + up][j + 1 + left] += main_matrix.main_matrix[i][j] / 4;
                nw_matrix[i + 1 + up][j + left] += main_matrix.main_matrix[i][j] / 4;
                nw_matrix[i + up][j - 1 + left] += main_matrix.main_matrix[i][j] / 4;
                nw_matrix[i - 1 + up][j + left] += main_matrix.main_matrix[i][j] / 4;   
            }
            nw_matrix[i + up][j + left] += main_matrix.main_matrix[i][j] % 4;
        }
        delete[] main_matrix.main_matrix[i];
    }
    delete[] main_matrix.main_matrix;
    main_matrix.main_matrix = nw_matrix;
}

void SandPile(std::ifstream& input, Matrix& main_matrix) {
    MakeMatrixSize(input, main_matrix);
    FillMatrix(input, main_matrix);
    
    int pictures_cnt = 1;
    char* filename = getFileName(pictures_cnt);
    save(filename, main_matrix);
    int cnt_iters = 0;
    bool is_collapsed = false;

    while (cnt_iters < Arguments::max_iter && is_collapsed || cnt_iters == 0) {
        
        Collapse(is_collapsed, main_matrix);
        cnt_iters++;
        
        if (cnt_iters % Arguments::freq == 0) {
            pictures_cnt++;
            filename = getFileName(pictures_cnt);
            save(filename, main_matrix);
        }
    }

    if (cnt_iters % Arguments::freq != 0 && (cnt_iters != 1 || is_collapsed)) {
        pictures_cnt++;
        filename = getFileName(pictures_cnt);
        save(filename, main_matrix);
    }
}