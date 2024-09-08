#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void convert(long double x, long double y, int precision) {
    long double radius, angle;

    radius = sqrt(x * x + y * y);
    angle = atan2l(y, x);

    cout << fixed << setprecision(precision);
    cout << "Polar:" << endl;
    cout << "Radius = " << radius << endl;
    cout << "Angle = " << angle << endl;
}

void read(long double& x, long double& y, int& precision) {
    cout << "Enter (x, y):";
    cin >> x >> y;

    cout << "Enter precision:";
    cin >> precision;
}

int main() {
    long double x, y;
    int precision;

    read(x, y, precision);

    convert(x, y, precision);

    system("pause");
    return 0;
}
