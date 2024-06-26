// labwork7.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include "ftxui/component/captured_mouse.hpp"
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/loop.hpp>
#include "ftxui/component/event.hpp"
#include <map>
#include <ctime>
#include "City.cpp"
#include "WeatherData.cpp"

std::vector<City> cities;
std::vector<WeatherData> citiesWeather;
std::vector<std::string> time_of_day = { "Morning", "Day", "Evening", "Night" };
std::unordered_map<int, std::function<std::vector<ftxui::Element>()>> weather_image_map;
std::map<int, std::string> weather_name_map;


int count_show_days = 3;
int current_City = 0;

const int kMin_show_day = 1;
const int kDay_length = 24;

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.