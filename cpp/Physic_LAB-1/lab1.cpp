#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

void convertCartesianToPolar(long double x, long double y, int precision) {
    long double radius = sqrt(x * x + y * y);
    long double angle = atan2l(y, x);

    cout << fixed << setprecision(precision);
    cout << "Полярная система координат:" << endl;
    cout << "Радиус = " << radius << endl;
    cout << "Угол = " << angle << " радиан" << endl;
}

void convertCartesianToCylindrical(long double x, long double y, long double z, int precision) {
    long double radius = sqrt(x * x + y * y);
    long double angle = atan2l(y, x);

    cout << fixed << setprecision(precision);
    cout << "Цилиндрическая система координат:" << endl;
    cout << "Радиус = " << radius << endl;
    cout << "Угол = " << angle << " радиан" << endl;
    cout << "z = " << z << endl;
}

void convertCartesianToSpherical(long double x, long double y, long double z, int precision) {
    long double radius = sqrt(x * x + y * y + z * z);
    long double polarAngle = atan2l(sqrt(x * x + y * y), z);
    long double azimuthalAngle = atan2l(y, x);

    cout << fixed << setprecision(precision);
    cout << "Сферическая система координат:" << endl;
    cout << "Радиус = " << radius << endl;
    cout << "Полярный угол (θ) = " << polarAngle << " радиан" << endl;
    cout << "Азимутальный угол (φ) = " << azimuthalAngle << " радиан" << endl;
}

void readCartesian2D(long double& x, long double& y, int& precision) {
    cout << "Введите (x, y): ";
    while (!(cin >> x >> y)) {
        cout << "Ошибка ввода. Введите корректные значения для x и y: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите точность: ";
    while (!(cin >> precision) || precision < 0) {
        cout << "Ошибка ввода. Точность должна быть неотрицательным числом: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void readCartesian3D(long double& x, long double& y, long double& z, int& precision) {
    cout << "Введите (x, y, z): ";
    while (!(cin >> x >> y >> z)) {
        cout << "Ошибка ввода. Введите корректные значения для x, y и z: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите точность: ";
    while (!(cin >> precision) || precision < 0) {
        cout << "Ошибка ввода. Точность должна быть неотрицательным числом: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void menu() {
    cout << "Выберите преобразование:" << endl;
    cout << "1. Декартовые в Полярные (2D)" << endl;
    cout << "2. Декартовые в Цилиндрические (3D)" << endl;
    cout << "3. Декартовые в Сферические (3D)" << endl;
    cout << "Введите ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    int type, prec;
    long double x, y, z;

    menu();
    while (!(cin >> type) || type < 1 || type > 3) {
        cout << "Неправильный выбор. Пожалуйста, выберите между 1, 2 и 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (type) {
    case 1:
        readCartesian2D(x, y, prec);
        convertCartesianToPolar(x, y, prec);
        break;
    case 2:
        readCartesian3D(x, y, z, prec);
        convertCartesianToCylindrical(x, y, z, prec);
        break;
    case 3:
        readCartesian3D(x, y, z, prec);
        convertCartesianToSpherical(x, y, z, prec);
        break;
    }

    system("pause");
    return 0;
}
