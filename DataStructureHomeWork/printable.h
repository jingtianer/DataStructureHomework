#ifndef MY_PRINTABLE_H
#define MY_PRINTABLE_H
template<class T>
class Printable {
public:
	virtual void printAll() = 0;
};
template <class T>
void print_all(T x) { std::cout << x << " "; }

template <class T>
bool equals(T i, T j) { return i == j; }

template <class T>
bool Greater(T i, T j) { return i > j; };
template <class T>
bool Smaller(T i, T j) { return i < j; };
#endif // !MY_PRINTABLE_H
