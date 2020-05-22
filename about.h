/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-05-22 20:44:58
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#ifndef WHITE

#define WHITE 7
#define RED 4
#define BLUE 1
#define GREEN 2

int zxc=1;

void color(int x)	//自定义函根据参数改变颜色 
{
    if(x>=0 && x<=15)//参数在0-15的范围颜色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
    else//默认的颜色白色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void warn()
{
    color(RED);
    printf("Limited permission!\n");
    color(WHITE);
}

void print()
{
    color(BLUE);
    printf("\n\
________                ________              _____                 \n\
\\_____  \\  __ __   ____ \\______ \\   ____     /     \\ _____  ______  \n\
 /  / \\  \\|  |  \\_/ __ \\ |    |  \\_/ __ \\   /  \\ /  \\__  \\ \\____ \\ \n\
/   \\_/.  \\  |  /\\  ___/ |    `   \\  ___/  /    Y    \\/ __ \\|  |_> >\n\
\\_____\\ \\_/____/  \\___  >_______  /\\___  > \\____|__  (____  /   __/ \n\
       \\__>           \\/        \\/     \\/          \\/     \\/|__|    \n");
    printf("---------------------------------------------------------------------\n");
    printf("-----------------------------WELLCOME--------------------------------\n");
    printf("---------------------------------------------------------------------\n");
    color(WHITE);
    printf("Try entering help to learn how to do with this ^_^\n");
    return ;
}

using namespace std;
#include <iostream>
void rainbow(string str,int flg)
{
    if (zxc==8) zxc++;
    if (flg) 
    {
        color(zxc++);
    }
    // printf("%s\n",str);
    cout<<str;
        color(WHITE);
    return;
}
void help(int f)
{
    system("CLS");
    // printf("I am help!\n");
    string r1="Type \"login\" to login your account\n";
    string r2="Type \"delmber\" to delet a user\n";
    string r3="Type \"dir\" to show all users\n";
    string r4="Type \"add\" to add some now citys\n";
    string r5="Type \"del\" to delet a city\n";
    string r6="Type \"regist\" to regist some new accounts\n";
    string r7="Type \"show\" to show all the cities\n";
    rainbow(r1,f);
    rainbow(r2,f);
    rainbow(r3,f);
    rainbow(r4,f);
    rainbow(r5,f);
    rainbow("--------------------------------------\n",f);
    rainbow(r6,f);
    rainbow(r7,f);
}
#endif