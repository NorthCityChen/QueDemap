/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-05-26 12:54:15
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
#include "login.h"
#include "datactl.h"

int main()
{
    char cmd[100];
    print();
    int cl=GREEN;
    while(color(cl),(strcmp(usr,"")?printf("[cmd] %s:",usr):printf("[cmd]:"),scanf("%s",cmd)!=-1)&&strcmp(cmd,"exit")!=0)
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
        else if (strcmp(cmd,"logout")==0)
            logout(),cl=GREEN;
        else if (strcmp(cmd,"require")==0)
        {
            // checkfile();
            if (access(".\\dat\\loc.txt",0)==0)
                find_way();
            else
            {
                color(RED);
                printf("No \"loc.txt\" founded!\n");
                color(WHITE);
            }
        }
        else if (strcmp(cmd,"kill-la-kill")==0)
        {
            printt();
        }
        // else if (strcmp(cmd,"connect")!=0&&flag>=1)
        //     connect();
        else if (strcmp(cmd,"fetch")==0)
        {
            if (flag==2)
                system("python web.py fetch");
            else warn();
        }
        else if (strcmp(cmd,"backup")==0)
        {
            if (flag==2)
            {
                 system("python web.py upload");
                 char str[]="The backup succeed!\n";
                 cprint(str,GREEN);
            }
               
            else warn();
        }
        else 
            printf("cmd:%s not defined!\n",cmd);
        if (flag==2) cl=YELLOW;
        if (flag==1) cl=GREEN;
    }
    color(WHITE);
    return 0;
}
