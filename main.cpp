/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-05-24 20:11:16
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
#include "login.h"
#include "datactl.h"

int main()
{
    char cmd[100];
    print();
    while(color(GREEN),(strcmp(usr,"")?printf("[cmd]%s:",usr):printf("[cmd]:"),scanf("%s",cmd)!=-1)&&strcmp(cmd,"exit")!=0)
    {
        color(WHITE);
        if (strcmp(cmd,"login")==0)
            flag=login();
            //login
        else if (strcmp(cmd,"regist")==0)
            singup();
            //regist
        else if (strcmp(cmd,"dir")==0)
        {
            if (flag==2) ulist();
            else warn();
            //show user list
        }
        else if (strcmp(cmd,"delmber")==0)
        {
            if (flag==2) del_member();
            else warn();
            //delet user
        }
        else if (strcmp(cmd,"add")==0)
        {
            if (flag==2) add();
            else warn();
            //add cities
        }
        else if (strcmp(cmd,"show")==0)
            show();
            //show city maps
        else if (strcmp(cmd,"del")==0)
        {
            if (flag==2) del();
            else warn();
            //delet cities
        }
        else if (strcmp(cmd,"help")==0)
            help(0);
        else if (strcmp(cmd,"-help")==0)
            help(1);
        else if (strcmp(cmd,"loggout")==0)
            logout();
        else if (strcmp(cmd,"require")==0)
            find_way();
        // else if (strcmp(cmd,"connect")!=0&&flag>=1)
        //     connect();
        else 
            printf("cmd:%s not defined!\n",cmd);
    }
    color(WHITE);
    return 0;
}
