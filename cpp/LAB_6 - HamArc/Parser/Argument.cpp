#pragma once
#include "string"
#include "vector"

namespace ArgumentParser {

	template<typename T>
	class Argument {
	public:
		explicit Argument() {};
		explicit Argument(const char short_name, const char* name, const char* description) : short_name(short_name), name(name), description(description) {};
		explicit Argument(const char* name, const char* description) : name(name), description(description) {};

		void AddName(const std::string& name) {
			this->name = name;
		}

		void AddShortName(const char short_name) {
			this->short_name = short_name;
		}

		std::string GetDescription() {
			return description;
		}

		std::vector<T> GetValue() {
			return values;
		}

		T GetDefaultValue() {
			return default_value;
		}
		void AddValue(T value) {
			values.push_back(value);
			is_default = false;
			if (is_outside_value) {
				(*outside_value) = value;
			}
			if (is_outside_vector) {
				(*outside_values).push_back(value);
			}
		}

		std::string GetName() {
			return name;
		}

		char GetShortName() {
			return short_name;
		}
		bool IsDefaultArgument() {
			return is_default;
		}

		void SetOutsideValue(std::vector<T>& vector) {
			outside_values = &vector;
			is_outside_vector = true;
		}

		void SetOutsideValue(T& value) {
			outside_value = &value;
			is_outside_value = true;
		}

		bool IsPositional() {
			return is_positional;
		}
		void SetMinCountArguments(int value) {
			min_count_arguments = value;
			is_multivalue = true;
		}

		bool IsMultiValue() {
			return is_multivalue;
		}

		size_t GetValuesSize() {
			return values.size();
		}

		int GetMinCountArguments() {
			return min_count_arguments;
		}

		void SetDefaultValue(T value) {
			default_value = value;
			is_default = true;
		}
		void SetPositional() {
			is_positional = true;
		}

	private:
		std::vector<T> values;
		char short_name;
		std::string name;
		std::string description;
		bool is_default{};
		std::vector<T>* outside_values{};
		T* outside_value{};
		bool is_outside_vector{};
		bool is_outside_value{};
		int min_count_arguments{};
		bool is_multivalue{};
		bool is_positional{};
		T default_value;
	};
} // namespace ArgumentParser