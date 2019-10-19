#include "TestSettings.h"

void initAlpha(list<char> * l)
{
    for(int i = 'a'; i <= 'z'; i++)
    {
        l->ListInsert(l->ListLength()  + 1,i);
    }
    cout << "初始化字母表" << endl;
    print<char>(l);
}
bool alphaGreater(char a, char b)
{
    if(a >= 'A' && a <= 'Z')
    {
        a = a - 'A' + 'a';
    }
    if(b >= 'A' && b <= 'Z')
    {
        b = b - 'A' + 'a';
    }
    return a > b;
}
void insertAlpha(LinkList<char> * l,char s)
{
    char temp = s;
    if(s >= 'A' && s <= 'Z')
    {
        temp = s - 'A' + 'a';
    }
    try
    {
        LinkList<char> temp;
        temp.ListInsert(temp.ListLength() + 1, s);
        *l = l->MergeList_Link(&temp, alphaGreater, equals<char>);
        cout << "插入字符 : " << s << endl;
        print<char>(l);
    }
    catch(char const * err)
    {
        cout << err << endl;
    }
}
void deleteAlpha(list<char> * l,char s)
{
    try
    {
        int i = l->LocateElement(s, equals<char>);
        l->ListDelete(i);
        cout << "删去字符 : " << s << endl;
        print<char>(l);
    }
    catch(char const * err)
    {
        cout << "没有字符 : " << s << endl;
    }
}
int AlphabetTest()
{
    LinkList<char> alpha;
    initAlpha(&alpha);

    insertAlpha(&alpha, 'M');
    insertAlpha(&alpha, 'm');
    insertAlpha(&alpha, 'P');
    insertAlpha(&alpha, 'p');

    deleteAlpha(&alpha,'a');
    deleteAlpha(&alpha,'A');
    return 0;
}

struct joseph
{
    int code;
    int pos;
    joseph(int a, int b)
    {
        code = a;
        pos = b;
    }
    joseph()
    {
    }
    friend ostream& operator<<(ostream& file, joseph& j)
    {
        file << "code = " <<  j.code << "\npos = " << j.pos << endl;
    }
};
void print_joseph(joseph x)
{
    cout << x.pos << " ";

}
bool equal_joseph(joseph x, joseph y)
{
    return x.code == y.code && x.pos == y.pos;
}
int josephTest()
{
    CycleList<joseph> CList;
    int m, n = 7;
    int code[7] = {3,1,7,2,4,8,4};
    for(int i = 0; i < 7; i++)
    {
        joseph data(code[i], i + 1);
        CList.ListInsert(CList.ListLength() + 1, data);
    }
    joseph e = CList.GetElement(1);
    m = 20;
    while(!CList.ListEmpty())
    {
        for(int j = 0; j < m - 1; j++)
        {
            e = CList.NextElement(e, equal_joseph);
        }
        joseph temp;
        try
        {
            temp = CList.NextElement(e, equal_joseph);
            CList.ListDelete(CList.LocateElement(e, equal_joseph));
        }
        catch(char const * s)
        {
            print_joseph(e);
            break;
        }
        print_joseph(e);
        m = e.code;
        e = temp;
    }
    return 0;
}
void convertion(int n, int m)
{
    int tempn = n;
    SqStack<int> s;
    if(m <= 1)
    {
        cout << "error!" << endl;
        return;
    }
    while(n)
    {
        s.Push(n % m);
        n /= m;
    }
    cout << tempn << "(" << 10 << ")" << " = ";
    while(!s.StackEmpty())
    {
        cout << s.Pop();
    }
    cout << "(" << m << ")" << endl;
}

void BracketsMatch(string& s)
{
    char match[128] = {0};
    match[')'] = '(';
    match['}'] = '{';
    match[']'] = '[';
    match['('] = -1;
    match['{'] = -1;
    match['['] = -1;
    char left[128] = {0};
    left[')'] = -1;
    left['}'] = -1;
    left[']'] = -1;
    int i = 0;
    int len = s.length();
    SqStack<char> sta;
    while(i < len)
    {
        if(match[s[i]] == -1)
        {
            sta.Push(s[i]);
        }
        else if (left[s[i]] == -1)
        {
            if(sta.GetTop() == match[s[i]])
            {
                sta.Pop();
            }
            else
            {
                cout << "error" << endl;
                return;
            }
        }
        i++;
    }
    if(!sta.StackEmpty())
    {
        cout << "error" << endl;
        return;
    }
    cout << "ok" << endl;

}
const int big = 1;
const int same = 2;
const int error = 0;
const int small = -1;
double operate(double a, char theta, double b)
{
    switch(theta)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    throw "unexpected operator";
}
void EvaluateExpression(string& s)
{
    SqStack<char> optr;
    SqStack<double> opnd;
    char isOption[128] = {0};
    string option = "+-*/()#";
    int opMap[128][128] = {0};
    opMap['+']['+'] = big;
    opMap['+']['-'] = big;
    opMap['+'][')'] = big;
    opMap['+']['#'] = big;
    opMap['+']['*'] = small;
    opMap['+']['/'] = small;
    opMap['+']['('] = small;

    opMap['-']['+'] = big;
    opMap['-']['-'] = big;
    opMap['-'][')'] = big;
    opMap['-']['#'] = big;
    opMap['-']['*'] = small;
    opMap['-']['/'] = small;
    opMap['-']['('] = small;

    opMap['*']['+'] = big;
    opMap['*']['-'] = big;
    opMap['*']['*'] = big;
    opMap['*']['/'] = big;
    opMap['*']['('] = small;
    opMap['*'][')'] = big;
    opMap['*']['#'] = big;

    opMap['/']['+'] = big;
    opMap['/']['-'] = big;
    opMap['/']['*'] = big;
    opMap['/']['/'] = big;
    opMap['/']['('] = small;
    opMap['/'][')'] = big;
    opMap['/']['#'] = big;

    opMap['(']['+'] = small;
    opMap['(']['-'] = small;
    opMap['(']['*'] = small;
    opMap['(']['/'] = small;
    opMap['(']['('] = small;
    opMap['('][')'] = same;
    opMap['(']['#'] = error;

    opMap[')']['+'] = big;
    opMap[')']['-'] = big;
    opMap[')']['*'] = big;
    opMap[')']['/'] = big;
    opMap[')']['('] = error;
    opMap[')'][')'] = big;
    opMap[')']['#'] = big;

    opMap['#']['+'] = small;
    opMap['#']['-'] = small;
    opMap['#']['*'] = small;
    opMap['#']['/'] = small;
    opMap['#']['('] = small;
    opMap['#'][')'] = error;
    opMap['#']['#'] = same;
    for(int i = 0; i < 7; i++)
    {
        isOption[option[i]] = 1;
    }

    int i = 0;
    if(s[i] == '#')
    {
        optr.Push(s[i]);
        i++;
    }
    else
    {
        cout << "wrong expression" << endl;
    }
    while (s[i] != '#' || optr.GetTop() != '#')
    {
        if(!isOption[s[i]])
        {
            string num;
            while(!isOption[s[i]] || s[i] == '.')
            {
                num.push_back(s[i]);
                i++;
            }
            stringstream ss(num);
            double n;
            ss >> n;
            //sscanf也可以
            opnd.Push(n);
        }
        else
        {
            switch(opMap[optr.GetTop()][s[i]])
            {
            case small :
                optr.Push(s[i]);
                i++;
                break;
            case same:
                optr.Pop();
                i++;
                break;
            case big:
                char theta = optr.Pop();
                double b = opnd.Pop();
                double a = opnd.Pop();//push的时候是减去了字符
                opnd.Push(operate(a, theta, b));
                break;
            }
        }
    }
    cout << s << " == " << opnd.GetTop() <<endl;
}
void BRACKETSMATCH_TEST()
{
    vector<string> test = {"()()(({{}[]}))", "{{]}"};
    int len = test.size();
    for(int i = 0; i < len; i++)
    {
        cout << test[i] << "is : ";
        BracketsMatch(test[i]);
    }
}

void EVALUATE_EXPRESSION_TEST()
{
    vector<string> test = {"#6/2+7-4*(8-6)#","#5+7-8*7/(5-5*2)#", "#15.7+78-4*(96-25)#"};
    int len = test.size();
    for(int i = 0; i < len; i++)
    {
        EvaluateExpression(test[i]);
    }
}
void Palindrome_Test(string& str)
{
    SqQueue<char> q;
    SqStack<char> s;
    cout << str << " ";
    for(char c : str)
    {
        q.EnQueue(c);
        s.Push(c);
    }
    while(!q.QueueEmpty())
    {
        char a = q.DeQueue();
        char b = s.Pop();
        if(a != b)
        {
            cout << "is not a Palindrome" << endl;
            return;
        }
    }
    cout << "is a Palindrome" << endl;
}
void Palindrome_Test()
{
    string s = "123456";
    Palindrome_Test(s);
    s = "abcdcba";
    Palindrome_Test(s);
}
struct monkey
{
    int id;
    int peach;
    monkey(int id)
    {
        this->id = id;
        peach = 0;
    }
    monkey()
    {
        id = 0;
        peach = 0;
    }
    friend ostream& operator<<(ostream& file, monkey& j)
    {
        file << "\nid = " <<  j.id << " peach = " << j.peach;
    }
    /*monkey(monkey& m) {
        this->id = m.id;
        this->peach = m.peach;
    }*/
};
//#define Monkey_Process
void MonkeyPeach_Test(int n, int k, int m)
{
    cout << "一共" << n << "个小猴子，篮子里一次性最多放" << k << "个桃子，每个小猴子要拿" << m << "个桃子" << endl;
    LinkQueue<monkey> q;
    for(int i = 0; i < n; i++)
    {
        monkey mky(i + 1);
        q.EnQueue(mky);
    }
    int curBlanket = 0;
    int temp_k = 0;
    SqList<monkey> l;
#ifdef Monkey_Process
    cout << "初始化猴子队列" << endl;
    print(&q);
#endif // Monkey_Process
    while(!q.QueueEmpty())
    {
        if(curBlanket == 0)
        {
            temp_k = temp_k%k + 1;
            curBlanket = temp_k;
        }
#ifdef Monkey_Process
        cout << "拿桃子前，剩余：" << curBlanket << endl;
#endif // Monkey_Process
        monkey temp = q.GetHead();
        int need = m-temp.peach;
        int sub = need > curBlanket ? curBlanket : need;
        temp.peach += sub;
        curBlanket -= sub;
        q.DeQueue();
        if(!(m - temp.peach))
        {
            l.ListInsert(l.ListLength() + 1, temp);
        }
        else
        {
            q.EnQueue(temp);
        }
#ifdef Monkey_Process
        print(&q);
        cout << "拿桃子后，剩余：" << curBlanket << endl;
#endif // Monkey_Process
    }
    cout << "小猴子的出队序列" << endl;
    print(&l);
}
void MonkeyPeach_Test()
{
    MonkeyPeach_Test(5,8,15);
    MonkeyPeach_Test(7,5,5);
}

void TriMatrix_Test(const vector<vector<int>>& va, const vector<vector<int>>& vb)
{
    TriMatrix<int> a(va);
    TriMatrix<int> b(vb);
    cout << "A:";
    print(&a);
    cout << "B:";
    print(&b);

    a.Reverse();
    b.Reverse();

    cout << "AB转置\n";
    cout << "A:";
    print(&a);
    cout << "B:";
    print(&b);

    TriMatrix<int> c = TriMatrix<int>::add(a,b);

    cout << "A + B:";
    print(&c);;
    system("pause");

}
void String_Test(const string& d, const string& s, const string& t) {
    cout << "在字符串 \"" << d << "\"\n"
         << "把所有   \"" << s << "\"\n"
         << "替换为   \"" << t  << "\""<< endl;
    String myStr(d);
    myStr.Replace(s, t);
    cout << "result : " << myStr.StrCopy() << endl << "\n";
}
int main()
{
    /*cout << "-----ALPHANET_TEST-----\n";
    AlphabetTest();
    cout << "\n------JOSEPH_TEST------\n";
    josephTest();
    cout << "\n------CONVERSION_TEST------\n";
    convertion(1,2);
    convertion(2,2);
    convertion(3,2);
    convertion(4,2);
    convertion(8,3);
    cout << "\n------BRACKETSMATCH_TEST------\n";
    BRACKETSMATCH_TEST();
    cout << "\n------EVALUATE_EXPRESSION_TEST------\n";
    try {
        EVALUATE_EXPRESSION_TEST();
    } catch(const char *s) {
        cout << s << endl;
    }*/
    /*cout << "\n------Palindrome_Test------\n";
    Palindrome_Test();
    WriteToFile();
    cout << "\n------MonkeyPeach_Test------\n";
    MonkeyPeach_Test();
    RecoverCOUT();*/
/*
    1 0 0
    5 0 0
    0 0 0
    2 10 0
    0 0 0
    0 0 0
    1 2 3
    4 5 6
    7 8 9
    10 11 12
    13 14 15
    16 17 18
*/
    cout << "\n------TriMatrix_Test------\n";
    TriMatrix_Test({{1,0,0},{5,0,0},{0,0,0}}, {{2,10,0},{0,0,0},{0,0,0}});
    TriMatrix_Test({{1,2,3},{4,5,6},{7,8,9}}, {{10,11,12},{13,14,15},{16,17,18}});

    cout << "\n------String_Test------\n";
	String_Test("ack1234567hijack1234567hijack1234567hijack1234567hij", "1234567", "(^_^)!!");
	String_Test("||||O_o||||", "|", "(>_<)");
	String_Test("ast12345678910Toast12345678910Toast12345678910To", "12345678910", "(>_<)!");
    return 0;
}
