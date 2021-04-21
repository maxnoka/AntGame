#include <stdio.h>
#include "foo.h"
#include "bar.h"

int main(int argc, char **argv)
{
	printf("hello world\n");
    {
        bar ting;
    }
	return 0;
}
