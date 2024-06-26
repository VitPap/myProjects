#include "number.h"

int2023_t from_int(int32_t i) {
    int2023_t number;
    int current_byte = 0;
    const bool kIs_negative = (i < 0);
    i *= (kIs_negative ? -1 : 1);

    while (i > 0) {
        number.bytes[current_byte++] = i % 256;

        i /= 256;
    }

    if (kIs_negative) {
        converting_negative(number);
    }
    return number;
}

void converting_negative(int2023_t& number) {
    int add_byte = 1;
    for (int i = 0; i < 253; i++) {
        int value = (255 - number.bytes[i]) + add_byte;
        add_byte = 0;
        if (value == 256) {
            value = 0;
            add_byte = 1;
        }
        number.bytes[i] = value;
    }
}

int2023_t from_string(const char* buff) {
    const bool kIs_negative = (buff[0] == '-');
    const int kLen = strlen(buff);
    
    char str[408];
    for (int i = 0; i < kLen; i++) {
        str[i] = buff[i];
    }

    int index = 0, pow = 1;
    int2023_t number;
    bool is_zero = false;
    while (!is_zero) {
        is_zero = true;
        number.bytes[index] += pow * (str[kLen - 1] % 2);

        for (int i = kLen - 1; i >= 0; i--) {
            if (str[i] != '-' && str[i] != '0') {
                is_zero = false;
                if (i + 1 != kLen && str[i] % 2) {
                    str[i + 1] += 5;
                }
                str[i] = static_cast<char>('0' + (str[i] - '0') / 2);
            }
        }

        pow *= 2;
        if (pow == 256) {
            pow = 1;
            index++;
        }
    }

    if (kIs_negative) {
        converting_negative(number);
    }

    return number;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t number;
    uint8_t add_byte = 0;
    for (int i = 0; i < 253; i++) {
        int value = lhs.bytes[i] + rhs.bytes[i] + add_byte;
        add_byte = value / 256;
        number.bytes[i] = value % 256;
    }

    return number;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t number = rhs;
    converting_negative(number);

    return lhs + number;
}

bool isNegative(const int2023_t& number) {
    return number.bytes[252] >= 4;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t left = lhs;
    int2023_t right = rhs;
    int2023_t result;

    const bool kIs_left_negative = isNegative(lhs);
    const bool kIs_right_negative = isNegative(rhs);
    if (kIs_left_negative) {
        converting_negative(left);
    }
    if (kIs_right_negative) {
        converting_negative(right);
    }

    for (int i = 0; i < 253; i++) {
        uint8_t additional = 0;
        for (int j = 0; j < 253; j++) {
            int value = result.bytes[(i + j) % 253] + left.bytes[i] * right.bytes[j] + additional;
            
            result.bytes[(i + j) % 253] = value % 256;
            additional = value / 256;
        }
    }

    if (kIs_left_negative ^ kIs_right_negative) {
        converting_negative(result);
    }

    return result;
}

int lastNotZero(const int2023_t& number) {
    for (int i = 252; i >= 0; i--) {
        if (number.bytes[i] != 0) {
            return i;
        }
    }
    return 0;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t left = lhs;
    int2023_t right = rhs;
    int2023_t result;
    
    const bool kIs_left_negative = isNegative(lhs);
    const bool kIs_right_negative = isNegative(rhs);
    if (kIs_left_negative) {
        converting_negative(left);
    }
    if (kIs_right_negative) {
        converting_negative(right);
    }

    int index_right = lastNotZero(right);
    int index_left = lastNotZero(left);
    int index_result = 252;
    int2023_t sub_number;
    while (right <= left) {
        int coef = left.bytes[index_left] / right.bytes[index_right];
        
        sub_number = from_int(coef) * right;
        bool is_left_greater_sub = true;
        int j = index_left;
        for (int i = lastNotZero(sub_number); i >= 0; i--, j--) {
            if (sub_number.bytes[i] != left.bytes[j]) {
                is_left_greater_sub = left.bytes[j] > sub_number.bytes[i];
                break;
            }
        }

        if (!is_left_greater_sub) {
            coef /= 2;
            sub_number = from_int(coef) * right;
        }

        bool is_was_shift = false;
        if (coef == 0) {
            is_was_shift = true;

            int additional = left.bytes[index_left] * 256 + left.bytes[index_left - 1];
            coef = additional / right.bytes[index_right];
            sub_number = from_int(coef) * right;

            int index_sub = lastNotZero(sub_number);
            is_left_greater_sub = true;
            int j = index_left;
            if (index_sub != index_right) {
                for (int i = index_sub; i >= 0; i--, j--) {
                    if (sub_number.bytes[i] != left.bytes[j]) {
                        is_left_greater_sub = left.bytes[j] > sub_number.bytes[i];
                        break;
                    }
                }
            }

            if (!is_left_greater_sub) {
                coef /= 2;
                sub_number = from_int(coef) * right;
            }
        }

        if (coef == 0) {
            break;
        }

        bool is_sub_byte = false;
        for (int i = index_left - index_right - is_was_shift, j = 0; i <= index_left; i++, j++) {
            int ost = left.bytes[i];
            uint8_t value = sub_number.bytes[j] + is_sub_byte;
            is_sub_byte = false;
            if (value > ost) {
                is_sub_byte = true;
                ost += 256;
            }

            ost -= value;
            left.bytes[i] = ost;
        }
        result.bytes[index_result - is_was_shift] += coef;
        while (index_left >= 0 && left.bytes[index_left] == 0) {
            index_left--;
            index_result--;
        }
    }
    index_result += result.bytes[index_result] == 0;
    for (int i = 0; i < 253; i++) {
        result.bytes[i] = (i + index_result < 253) ? result.bytes[i + index_result] : 0;
    }
    if (kIs_left_negative ^ kIs_right_negative) {
        converting_negative(result);
    }

    return result;
}

bool operator<=(const int2023_t& lhs, const int2023_t& rhs) {
    const bool kIs_left_negative = isNegative(lhs);
    const bool kIs_right_negative = isNegative(rhs);

    if (kIs_left_negative != kIs_right_negative) {
        return kIs_left_negative;
    }

    for (int i = 252; i >= 0; i--) {
        if (lhs.bytes[i] != rhs.bytes[i]) {
            return rhs.bytes[i] > lhs.bytes[i];
        }
    }

    return true;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = 0; i < 253; i++) {
        if (lhs.bytes[i] != rhs.bytes[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    for (int i = 252; i >= 0; i--) {
        stream << value.bytes[i];
    }

    return stream;
}
