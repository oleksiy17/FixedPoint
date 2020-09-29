#include "fixedpoint.h"
#include "math.h"

int main()
{
    my_float x = 0.875;
    printf("Float equal: %lf\n", x);

    my_sint32 y = float_To_Fixed(x);
    printf("Fixed equal: %d\n", y);

    x = fixed_To_Float(y);
    printf("Fixed - to - float:  %lf\n", x);

    return 0;

}