#include "fixedpoint.h"
#include "math.h"
#
int main()
{
    my_float A = 0.699017;
    my_float a = 0.456;
    my_float x = 0.456;
    printf("log2(%f) = %f\n\n", a, log2f(A));

    my_sint32 b = float_To_Fixed(A, FRACTION_BASE);
    printf("%f %d\n", a, b);

    my_uint32 logor = log2x(b);

    printf("log2x(%f) = %f\n", a, fixed_To_Float(logor, LOG_BASE));

    printf("Need: %d\n", logor);
    
    my_sint32 pawer = pow2x(logor);

    printf("Pawer: %d %f\n ", pawer, fixed_To_Float(pawer, FRACTION_BASE));


    my_sint32 result = my_pow(float_To_Fixed(a, FRACTION_BASE), float_To_Fixed(x, FRACTION_BASE));
    


    /*
    float k = 0.0;

    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d, ",  float_To_Fixed(powf(2.0, k), FRACTION_BASE));
            k -= 0.0625;
        }
        printf("\n");

    }*/

    return 0;

}
