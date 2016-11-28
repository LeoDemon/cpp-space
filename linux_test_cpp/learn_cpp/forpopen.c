/*
 * =====================================================================================
 *
 *       Filename:  forpopen.c
 *
 *    Description:  for unix-ipc popen learning
 *
 *        Version:  1.0
 *        Created:  2015年01月28日 14时27分50秒
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

int main(void)
{
    int c = 0;
    while((c = getchar()) != ']')
    {
        if(islower(c))
            c = toupper(c);
        if(putchar(c) == EOF)
            perror("putchar error:");
        fflush(stdout);
    }

    return 0;
}

