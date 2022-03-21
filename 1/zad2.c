#include <stdio.h>
#include <stdarg.h>
#define TINT 1

unsigned bitsNCount(unsigned count, unsigned bitscnt, ...)
{
    unsigned numOfMasks = 0;
    va_list m;
    va_start(m, count);

    int n = 0;
    
    while (n < count)
    {
        unsigned setBits = 0;
        int helper = va_arg(m, int);
        while (helper)
        {
            helper &= (helper - 1);
            setBits++;
        }
        if (setBits == bitscnt) 
        {
            numOfMasks++;
        }
        n++;
        
    }

    va_end(m);
    
    return numOfMasks;
}
int main()
{
    unsigned numberOfMasks = bitsNCount(4, 2, 0x0a, 0xff, 0, 1);
    printf("%d\n",numberOfMasks);
    numberOfMasks = bitsNCount(3, 8, 0xff, 0x13f1, 0xaaaa);
    printf("%d\n",numberOfMasks);
    numberOfMasks = bitsNCount(5, 10, 0x0a, 0xa0ff, 0, 10, 0b1010111110111);
    printf("%d\n",numberOfMasks);
    return 0;
}