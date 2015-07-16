/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月05日 星期日 19时49分14秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
void main(void)
{
    time_t rawtime;
    struct tm *timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    printf("%s\n",asctime(timeinfo));
}
