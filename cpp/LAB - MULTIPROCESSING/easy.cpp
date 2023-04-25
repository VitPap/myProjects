#include <fstream>
#include <omp.h>
#include <time.h>
using namespace std;

const int precision = 3;
const double p = 3.14159265;

int radius, N;

double midX, midY;

int pow(int x, int y) {
	if (y == 0)
		return 1;

	int res = pow(x, y >> 1);

	res *= res;

	if (y % 2 != 0)
		res *= x;

	return res;
}

double getRandomPoint(double left, double right) {
	double point;

	point = rand() % int(pow(10, precision));

	point = left + (point / pow(10, precision)) * (right - left);

	return point;
}

bool isPointIn(double x, double y) {
	double distance = (midX - x) * (midX - x) + (midY - y) * (midY - y);

	return distance <= radius * radius;
}

int cnt = 0;


int stringToInt(string str) {
	int res = 0;

	int from = (str[0] == '-');

	for (int i = from; i < str.length(); i++) {
		int c = (str[i] - '0');
		res = res * 10 + c;
	}
	if (str[0] == '-')
		res *= -1;
	return res;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int nThread = stringToInt(argv[1]);
	string inName = argv[2];
	string outName = argv[3];


	ifstream in(inName);
	if (!in.is_open()) {
		printf("Error in opening input file!");
		exit(1);
	}
	in >> radius >> N;
	in.close();


	midX = midY = radius;
	if (nThread > 0) {
		omp_set_num_threads(nThread);
	}
	double Tstart = omp_get_wtime();
#pragma omp parallel for schedule(static) if (nThread != -1) 
	for (int i = 0; i < N; i++) {
		double x = getRandomPoint(0, radius + radius);
		double y = getRandomPoint(0, radius + radius);
		if (isPointIn(x, y)) {
#pragma omp atomic
			cnt++;
		}
	}


	printf("Time (msec): %f", (omp_get_wtime() - Tstart) * 1000);


	double subArea = 2 * radius * 2 * radius;
	double area = double(cnt) / double(N);
	area = subArea * area;


	ofstream out(outName);
	out << area << endl;
	out.close();

	return 0;
}