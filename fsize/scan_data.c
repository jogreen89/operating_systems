#include <stdio.h>
#include <dirent.h>
// #include <sys.h>

/* getchar: unbuffered single character input */
int getchar(void)
{
    char c;

    // clang complains about invalid c99 declarations
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
    // return 0;
}

int main()
{
    struct dirent *de;

    DIR *dr = opendir(".");

    if (dr == NULL)
    {
        printf("Could not open current directory");
        return 1;
    }
    else
    {
        while ((de = readdir(dr)) != NULL)
        {
            printf("%s\n", de->d_name);
        }
        printf("Testing getchar() method\n");
        closedir(dr);
    }
    return 0;
}
