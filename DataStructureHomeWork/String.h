#ifndef MY_STRING_H
#define MY_STRING_H
#include<string>
using namespace std;
class ADTString {
public:
	virtual void StrAssign(const string& s) = 0;
	virtual string StrCopy() = 0;
	virtual bool StrEmpty() = 0;
	virtual int StrCompare(const string& s) = 0;
	virtual int StrLength() = 0;
	virtual void ClearString() = 0;
	virtual void Concat(const string& s) = 0;
	virtual string SubString(int pos, int len) = 0;
	virtual int Index(const string& s) = 0;
	virtual void Replace(const string& t, const string& v) = 0;
	virtual void StrInsert(int pos, const string& t) = 0;
	virtual void StrDelete(int pos, int len) = 0;
	virtual void DestroyString() = 0;
	static const int Longer = 1;
	static const int Smaller = -1;
	static const int Equal = 0;
};

class String : ADTString {
public:
	String(){}
	String(const string& init) {
		StrAssign(init);
	}
	~String() {
		DestroyString();
	}
	void StrAssign(const string& s){
		size_t l = s.length();
		data.clear();
		for (int i = 0; i < l; i++) {
			data.push_back(s[i]);
		}
	}
	string StrCopy(){
		string s;
		int l = data.size();
		for (int i = 0; i < l; i++) {
			s.push_back(data[i]);
		}
		return s;
	}
	bool StrEmpty(){
		return data.empty();
	}
	int StrCompare(const string& s){
		size_t l1 = s.length();
		size_t l2 = data.size();
		if (l1 > l2) {
			return Longer;
		}
		else if (l1 < l2) {
			return Smaller;
		}
		int i = 0;
		while (i < l1 && s[i] == data[i]) {
			i++;
		}
		if (i == l1) return Equal;
		else {
			if (s[i] > data[i]) return Longer;
			else return Smaller;
		}
	}
	int StrLength(){
		return data.size();
	}
	void ClearString(){
		data.clear();
	}
	void Concat(const string& s){
		size_t l = s.length();
		for (int i = 0; i < l; i++) {
			data.push_back(s[i]);
		}
	}
	string SubString(int pos, int len){
		string s;
		size_t l = data.size();
		for (int i = 0; i < len && i + pos < l; i++) {
			s.push_back(data[i + pos]);
		}
		return s;
	}

	void Replace(const string& t, const string& v){
		vector<char> NewData;
		int pos = 0;
		int i = 0;
		size_t len = data.size();
		size_t len2 = v.length();
		size_t len3 = t.length();
		while ((pos = Index(t)) != -1) {
			for (; i < pos; i++) {
				NewData.push_back(data[i]);
			}
			for (int j = 0; j < len3; j++,++i) {
				data[i] = 0;
			}
			for (int j = 0; j < len2; j++) {
				NewData.push_back(v[j]);
			}
		}
		for(; i < len; i++) {
            NewData.push_back(data[i]);
		}
		data = NewData;
	}
	void StrInsert(int pos, const string& t){
		vector<char> NewData;
		size_t l1 = data.size();
		size_t l2 = t.length();
		for (int i = 0; i < pos; i++) {
			NewData.push_back(data[i]);
		}
		for (int i = 0; i < l2; i++) {
			NewData.push_back(t[i]);
		}
		for (int i = pos; i < l1; i++) {
			NewData.push_back(data[i]);
		}
		data = NewData;
	}
	void StrDelete(int pos, int len){
		size_t size = data.size();
		for (int i = pos; i + len < size; i++) {
			data[i] = data[i + len];
		}
		size -= (size - pos > len) ? len : (size - pos);
		data.resize(size);
	}
	void DestroyString(){
		ClearString();
	}
	int Index(const string& B)
	{
		return KMP(B);
	}
private:
	vector<int> getNext(string p) {
		vector<int> next(p.size());
		int j = 0;
		int k = -1;
		next[0] = -1;
		while (j < p.size() - 1) {   //注意要小于长度减1
			if (k == -1 || p[j] == p[k]) {
				if (p[++j] == p[++k])
					next[j] = next[k];
				else
					next[j] = k;
			}
			else
				k = next[k];
		}
		return next;
	}

	int KMP(string p) {
		int i = 0, j = 0;
		vector<int> next = getNext(p);
		while ((i < data.size()) && j < (int)p.size()) {//这个地方易错，一定要强制转换，j有可能取-1，

		  //此时p.size和-1比较会出现小于-1，对j取绝对值比较也可以

		  //   abs(j)<p.size() 也可以
			if (j == -1 || data[i] == p[j]) {
				i++; j++;
			}
			else {
				j = next[j];
			}
		}
		if (j == p.size()) {
			return i - j;
		}
		else
			return -1;
	}
	vector<char> data;
};
#endif // !MY_STRING_H
