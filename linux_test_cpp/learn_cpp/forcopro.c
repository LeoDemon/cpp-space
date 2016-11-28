/*
 * =====================================================================================
 *
 *       Filename:  forcopro.c
 *
 *    Description:  for test coprocess
 *
 *        Version:  1.0
 *        Created:  2015年01月30日 09时33分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LeoDemon
 *   Organization:  open-free
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int len, num1, num2;
    char ssum[100];
    memset(ssum, '\0', sizeof(ssum));
    while((len = read(STDIN_FILENO, ssum, 100)) > 0)
    {
        if(ssum[len-1] == '\n')
            ssum[len-1] = '\0';
        if(strcmp(ssum, "quit") == 0)
            break;

        if(sscanf(ssum, "%d%d", &num1, &num2) == 2)
        {
            sprintf(ssum, "%d+%d = %d\n", num1, num2, num1+num2);
            len = strlen(ssum);
            if(write(STDOUT_FILENO, ssum, len) != len)
                perror("forcopro write1 error:");
        }
        else
        {
            const char *ret = "invalid input args\n";
            len = strlen(ret);
            if(write(STDOUT_FILENO, ret, len) != len)
                perror("forcopro write2 error:");
        }
    }

    return 0;
}

