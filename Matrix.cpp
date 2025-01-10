#include<iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "GradeBook.h"
using namespace std;


class Matrix {
	friend ostream &operator<< (ostream &, const Matrix &);
	friend istream &operator>> (istream &, Matrix &);
public:
	Matrix (int inr = 10, int inc = 10){
		row = inr; col = inc; 
		data = new int*[row];
		for(int i = 0; i < row; i++)
			data[i] = new int[col];	
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				data [i][j] = 0;
	}
	Matrix operator+(const Matrix &);
	Matrix operator*(const Matrix &);
	operator int ()const;
private:
	int row, col;
	int **data;	
};

Matrix Matrix::operator+(const Matrix &m){
	
	if (this->row != m.row || this->col != m.col){		
		exit (0);
	}	
	Matrix result(row, col);
	for (int i = 0; i < this->row; i++){
		for (int j = 0; j < this->col; j++){
			result.data [i][j] = this->data [i][j] + m.data [i][j];
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix &m){
	
	if (this->col != m.row){		
		exit (0);
	}	
	Matrix result(this->row, m.col);
	for (int k = 0; k < this->col; k++){
		for (int i = 0; i < this->row; i++){
			for (int j = 0; j < m.col; j++){				
				result.data [i][j] += this->data [i][k] * m.data [k][j];				
			}
		}
	}
	return result;
}


ostream &operator<< (ostream &output, const Matrix &m){	
	for (int i = 0; i < m.row; i++){
		for (int j = 0; j < m.col; j++){
			output << m.data [i][j] << " ";			 
		}
		output << endl;
	}
	return output;
}

istream &operator>> (istream &input, Matrix &m){
	//input >> m.row >> m.col;
	int indata;
	for (int i = 0; i < m.row; i++){
		for (int j = 0; j < m.col; j++){
			input >> indata;
			m.data [i][j] = indata;
		}
	}

	return input;
}

Matrix::operator int() const{
	
	int total = 0;
	for (int i = 0; i < this->row; i++){
		for (int j = 0; j < this->col; j++){
			total += this->data [i][j];
		}
	}
	return total;
}


void main(){

	int num, row, col;

	cin >> num;
	Matrix *m[10];	
	for (int i = 0; i < num; i++){		
		cin >> row >> col;
		m [i] = new Matrix (row, col);
		cin >> *m[i];
	}

	for (int i = 0; i < num; i++){
		cout << *m[i];
	}
	Matrix a;
	a = (*m[0]) * (*m[1]);
	cout << a;

	cout << "Value of m[0] is " << static_cast<int> (*m[0]) << endl;
	cout << "Value of m[1] is " << static_cast<int> (*m[1]) << endl;
	cout << "Value of a is " << static_cast<int> (a) << endl;

	system("pause");
}
