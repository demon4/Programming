/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : buffer overflow v1
 * @created     : Sunday Aug 05, 2018 22:42:45 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<stdio.h>
#include<cstdio>
using namespace std;

int main() 
{
    char buf[10] = "";
    char buf1[10] = "";
    cout << "before -> buf[10] = " << buf << " -> buf1[10] = " << buf1 << endl;
    strcpy(buf, "hello i am longer than 10 characters");
    cout << "after -> buf[10, 11, 12, 13, 14] = " << buf[11] << buf[12] << buf[13] << buf[14] << " -> buf1[1, 2, 3, 10] = " << buf1[1] << buf1[2] << buf1[3] << buf[10]<< endl;
    cout << "size of buf[10] =  " << sizeof(buf) << " size of buf1[10] = " << sizeof(buf1) << endl; 
    return 0;
}

