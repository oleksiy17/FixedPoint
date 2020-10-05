#include "fixedpoint.h"
#include "math.h"
#
int main()
{
    my_float a = 0.456;

    my_sint32 b = float_To_Fixed(a, FRACTION_BASE);
    printf("%f %d\n", a, b);

    my_uint32 logor = log2x(b, LOG_BASE);

    printf("log2x(%f) = %f\n", a, fixed_To_Float(logor, FRACTION_BASE));



    return 0;

}
