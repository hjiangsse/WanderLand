#include <stdio.h>
#include <unistd.h>

int main() 
{
    int ret;

    /*
    ret = execl("/usr/bin/vim", "vim", "./test.txt",NULL);
    if(ret == -1)
    {
        perror("execl");
    }
    */

    /*
    ret = execlp("vim", "hack-vim", "./test.txt", NULL);
    if(ret == -1)
    {
        perror("execlp");
    }
    */

    const char* argv[] = {
        "path-vim",
	"./test.txt",
	NULL
    };

    ret = execvp("vim", (const char **)argv);
    if(ret == -1)
    {
	perror("execvp");
    }
}
