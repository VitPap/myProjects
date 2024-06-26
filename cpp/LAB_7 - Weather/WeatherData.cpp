#include <string>
#include <vector>

class WeatherVariables {
public:
	const std::string city_name;
	std::string temperature;
	std::string wind_speed;
	std::string precipitation;
	std::string wind_direction;
	std::string weather_type;
	std::string visibility;
	std::string date;
	WeatherVariables() {};
	WeatherVariables(
		std::string city_name,
		std::string temperature,
		std::string wind_speed,
		std::string precipitation,
		std::string wind_direction,
		std::string weather_type,
		std::string visibility,
		std::string date
	) : city_name(city_name),
		temperature(temperature),
		wind_speed(wind_speed),
		precipitation(precipitation),
		wind_direction(wind_direction),
		weather_type(weather_type),
		visibility(visibility),
		date(date)
	{}
	WeatherVariables operator=(const WeatherVariables& variables) {
		this->temperature = variables.temperature;
		this->wind_speed = variables.wind_speed;
		this->precipitation = variables.precipitation;
		this->wind_direction = variables.wind_direction;
		this->weather_type = variables.weather_type;
		this->visibility = variables.visibility;
		this->date = date;
		return *this;
	}
};

class WeatherData {
private:
	std::vector<WeatherVariables> data{};
public:
	WeatherData() {};

	void AddData(const WeatherVariables variables) {
		data.push_back(variables);
	}

	void UpdateData(const int index, const WeatherVariables variables) {
		data[index] = variables;
	}

	WeatherVariables GetWeatherVariables(const int day, const int time) {
		return data[day * 4 + time];
	}

	std::string GetWeatherType(const int day, const int time) {
		return data[day * 4 + time].weather_type;
	}
	std::string GetDayDate(int day) {
		std::string date = data[day * 4].date;
		date.erase(date.end() - 6, date.end());
		return date;
	}
};