#include "Bmp.h"

char* getFileName(int64_t pictures_cnt) {
    size_t output_size = std::strlen(Arguments::output);
    size_t name_size = static_cast<int>(ceil(log10(pictures_cnt + 1)));
    char* name = new char[name_size];
    std::to_chars(name, name + name_size + 1, pictures_cnt);
    char* filename = new char[output_size + name_size + 6];

    for (int64_t i = 0; i < name_size + output_size + 1; i++) {
        if (i < output_size) {
            filename[i] = Arguments::output[i];
        } else if (i == output_size) {
            filename[i] = '\\';
        } else {
            filename[i] = name[i - output_size - 1];
        }
    }

    filename[output_size + name_size + 1] = '.';
    filename[output_size + name_size + 2] = 'b';
    filename[output_size + name_size + 3] = 'm';
    filename[output_size + name_size + 4] = 'p';
    filename[output_size + name_size + 5] = '\0';

    delete[] name;
    return filename;
}

#pragma pack(push, 1)

uint8_t color_matrix[20] = {
        0xFF, 0xFF, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0x00,
        0x00, 0xFF, 0xFF, 0x00,
        0x80, 0x00, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00,
};

struct BMP {
    char signature[2]{'B','M'};
    uint32_t size_file;
    uint16_t reserv_1{0};
    uint16_t reserv_2{0};
    uint32_t size_data_offset;
    uint32_t size_header{40};
    uint32_t width;
    uint32_t height;
    uint16_t planes{1};
    uint16_t bit_per_pixel{4};
    uint32_t compression{0};
    uint32_t size_data{0};
    uint32_t colors{16};
};

#pragma pack(pop)

void save(char* filename, Matrix& main_matrix) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Output folder is not found";
        exit(EXIT_FAILURE);
    }

    const int kWidth = main_matrix.row_size;
    const int kHeight = main_matrix.column_size;
    int width_in_byte = ceil(static_cast<double>(kWidth) / 2);
    int padding = (4 - width_in_byte % 4) % 4;

    BMP header;
    header.size_data_offset = 74;
    header.height = kHeight;
    header.width = padding + kWidth;
    header.size_data = (width_in_byte + padding) * kHeight;
    header.size_file = header.size_data_offset + header.size_data;
    
    file.write(reinterpret_cast<char*>(&header), 54);
    file.write(reinterpret_cast<char*>(color_matrix), 20);

    uint8_t* str = new uint8_t[width_in_byte + padding];
    for (int i = kHeight - 1; i >= 0; i--) {
        for (int j = 0; j < width_in_byte + padding; j++) {
            str[j] = 0x00;
        }

        uint8_t pixel = 0x00;
        int cnt = 0;
        for (int j = 0; j < kWidth; j++) {
            if (main_matrix.main_matrix[i][j] == 0) {
                pixel |= 0x00;
            } else if (main_matrix.main_matrix[i][j] == 1) {
                pixel |= 0x01;
            } else if (main_matrix.main_matrix[i][j] == 2) {
                pixel |= 0x02;
            } else if (main_matrix.main_matrix[i][j] == 3) {
                pixel |= 0x03;
            } else {
                pixel |= 0x04;
            }
            
            cnt++;
            if (cnt % 2) {
                pixel <<= 4;
            } else {
                str[cnt / 2 - 1] = pixel;
                pixel = 0x00;
            }
        }

        if (pixel != 0x00) {
            str[(cnt + 2) / 2 - 1] = pixel;
        }

        file.write(reinterpret_cast<char*>(str), padding + width_in_byte);
    }
    delete[] filename;
    delete[] str;
    file.close();
}
