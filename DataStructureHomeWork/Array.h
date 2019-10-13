#ifndef MY_ARRAY_H
#define MY_ARRAY_H
#include"printable.h"
#include<stdarg.h>
template<class T>
class Array {
private:
	T* base;
	int dim;
	int* bounds;//每一个维度数组长度
	int* constants;//数组映像函数
	int elemTotal;
public:
	Array(int dim, ...){
		va_list args;
		va_start(args, dim);
		InitArray(dim, args);
		va_end(args);
	}
	~Array(){
		DestroyArry();
	}
	void InitArray(int dim, va_list args) {
		if (dim < 1)
		{
			throw "Error";
		}//判断维度数dimension是否合法
		this->dim = dim;
		bounds = new int[dim];
		if (!bounds) throw "Alloc Fail";
		//边界数组初始化
		int elemTotal = 1;
		//开始获得可变参数
		for (int i = 0; i < dim; i++) {
			bounds[i] = va_arg(args, int);
			if (bounds[i] < 0) throw "ILLEGAL_LENGTH_OF_ARRAY";
			elemTotal *= bounds[i];
		}
		this->elemTotal = elemTotal;

		base = new T[elemTotal];
		if (!base) throw "Alloc Fail";
		constants = new int[dim];
		if (!constants)
		{
			throw "Alloc Fail";
		}
		constants[dim - 1] = 1;
		for (int i = dim-2; i >= 0 ; i--)
		{
			constants[i] = bounds[i + 1] * constants[i + 1];
		}
	}
	void DestroyArry() {
		if (!base)
		{
			delete[] base;
			base = nullptr;
		}
		if (!bounds)
		{
			delete[] bounds;
			bounds = nullptr;
		}
		if (!constants) {
			delete[] constants;
			constants = nullptr;
		}
	}
	void Value(T* e,...) {
		va_list args;
		va_start(args, e);
		int result = Locate(args);
		*e = base[result];
		va_end(args);
	}
	
	void Assign(T e, ...) {
		va_list args;
		va_start(args, e);
		int result = Locate(args);
		base[result] = e;
		va_end(args);
	}

private:
	int Locate(va_list args) {
		int off = 0;
		for (int i = 0; i < dim; i++)
		{
			int ind = va_arg(args, int);
			if (ind < 0 || ind >= bounds[i])
			{
				throw "IndexOutOfBounds";
			}
			off += constants[i] * ind;
		}
		return off;
	}
	

};
#endif // !MY_ARRAY_H