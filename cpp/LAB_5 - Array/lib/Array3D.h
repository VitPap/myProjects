#pragma once
#include <iostream>
#include <cmath>

class Array3D {
private:
	class Data {
	public:
		Data() = default;
		Data(const int nx, const int ny, const int nz);
		Data(const Data& other);
		Data& operator=(int value);
		friend std::ostream& operator<<(std::ostream& stream, Data& data);
		friend std::istream& operator>>(std::istream& stream, Data& data);
		int GetElement(const int pos) const;
		int GetElement(const int x, const int y, const int z) const;
		void SetElement(const int pos, const int value);
		Data& operator=(const Data& other);
		bool operator==(int value) const;
		bool IsEqualSize(const Data* other) const;
		~Data();
	private:
		friend Array3D;
		int x_size{}, y_size{}, z_size{};
		int elem_pos{};
		uint16_t* data{};
		uint16_t* add_data{};
	};

	Data* data;

	friend std::ostream& operator<<(std::ostream& stream, Data& data);
	friend std::istream& operator>>(std::istream& stream, Data& data);

	class ZOperator {
	public:
		ZOperator(int elem, Array3D* array);
		Array3D::Data& operator[](int z) const;
	private:
		Array3D* array;
		int elem;
	};

	class YOperator {
	public:
		YOperator(int elem, Array3D* array);
		ZOperator operator[](int y) const;
	private:
		Array3D* array;
		int elem;
	};

public:
	explicit Array3D();
	explicit Array3D(int nx, int ny, int nz);
	Array3D(const Array3D& other);
	Array3D& operator=(const Array3D& other);
	static Array3D make_array(int nx, int ny, int nz);

	Array3D operator-(const Array3D& rigth_arr) const;
	Array3D operator+(const Array3D& right_arr) const;
	Array3D operator*(int h) const;
	YOperator operator[](int x);


	~Array3D();
};