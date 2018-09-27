#include "matrix.hpp"

int main()
{
	Matrix<int> A(5,3);
	A(1,1) = 1;
	A(1,2) = 3;
	A(1,3) = 1;
	A(2,1) = 3;
	A(2,2) = 6;
	A(2,3) = 0;
	A(3,1) = 2;
	A(3,2) = 7;
	A(3,3) = 2;
	A(4,1) = 1;
	A(4,2) = 8;
	A(4,3) = 0;
	A(5,1) = 3;
	A(5,2) = 6;
	A(5,3) = 5;
	//std::cout<<"A matrix is -> "<<A<<std::endl;
	
	//std::cout<<"5*A = "<<5*A<<std::endl;
	//std::cout<<"A transpose = "<< A.transpose()<<std::endl;
	
	Matrix<int> B(3,5);
	B(1,1) = 4;
	B(1,2) = 4;
	B(1,3) = 0;
	B(1,4) = 2;
	B(1,5) = 0;
	B(2,1) = 6;
	B(2,2) = 5;
	B(2,3) = 0;
	B(2,4) = 0;
	B(2,5) = 0;
	B(3,1) = 1;
	B(3,2) = 2;
	B(3,3) = 1;
	B(3,4) = 1;
	B(3,5) = 0;

	//std::cout<< "A*B =  "<<A*B<<std::endl;

	Vector<int> row = A.get_row(3);
	Vector<int> column = B.get_column(1);
	
	std::cout <<row* column <<std::endl;
}
