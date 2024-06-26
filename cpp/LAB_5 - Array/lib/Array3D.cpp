#include "Array3D.h"

Array3D::Array3D(const int nx, const int ny, const int nz) {
	data = new Data(nx, ny, nz);
}

Array3D Array3D::make_array(const int nx, const int ny, const int nz) {
	Array3D new_array(nx, ny, nz);
	for (int i = 0; i < nx * ny * nz; i++) {
		new_array.data->data[i] = 0;
	}

	for (int i = 0; i < static_cast<int>(ceil(nx * ny * nz / 16.0)); i++) {
		new_array.data->add_data[i] = 0;
	}
	return new_array;
}

bool Array3D::Data::IsEqualSize(const Data* other) const {
	return (other->x_size == x_size && other->y_size == y_size && other->z_size == z_size);
}

Array3D Array3D::operator-(const Array3D& rigth_arr) const {
	if (!data->IsEqualSize(rigth_arr.data)) {
		std::cerr << "Trying to sub arrays with different sizes";
		throw std::runtime_error("Trying to sub arrays with different sizes");
	}

	Array3D new_array = Array3D::make_array(data->x_size, data->y_size, data->z_size);

	for (int x = 0; x < data->x_size; x++) {
		for (int y = 0; y < data->y_size; y++) {
			for (int z = 0; z < data->z_size; z++) {
				new_array[x][y][z] = data->GetElement(x, y, z) - rigth_arr.data->GetElement(x, y, z);
			}
		}
	}
	return new_array;
}

Array3D Array3D::operator+(const Array3D& rigth_arr) const {
	if (!data->IsEqualSize(rigth_arr.data)) {
		std::cerr << "Trying to sum arrays with different sizes";
		throw std::runtime_error("Trying to sum arrays with different sizes");
	}

	Array3D new_array = Array3D::make_array(data->x_size, data->y_size, data->z_size);

	for (int x = 0; x < data->x_size; x++) {
		for (int y = 0; y < data->y_size; y++) {
			for (int z = 0; z < data->z_size; z++) {
				new_array[x][y][z] = data->GetElement(x, y, z) + rigth_arr.data->GetElement(x, y, z);
			}
		}
	}
	return new_array;
}

Array3D Array3D::operator*(int h) const {
	Array3D arr = Array3D::make_array(data->x_size, data->y_size, data->z_size);

	for (int x = 0; x < data->x_size; x++) {
		for (int y = 0; y < data->y_size; y++) {
			for (int z = 0; z < data->z_size; z++) {
				arr[x][y][z] = data->GetElement(x, y, z) * h;
			}
		}
	}
	return arr;
}

Array3D::YOperator Array3D::operator[](int x) {
	if (data->x_size <= x) {
		std::cerr << "Out of range x axis";
		throw std::out_of_range("Out of range x axis");
	}
	int elem = x * data->y_size * data->z_size;
	return YOperator(elem, this);
}

Array3D::Array3D(const Array3D& other) {
	delete data;
	data = new Data(*other.data);
}

bool Array3D::Data::operator==(int value) const {
	return GetElement(elem_pos) == value;
}

Array3D& Array3D::operator=(const Array3D& other) {
	if (this != &other) {
		delete data;
		data = new Data(*other.data);
	}

	return *this;
}

Array3D::Array3D() {
	data = new Data();
}

Array3D::~Array3D() {
	delete data;
}

Array3D::ZOperator Array3D::YOperator::operator[](int y) const {
	if (array->data->y_size <= y) {
		std::cerr << "Out of range y axis";
		throw std::out_of_range("Out of range y axis");
	}
	return ZOperator(elem + y * array->data->z_size, array);
}

Array3D::Data& Array3D::ZOperator::operator[](int z) const {
	if (array->data->z_size <= z) {
		std::cerr << "Out of range z axis";
		throw std::out_of_range("Out of range z axis");
	}
	array->data->elem_pos = elem + z;
	return *(array->data);
}

Array3D::YOperator::YOperator(int elem, Array3D* array) : elem(elem), array(array) {}
Array3D::ZOperator::ZOperator(int elem, Array3D* array) : elem(elem), array(array) {}

Array3D::Data::Data(int nx, int ny, int nz) : x_size(nx), y_size(ny), z_size(nz), elem_pos(0) {
	data = new uint16_t[nx * ny * nz];
	add_data = new uint16_t[static_cast<int>(ceil(nx * ny * nz / 16.0))];
}

Array3D::Data::Data(const Data& other) : x_size(other.x_size), y_size(other.y_size), z_size(other.z_size), elem_pos(0) {
	delete[] data;
	delete[] add_data;

	data = new uint16_t[x_size * y_size * z_size];
	add_data = new uint16_t[static_cast<int>(ceil(x_size * y_size * z_size / 16.0))];

	for (int i = 0; i < x_size * y_size * z_size; i++) {
		data[i] = other.data[i];
	}

	for (int i = 0; i < static_cast<int>(ceil(x_size * y_size * z_size / 16.0)); i++) {
		add_data[i] = other.add_data[i];
	}
}

Array3D::Data& Array3D::Data::operator=(const int value) {
	SetElement(elem_pos, value);
	return *this;
}

Array3D::Data& Array3D::Data::operator=(const Data& other) {
	if (this != &other) {
		delete[] data;
		delete[] add_data;

		data = new uint16_t[x_size * y_size * z_size];
		add_data = new uint16_t[static_cast<int>(ceil(x_size * y_size * z_size / 16.0))];

		for (int i = 0; i < x_size * y_size * z_size; i++) {
			data[i] = other.data[i];
		}

		for (int i = 0; i < static_cast<int>(ceil(x_size * y_size * z_size / 16.0)); i++) {
			add_data[i] = other.add_data[i];
		}
	}

	return *this;
}

Array3D::Data::~Data() {
	delete[] data;
	delete[] add_data;
}

int Array3D::Data::GetElement(const int pos) const {
	int result = data[pos];
	if (add_data[pos / 16] & (1 << (pos % 16))) {
		result += (1 << 16);
	}

	return result;
}

int Array3D::Data::GetElement(const int x, const int y, const int z) const {
	return GetElement(x * y_size * z_size + y * z_size + z);
}

void Array3D::Data::SetElement(const int pos, const int value) {
	data[pos] = value % (1 << 16);
	bool is_bit_in_value = value & (1 << 16);
	bool is_bit_in_add_data = add_data[pos / 16] & (1 << (pos % 16));

	if ((!is_bit_in_value && is_bit_in_add_data) || (is_bit_in_value && !is_bit_in_add_data)) {
		add_data[pos / 16] ^= (1 << (pos % 16));
	}
}

std::ostream& operator<<(std::ostream& stream, Array3D::Data& data) {
	stream << data.GetElement(data.elem_pos);
	return stream;
}

std::istream& operator>>(std::istream& stream, Array3D::Data& data) {
	int value;
	stream >> value;
	data.SetElement(data.elem_pos, value);
	return stream;
}
