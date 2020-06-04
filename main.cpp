/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-06-03 11:12:46
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
#include "./headers/login.h"
#include "./headers/city.h"
#include "./headers/store.h"
#include "./headers/path.h"
#include <direct.h>

int main()
{
    char cmd[100];
    print();
    int cl=GREEN,fg=0;
    init_map();
    while(color(cl),(strcmp(usr,"")?printf("[cmd] %s:",usr):printf("[cmd]:"),scanf("%s",cmd)!=-1)&&strcmp(cmd,"exit")!=0)
    {
        color(WHITE);
        fg=0;
        if (strcmp(cmd,"login")==0)
            PERMISSION=login();
            //login
        else if (strcmp(cmd,"regist")==0)
            regist();
            //regist
        else if (strcmp(cmd,"ls_user")==0)
        {
            if (PERMISSION==2) ulist();
            else warn();
            //show user list
        }
        else if (strcmp(cmd,"del_member")==0)
        {
            if (PERMISSION==2) del_member();
            else warn();
            //delet user
        }
        else if (strcmp(cmd,"add_city")==0)
        {
            if (PERMISSION==2) add();
            else warn();
            //add cities
        }
        else if (strcmp(cmd,"add_path")==0)
        {
            if (PERMISSION==2) makeinput_by_hand();
            else warn();
        }
        else if (strcmp(cmd,"add_path_auto")==0)
        {
            if (PERMISSION==2) makeinput();
            else warn();
        }
        else if (strcmp(cmd,"ls_city")==0)
            show();
            //show city maps
        else if (strcmp(cmd,"del_city")==0)
        {
            if (PERMISSION==2) del();
            else warn();
            //delet cities
        }
        else if (strcmp(cmd,"del_path")==0)
        {
            if (PERMISSION==2) del_path();
            else warn();
        }
        else if (strcmp(cmd,"cfg")==0)
        {
            show_map();
        }
        else if (strcmp(cmd,"clean_path")==0)
            check_path();
        else if (strcmp(cmd,"ls_path")==0)
            show_path();
        else if (strcmp(cmd,"help")==0)
            help(0);
        else if (strcmp(cmd,"--help")==0)
            help(1);
        else if (strcmp(cmd,"logout")==0)
            logout(),cl=GREEN;
        else if (strcmp(cmd,"path")==0)
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
        else if (checkcmd(cmd))
        {
            if (PERMISSION==2)
            {
                char *cm=_getcwd(NULL,0);
                strcat(cmd,".exe");
                strcat(cm,"/blocks/");
                strcat(cm,cmd);
                // puts(cm);
                system(cm);
            }
            else warn();
        }
        else
            printf("cmd:%s not defined!\n",cmd);
        if (PERMISSION==2) cl=YELLOW;
        if (PERMISSION==1) cl=GREEN;
    }
    color(WHITE);
    return 0;
}
