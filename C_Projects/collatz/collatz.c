
#include <stdio.h>

int collatz(int n);

int steps = 0;

int main(void)
{
    collatz(27);
    printf("%i\n",steps);
    return 0;
}

int collatz(int n)
{
    if (n == 1)
    {
        steps += 0;
        return 1;
    }
    else
        if (n % 2 == 0)
        {
            steps += 1;
            return collatz(n/2);
        }
        else
        {
            steps += 1;
            return collatz((3 * n) + 1);
        }

}