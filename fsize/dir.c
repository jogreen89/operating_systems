#include <stdio.h>
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
    printf("Testing getchar() method\n");
    return 0;
}
