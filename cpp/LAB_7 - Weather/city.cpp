#include <string>

class City {
private:
	const std::string name;
	const double latitude;
	const double longitude;
public:
	City(std::string name, double latitude, double longitude)
		: name(name), longitude(longitude), latitude(latitude)
	{}

	const std::string getName() {
		return name;
	}
	const double getLatitude() {
		return latitude;
	}
	const double getLongitude() {
		return longitude;
	}
};