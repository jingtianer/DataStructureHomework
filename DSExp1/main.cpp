#include "TestSettings.h"

void initAlpha(list<char> * l) {
    for(int i = 'a'; i <= 'z'; i++) {
		l->ListInsert(l->ListLength()  + 1,i);
	}
	cout << "³õÊ¼»¯×ÖÄ¸±í" << endl;
	print<char>(l);
}
bool alphaGreater(char a, char b) {
    if(a >= 'A' && a <= 'Z') {
        a = a - 'A' + 'a';
    }
    if(b >= 'A' && b <= 'Z') {
        b = b - 'A' + 'a';
    }
    return a > b;
}
void insertAlpha(LinkList<char> * l,char s) {
    char temp = s;
    if(s >= 'A' && s <= 'Z') {
        temp = s - 'A' + 'a';
    }
    try {
        LinkList<char> temp;
        temp.ListInsert(temp.ListLength() + 1, s);
        *l = l->MergeList_Link(&temp, alphaGreater, equals<char>);
        cout << "²åÈë×Ö·û : " << s << endl;
        print<char>(l);
    } catch(char const * err) {
        cout << err << endl;
    }
}
void deleteAlpha(list<char> * l,char s) {
    try {
        int i = l->LocateElement(s, equals<char>);
        l->ListDelete(i);
        cout << "É¾È¥×Ö·û : " << s << endl;
        print<char>(l);
    } catch(char const * err) {
        cout << "Ã»ÓÐ×Ö·û : " << s << endl;
    }
}
int AlphabetTest() {
	LinkList<char> alpha;
	initAlpha(&alpha);

	insertAlpha(&alpha, 'M');
	insertAlpha(&alpha, 'm');
	insertAlpha(&alpha, 'P');
	insertAlpha(&alpha, 'p');

	deleteAlpha(&alpha ,'a');
	deleteAlpha(&alpha ,'A');
	return 0;
}

struct joseph {
    int code;
    int pos;
    joseph(int a, int b) {
        code = a;
        pos = b;
    }
    joseph() {
    }
};
void print_joseph(joseph x) {
    cout << x.pos << " ";

}
bool equal_joseph(joseph x, joseph y) {
    return x.code == y.code && x.pos == y.pos;
}
int josephTest() {
    CycleList<joseph> CList;
    int m, n = 7;
    int code[7] = {3,1,7,2,4,8,4};
    for(int i = 0; i < 7; i++) {
        joseph data(code[i], i + 1);
        CList.ListInsert(CList.ListLength() + 1, data);
    }
    joseph e = CList.GetElement(1);
    m = 6;
    while(!CList.ListEmpty()) {
        for(int j = 0; j < m - 1; j++) {
            e = CList.NextElement(e, equal_joseph);
        }
        joseph temp;
        try {
            temp = CList.NextElement(e, equal_joseph);
            CList.ListDelete(CList.LocateElement(e, equal_joseph));
        } catch(char const * s) {
            print_joseph(e);
            break;
        }
        print_joseph(e);
        m = e.code;
        e = temp;
    }
    return 0;
}

int main() {
    cout << "-----ALPHANET_TEST-----\n";
    AlphabetTest();
    cout << "\n------JOSEPH_TEST------\n";
    josephTest();
    return 0;
}
