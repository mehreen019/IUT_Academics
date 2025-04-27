/* Once you have compiled the application into an executable,
 * let's say `app.exe` or just `app`, you can redirect the i/o
 * by calling the application like:
 * 
 * Windows CMD:
 * app.exe < ./input.txt > ./output.txt
 * 
 * Windows Powershell:
 * Get-Content ./input.txt | ./app.exe > ./output.txt
 * 
 * Linux Shells (e.g. Bash, Zsh, sh etc.):
 * ./app < ./input.txt > ./output.txt
 * 
 * [< is used for input redirection, > for output, order does not matter]
 * [Powershell's behavior is slightly different]
 * [You can use >> instead of > to append the output to a file instead of
 * rewriting it]
 * */

#include <stdio.h>

int main(void)
{
    int val;

    // scanf by default reads from stdin which can be redirected by the parent entity
    scanf("%d", &val);

    // printf by default writes to stdout which can be redirected by the parent entity
    printf("Hello World, %d!\n", val);

    // You need to mentiond the stream/file pointer in the case of fprintf or fscanf
    fprintf(stderr, "The value (%d) has been printed.\n");
    
    return 0;
}