/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-06-01 22:45:39
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 

// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
//     system("python store.py");
//     return 0;
// }
#ifndef exe_files

#include <stdio.h>
#include <io.h>
#include <string.h>

#define exeNUM 20000
char exe_files[exeNUM][1000];

int getFiles()
{
	int num_of_exe = 0;
	long   hFile = 0;
	struct _finddata_t fileinfo;
	char p[700] = { 0 };
	char path[]="./blocks";
	strcpy(p, path);
	strcat(p, "\\*");
	if ((hFile = _findfirst(p, &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					continue;
			}
			else
			{
                for (int i=0;fileinfo.name[i]!='.'&&i<strlen(fileinfo.name);exe_files[num_of_exe][i]=fileinfo.name[i],i++);
                num_of_exe++;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return num_of_exe;
}

int checkcmd(char cmd[])
{
	int num=getFiles(),fg=0;
	for (int i=0;i<num;i++)
	{
		if (strcmp(cmd,exe_files[i])==0)
		{
			// char *cm=_getcwd(NULL,0);
			// strcat(cmd,".exe");
			// strcat(cm,"\\blocks\\");
			// strcat(cm,cmd);
			// system(cm);
			// fg=1;
			// break;
			return 1;
		}
	}
	return 0;
}
#endif 