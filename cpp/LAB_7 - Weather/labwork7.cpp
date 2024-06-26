#include "labwork7.h"

void Initialization() {
	weather_name_map[0] = "Sunny";
	weather_name_map[1] = "Mainly clear";
	weather_name_map[2] = "Cloudy";
	weather_name_map[3] = "Overcast";
	weather_name_map[45] = weather_name_map[48] = "Fog";
	weather_name_map[51] = "Little drizzle";
	weather_name_map[53] = "Moderate drizzle";
	weather_name_map[55] = "Dense drizzle";
	weather_name_map[61] = "Little rain";
	weather_name_map[63] = "Moderate rain";
	weather_name_map[65] = "Heavy rain";
	weather_name_map[66] = "Little Freezing Rain";
	weather_name_map[67] = "Heavy Freezing Rain";
	weather_name_map[71] = "Little snowfall";
	weather_name_map[73] = "Moderate snowfall";
	weather_name_map[75] = "Heavy snowfall";
	weather_name_map[77] = "Snow grains";
	weather_name_map[80] = "Little rain";
	weather_name_map[81] = "Moderate rain";
	weather_name_map[82] = "Heavy rain";
	weather_name_map[85] = "Little snow";
	weather_name_map[86] = "Heavy snow";
	weather_name_map[95] = weather_name_map[96] = weather_name_map[99] = "Thunderstorm";

	weather_image_map[0] = []() {
		return std::vector<ftxui::Element>{
			ftxui::text(R"(    \   /    )"),
				ftxui::text("     .-.     "),
				ftxui::text("  ‒ (   ) ‒  "),
				ftxui::text("     `-᾿     "),
				ftxui::text(R"(    /   \    )")};
		};

	weather_image_map[1] =
		weather_image_map[2] =
		weather_image_map[3] = []() {
		return std::vector<ftxui::Element>{
			ftxui::text("             "),
				ftxui::text("     .--.    "),
				ftxui::text("  .-(    ).  "),
				ftxui::text(" (___.__)__) "),
				ftxui::text("             ")};
		};

	weather_image_map[45] =
		weather_image_map[48] = []() {
		return std::vector<ftxui::Element>{
			ftxui::text("             "),
				ftxui::text(" _ - _ - _ - "),
				ftxui::text("  _ - _ - _  "),
				ftxui::text(" _ - _ - _ - "),
				ftxui::text("             ")};
		};

	weather_image_map[51] =
		weather_image_map[53] =
		weather_image_map[53] =
		weather_image_map[61] = []() {
		return std::vector<ftxui::Element>{
			ftxui::text("     .-.     "),
				ftxui::text("    (   ).   "),
				ftxui::text("   (___(__)  "),
				ftxui::text("    ʻ ʻ ʻ ʻ  "),
				ftxui::text("   ʻ ʻ ʻ ʻ   ")};
		};

	weather_image_map[56] =
	weather_image_map[57] =
	weather_image_map[66] =
	weather_image_map[67] = []() {
	return std::vector<ftxui::Element>{
		ftxui::text("     .-.     "),
		ftxui::text("    (   ).   "),
		ftxui::text("   (___(__)  "),
		ftxui::text("    ʻ * ʻ *  "),
		ftxui::text("   * ʻ * ʻ   ")};
	};

	weather_image_map[63] =
	weather_image_map[65] = []() {
	return std::vector<ftxui::Element>{
		ftxui::text("     .-.     "),
		ftxui::text("    (   ).   "),
		ftxui::text("   (___(__)  "),
		ftxui::text("  ‚ʻ‚ʻ‚ʻ‚ʻ   "),
		ftxui::text("  ‚ʻ‚ʻ‚ʻ‚ʻ   ")};
	};

	weather_image_map[71] =
	weather_image_map[73] =
	weather_image_map[75] =
	weather_image_map[77] = []() {
	return std::vector<ftxui::Element>{
		ftxui::text("     .-.     "),
		ftxui::text("    (   ).   "),
		ftxui::text("   (___(__)  "),
		ftxui::text("   * * * *   "),
		ftxui::text("  * * * *    ")};
	};

	weather_image_map[95] =
	weather_image_map[96] =
	weather_image_map[99] = []() {
	return std::vector<ftxui::Element>{
		ftxui::text("     .-.     "),
		ftxui::text("    (   ).   "),
		ftxui::text("   (___(__)  "),
		ftxui::text("   * * * *   "),
		ftxui::text("  * * * *    ")};
	};

	weather_image_map[85] =
	weather_image_map[86] = []() {
	return std::vector<ftxui::Element>{
		ftxui::text(R"( _`/\"\".-.    )"),
		ftxui::text(R"(  ,\_(   ).  )"),
		ftxui::text("   /(___(__) "),
		ftxui::text("    * * * *  "),
		ftxui::text("   * * * *   ")};
	};

	weather_image_map[80] =
	weather_image_map[81] =
	weather_image_map[82] = []() {
	return std::vector<ftxui::Element>{
		ftxui::text(R"( _`/\"\"-.   )"),
		ftxui::text(R"(  ,\\_(   ).  )"),
		ftxui::text("   /(___(__) "),
		ftxui::text("   ‚ʻ‚ʻ‚ʻ‚ʻ  "),
		ftxui::text("   ‚ʻ‚ʻ‚ʻ‚ʻ  ")};
	};
}

std::string GetWeatherName(int code) {
	if (weather_name_map.find(code) != weather_name_map.end())
		return weather_name_map[code];

	return "Unknown";
}

std::vector<ftxui::Element> GetWeatherImage(int code) {
	if (weather_image_map.find(code) != weather_image_map.end()) {
		return weather_image_map[code]();
	}

	return weather_image_map[0]();
}

std::vector<ftxui::Element> GetTimeDescription(int city, int day, const std::string& time) {
	WeatherVariables variables;
	if (time == "Morning") {
		variables = citiesWeather[city].GetWeatherVariables(day, 0);
	}
	else if (time == "Day") {
		variables = citiesWeather[city].GetWeatherVariables(day, 1);
	}
	else if (time == "Evening") {
		variables = citiesWeather[city].GetWeatherVariables(day, 2);
	}
	else {
		variables = citiesWeather[city].GetWeatherVariables(day, 3);
	}

	std::vector<ftxui::Element> description;

	description.push_back(ftxui::text(GetWeatherName(std::stoi(variables.weather_type))));

	std::string temperatures = variables.temperature;
	description.push_back(ftxui::text(temperatures + " °C"));

	description.push_back(ftxui::text(variables.wind_speed + " km/h"));
	int visibility = std::stoi(variables.wind_speed);
	description.push_back(ftxui::text(std::to_string(visibility) + " km"));
	description.push_back(ftxui::text(variables.precipitation + " %"));

	return description;
}

void getCityCoordinates(const nlohmann::json& config) {
	const std::string api_key_ninjas = config["api_key_ninjas"];

	cpr::Response city_response;
	nlohmann::json data;

	for (auto& name : config["cities"]) {
		city_response =
			cpr::Get(cpr::Url{ "https://api.api-ninjas.com/v1/city?name=" + static_cast<std::string>(name) },
				cpr::Header{ {"X-Api-Key", api_key_ninjas} });

		if (city_response.status_code != 200) {
			throw std::runtime_error(city_response.error.message);
		}

		data = nlohmann::json::parse(city_response.text).front();
		cities.push_back(
			City(static_cast<std::string>(name),
				data["latitude"],
				data["longitude"]
			)
		);
	}
}

void ParseWeatherData(nlohmann::json& data, const bool is_update, const int city_num, const int days) {
	for (int day = 0; day < days; day++) {
		for (int time = 4; time <= 22; time += 6) {
			WeatherVariables variables(
				cities[city_num].getName(),
				to_string(data["hourly"]["temperature_2m"][day * kDay_length + time]),
				to_string(data["hourly"]["wind_speed_10m"][day * kDay_length + time]),
				to_string(data["hourly"]["relativehumidity_2m"][day * kDay_length + time]),
				to_string(data["hourly"]["wind_direction_10m"][day * kDay_length + time]),
				to_string(data["hourly"]["weathercode"][day * kDay_length + time]),
				to_string(data["hourly"]["visibility"][day * kDay_length + time]),
				data["hourly"]["time"][day * kDay_length + time]);

			if (is_update) {
				citiesWeather[city_num].UpdateData(day * cities.size() + time / 6, variables);
			}
			else {
				citiesWeather[city_num].AddData(variables);
			}
		}
	}
}

void getWeatherData(City& city, const std::string& api_key_weather, const std::string days, nlohmann::json& data) {
	const cpr::Response response_weather =
		cpr::Get(cpr::Url{ "https://api.open-meteo.com/v1/forecast" },
			cpr::Header{ {"X-Api-Key", api_key_weather} },
			cpr::Parameters{ {"latitude", std::to_string(city.getLatitude())},
							{"longitude",std::to_string(city.getLongitude())},
							{"forecast_days", days},
							{"hourly", "temperature_2m"},
							{"hourly", "weathercode"},
							{"hourly", "relativehumidity_2m"},
							{"hourly", "wind_speed_10m"},
							{"hourly", "wind_direction_10m"},
							{"hourly", "visibility"} });

	if (response_weather.status_code != 200) {
		throw std::runtime_error(response_weather.error.message);
	}
	data = nlohmann::json::parse(response_weather.text);
}

void createDataCitiesWeather(const nlohmann::json& config) {
	const std::string api_key_weather = config["api_key_weather"];
	const int days = config["days"];
	nlohmann::json data;
	int iter = 0;
	for (auto& it : cities) {
		getWeatherData(it, api_key_weather, std::to_string(days), data);
		citiesWeather.push_back(WeatherData());
		ParseWeatherData(data, false, iter++, days);
	}
}

void updateWeatherData(const nlohmann::json& config) {
	const std::string api_key_weather = config["api_key_weather"];
	const int days = config["days"];
	nlohmann::json data;
	int iter = 0;
	for (auto& it : cities) {
		getWeatherData(it, api_key_weather, std::to_string(days), data);
		ParseWeatherData(data, true, iter++, days);
	}
}

std::vector<ftxui::Element> GetTimeImage(const int city, const int day, std::string time) {
	std::string weather_type;
	if (time == "Morning") {
		weather_type = citiesWeather[city].GetWeatherType(day, 0);
	}
	else if (time == "Day") {
		weather_type = citiesWeather[city].GetWeatherType(day, 1);
	}
	else if (time == "Evening") {
		weather_type = citiesWeather[city].GetWeatherType(day, 2);
	}
	else {
		weather_type = citiesWeather[city].GetWeatherType(day, 3);
	}

	return GetWeatherImage(std::stoi(weather_type));
}

void Start(nlohmann::json& config) {
	time_t local_time = time(0);
	auto screen = ftxui::ScreenInteractive::TerminalOutput();
	auto current_city = config["cities"].begin();

	auto component = ftxui::Renderer([&] {
		ftxui::Elements windows;
		windows.push_back(ftxui::text(cities[current_City].getName()) | ftxui::center);
		for (int day = 0; day < count_show_days; ++day) {
			ftxui::Elements row;

			for (const auto& time : time_of_day) {
				row.push_back(ftxui::vbox({ ftxui::text(time) | ftxui::center | ftxui::bold,
									ftxui::separator(),
									ftxui::hbox({
										vbox(GetTimeImage(current_City, day, time)),
										vbox(GetTimeDescription(current_City, day, time))
									}) })
					| ftxui::border | size(ftxui::WIDTH, ftxui::EQUAL, config["box_size"]));
			}

			windows.push_back(window(
				ftxui::text(citiesWeather[current_City].GetDayDate(day)) | ftxui::center,
				vbox(hbox(std::move(row)))));
		}
		windows.push_back(ftxui::text("last update: " + static_cast<std::string>(ctime(&local_time))) | ftxui::center);
		system("cls");
		return vbox(std::move(windows));
		});

	component = CatchEvent(component, [&](const ftxui::Event& event) {
		if (event == ftxui::Event::Character('q'))
			screen.ExitLoopClosure()();
		else if (event.input() == "+") {
			if (count_show_days < config["days"]) count_show_days++;
		}
		else if (event.input() == "-") {
			if (count_show_days > kMin_show_day) count_show_days--;
		}
		else if (event.input() == "n") {
			current_City = (current_City + 1) % cities.size();
		}
		else if (event.input() == "p") {
			current_City = (cities.size() + current_City - 1) % cities.size();
		}
		return false;
		});

	ftxui::Loop loop(&screen, component);
	auto last_time = std::chrono::steady_clock::now();
	while (!loop.HasQuitted()) {
		auto cur_time = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(cur_time - last_time).count() > config["tickrate"]) {
			last_time = cur_time;
			local_time = time(0);
			updateWeatherData(config);
		}
		loop.RunOnce();
	}
}

int main() {
	std::ifstream f("C:\\Vitaly\\myProjects\\cpp\\labwork7\\config.json");
	nlohmann::json config = nlohmann::json::parse(f);
	f.close();

	getCityCoordinates(config);
	createDataCitiesWeather(config);

	Initialization();
	Start(config);
	return 0;
}