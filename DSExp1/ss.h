#ifndef SS_H_INCLUDED
#define SS_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;

struct ss{
    string s;
    int length;
    ss()
    {
        s="";
        length=0;
    };
    ss substring(int index,int len)
    {
        ss temp;
        temp.s="";
        for(int i=index;i<index+len;i++)
            temp.s+=s[i];
        temp.length=len;
        return temp;
    }

    ss prestr(int index) //Ç°×º´®
    {
        ss temp;
        temp.s="";
        temp.length=0;
        for(int i=0;i<index;i++)
            temp.s+=s[i],temp.length++;
        return temp;
    }

    ss substr(int index)
    {
        ss temp;
        temp.s="";
        temp.length=0;
        for(int i=index;i<length;i++)
            temp.s+=s[i],temp.length++;
        return temp;
    }

    ss(string s)
    {
        this->s=s;
        this->length=s.size();
    }

    int find(ss x)
    {
        for(int i=0;i<=length-x.length;i++)
        {
            bool flag=true;
            for(int j=0;j<x.length;j++)
                if(s[i+j]!=x.s[j]){
                    flag=false;
                    break;
                }
            if(flag==true) return i;
        }
        return -1;
    }

    void print()
    {
        cout<<s;
    }

    ss operator + (const ss &x)
    {
        ss temp("");
        temp.s=s+x.s;
        temp.length=temp.s.size();
        return temp;
    }

};

ss Replace(ss s,ss t,ss tihuan)
{
    int index=s.find(t);
    return s.prestr(index)+tihuan+s.substr(index+t.length);
}

#endif // SS_H_INCLUDED
