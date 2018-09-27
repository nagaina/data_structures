#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <algorithm>
#include <string>

// Enum - Vector type -Row major or Column major
enum Vector_Type {ROW, COLUMN}; 

// Exception
struct Error
{
	Error(std::string m):massege(m) {}
	std::string massege;
};

template <typename T>
class Matrix;

// Vector
template <typename T>
class Vector
{
public:
	template <typename U>
	friend Matrix<U> operator*(const Matrix<U>&, const Vector<U>&);

	template <typename U>
	friend U operator*(const Vector<U>&, const Vector<U>&);

	Vector(T*& a, int s,int c, int i, Vector_Type t): array(a), size(s), column_count(c), index(i), type(t) {}
	T& operator[](int);
	int get_size() const;
private:
	Vector_Type type;
	int size;
	int column_count;
	int index;
	T*& array;
};

template <typename T>
T& Vector<T>::operator[](int i)
{
	if (type == ROW)
	{
		return array[index * column_count + i];
	}
	return array[i * column_count + index];
}

//
template <typename T>
T operator*(const Vector<T>& ob1, const Vector<T>& ob2)
{
	if (ob1.type == ROW && ob2.type == COLUMN && ob1.size == ob2.size)
	{
		T result = 0;
		for (int i = 0; i < ob1.size; ++i)
			result += ob1.array[ob1.index * ob1.column_count + i] * ob2.array[ob2.index + i * ob2.column_count];	
		return result;
	}
	throw Error("out of range");
}

//
template <typename T>
int Vector<T>::get_size() const
{
	return size;
}
// Matrix
template <typename T>
class Matrix
{
public:
	Matrix(int, int);
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	~Matrix();
	
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	
	Matrix& operator+=(const T&);
	Matrix& operator-=(const T&);
	Matrix& operator*=(const T&);
	Matrix& operator/=(const T&);
	
	Matrix<T> transpose();

	int get_rowcount() const;
	int get_columncount() const;

	Vector<T> get_row(int);
	Vector<T> get_column(int);

	T& operator()(int, int) const;

	void swap(Matrix&, Matrix&);

	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const Matrix<U>&);

	template <typename U>
	friend std::istream& operator>>(std::istream&, Matrix<U>&);

	template <typename U>
	friend Matrix<U> operator+(const Matrix<U>&, const Matrix<U>&);
	
	template <typename U>
	friend Matrix<U> operator-(const Matrix<U>&, const Matrix<U>&);

	template <typename U>
	friend Matrix<U> operator*(const Matrix<U>&, const Matrix<U>&);
	
	template <typename U>
	friend Matrix<U> operator*(const Matrix<U>&, const Vector<U>&);
	
	template <typename U>
	friend Matrix<U> operator+(const Matrix<U>&, const U&);
	
	template <typename U>
	friend Matrix<U> operator-(const Matrix<U>&, const U&);

	template <typename U>
	friend Matrix<U> operator*(const Matrix<U>&, const U&);
	
	template <typename U>
	friend Matrix<U> operator/(const Matrix<U>&, const U&);

	template <typename U>
	friend Matrix<U> operator+(const U&, const Matrix<U>&);
	
	template <typename U>
	friend Matrix<U> operator-(const U&, const Matrix<U>&);

	template <typename U>
	friend Matrix<U> operator*(const U&, const Matrix<U>&);
private:
	T* matrix;
	int column_count;
	int row_count;
};

// Parameter Constructor 
template <typename T>
Matrix<T>::Matrix(int r, int c):row_count(r), column_count(c)
{
	matrix = new T[row_count * column_count];
}

// Copy Constructor 
template <typename T>
Matrix<T>::Matrix(const Matrix& ob):row_count(ob.row_count), column_count(ob.column_count)
{
	matrix = new T[row_count * column_count];
	for (int i = 0; i < row_count * column_count; ++i)
		matrix[i] = ob.matrix[i];
}

// Assignment Operator 
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& ob)
{
	Matrix<T> temp(ob);
	swap(*this, temp);
	return *this;
}

//
template <typename T>
Vector<T> Matrix<T>::get_row(int i)
{
	return Vector<T>(matrix, column_count, column_count, i - 1, ROW); 
}

//
template <typename T>
Vector<T> Matrix<T>::get_column(int i)
{
	return Vector<T>(matrix,row_count, column_count, i - 1, COLUMN);
}

// Cumulative addition of this matrix and another  
template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& ob)
{
	if ((row_count == ob.row_count) && (column_count == ob.column_count))
	{
		for (int i = 0; i < row_count * column_count; ++i)
			matrix[i] += ob.matrix[i];
	}
	else throw Error("a");
}

// Matrix/scalar addition 
template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& data)
{
	for (int i = 0; i < row_count * column_count; ++i)
		matrix[i] += data;
}

// Matrix/scalar subtraction
template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T& data)
{
	for (int i = 0; i < row_count * column_count; ++i)
		matrix[i] -= data;
}

// Matrix/scalar multiplication
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& data)
{
	for (int i = 0; i < row_count * column_count; ++i)
		matrix[i] *= data;
}

// Matrix/scalar division
template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& data)
{
	if (data == 0)
		throw Error("g");
	for (int i = 0; i < row_count * column_count; ++i)
		matrix[i] /= data;
}
// Cumulative subtraction of this matrix and another  
template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& ob)
{
	if ((row_count == ob.row_count) && (column_count == ob.column_count))
	{
		for (int i = 0; i < row_count * column_count; ++i)
			matrix[i] -= ob.matrix[i];
	}
	else throw Error("a");
}

template <typename T>
void Matrix<T>::swap(Matrix<T>& first, Matrix<T>& second)
{
	std::swap(first.row_count, second.row_count);
	std::swap(first.column_count, second.column_count);
	std::swap(first.matrix, second.matrix);
}

template <typename T>
T& Matrix<T>::operator()(int i, int j) const
{
	if ((i-1 < 0 || i-1 >= row_count) || (j-1 < 0 || j-1 >= column_count))
		throw Error("Out of bounds");
	return matrix[(i-1) * column_count + j-1];
}

// Destructor
template <typename T>
Matrix<T>::~Matrix()
{
	delete matrix;
}

template <typename T>
int Matrix<T>::get_rowcount() const
{
	return row_count;
}

template <typename T>
int Matrix<T>::get_columncount() const
{
	return column_count;
}

// Calculate a transpose of this matrix
template <typename T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix<T> result(column_count, row_count);
	for (int i = 0; i < row_count; ++i)
		for (int j = 0; j < column_count; ++j)
			result.matrix[j * result.column_count + i] = matrix[i * column_count + j];
	return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const Matrix<T>& ob)
{	
	for (int i = 0; i < ob.row_count; ++i)
		for (int j = 0; j < ob.column_count; ++j)
		{
			output <<"[" << i + 1 <<" , " << j + 1 <<"] =" << ob.matrix[i* ob.column_count + j] << "\n";
		}
	return output;
		
}

template <typename T>
std::istream& operator>>(std::istream& input, Matrix<T>& ob)
{
	for (int i = 0; i < ob.row_count; ++i)
		for (int j = 0; j < ob.column_count; ++j)
		{
			std::cout <<"[" << i + 1 <<" , " << j + 1 <<"] = ";
			input >> ob.matrix[i* ob.column_count + j];
			std::cout << std::endl;
		}
	return input;
}

// Addition of two matrices  
template <typename T>
Matrix<T> operator+(const Matrix<T>& ob1, const Matrix<T>& ob2)
{
	if ((ob1.row_count == ob2.row_count) && (ob1.column_count == ob2. column_count))
	{
		Matrix<T> result(ob1.row_count, ob1.column_count);
		for (int i = 0; i < ob1.row_count * ob1.column_count; ++i)
			result.matrix[i] = ob1.matrix[i] + ob2.matrix[i];
		return result; 
	}
	throw Error("a");
}


// Subtraction of this matrix and another
template <typename T>
Matrix<T> operator-(const Matrix<T>& ob1, const Matrix<T>& ob2)
{
	if ((ob1.row_count == ob2.row_count) && (ob1.column_count == ob2. column_count))
	{
		Matrix<T> result(ob1.row_count, ob1.column_count);
		for (int i = 0; i < ob1.row_count * ob1.column_count; ++i)
			result.matrix[i] = ob1.matrix[i] - ob2.matrix[i];
		return result; 
	}
	throw Error("a");
}

// Multiplication of this matrix and another
template <typename T>
Matrix<T> operator*(const Matrix<T>& ob1, const Matrix<T>& ob2)
{
	if (ob1.column_count == ob2.row_count)
	{
		Matrix<T> result(ob1.row_count, ob2.column_count);
		for (int i = 0; i < result.row_count; ++i)
			for (int j = 0; j < result.column_count; ++j)
			{
				T sum = 0;
				for (int k = 0; k < ob1.column_count; ++k)
					sum += ob1.matrix[i* ob1.column_count + k] * ob2.matrix[k * ob2.column_count + j]; 
				result.matrix[i * result.column_count + j] = sum;
			}
		return result;
	}
	throw Error("g");
}

// Matrix/scalar addition 
template <typename T>
Matrix<T> operator+(const Matrix<T>& ob, const T& data)
{
	Matrix<T> result(ob.row_count, ob.column_count);
	for (int i = 0; i < ob.row_count * ob.column_count; ++i)
		result.matrix[i] = ob.matrix[i] + data;
	return result; 
}

// Scalar/matrix addition 
template <typename T>
Matrix<T> operator+(const T& data, const Matrix<T>& ob)
{
	Matrix<T> result(ob.row_count, ob.column_count);
	for (int i = 0; i < ob.row_count * ob.column_count; ++i)
		result.matrix[i] = ob.matrix[i] + data;
	return result; 
}

// Matrix/scalar subtraction
template <typename T>
Matrix<T> operator-(const Matrix<T>& ob, const T& data)
{
	Matrix<T> result(ob.row_count, ob.column_count);
	for (int i = 0; i < ob.row_count * ob.column_count; ++i)
		result.matrix[i] = ob.matrix[i] - data;
	return result; 
}

// Scalar/matrix subtraction
template <typename T>
Matrix<T> operator-(const T& data, const Matrix<T>& ob)
{
	Matrix<T> result(ob.row_count, ob.column_count);
	for (int i = 0; i < ob.row_count * ob.column_count; ++i)
		result.matrix[i] = ob.matrix[i] - data;
	return result; 
}

// Matrix/scalar multiplication
template <typename T>
Matrix<T> operator*(const Matrix<T>& ob, const T& data)
{
	Matrix<T> result(ob.row_count, ob.column_count);
	for (int i = 0; i < ob.row_count * ob.column_count; ++i)
		result.matrix[i] = ob.matrix[i] * data;
	return result; 
}

// Scalar/matrix multiplication
template <typename T>
Matrix<T> operator*(const T& data, const Matrix<T>& ob)
{
	Matrix<T> result(ob.row_count, ob.column_count);
	for (int i = 0; i < ob.row_count * ob.column_count; ++i)
		result.matrix[i] = ob.matrix[i] * data;
	return result; 
}
// Matrix/scalar division
template <typename T>
Matrix<T> operator/(const Matrix<T>& ob, const T& data)
{
	if (data == 0)
		throw Error("G");
	Matrix<T> result(ob.row_count, ob.column_count);
	for (int i = 0; i < ob.row_count * ob.column_count; ++i)
		result.matrix[i] = ob.matrix[i] / data;
	return result; 
}

//
template <typename T>
Matrix<T> operator*(const Matrix<T>& m, const Vector<T>& v)
{
	if ((m.column_count == v.size) && v.type == COLUMN)
	{
		Matrix<T> result(m.row_count,1);
		for (int i = 0; i < result.row_count; ++i)
			for (int j = 0; j < result.column_count; ++j)
			{
				T sum = 0;
				for (int k = 0; k < m.column_count; ++k)
					sum += m.matrix[i* m.column_count + k] * v.array[k * v.column_count + v.index]; 
				result.matrix[i * result.column_count + j] = sum;
			}
		return result;
	}
	throw Error("g");
}

#endif
