#include "fixedpoint.h"
#include "math.h"
#
int main()
{
    my_float a = -0.1;
    my_float b = 0.2896;
    my_float c = a / b;

    my_sint32 af = float_To_Fixed(a);
    my_sint32 bf = float_To_Fixed(b);
    my_sint32 cf = div32(af, bf);

    printf("Fixed %f / %f = %f\n", a, b, fixed_To_Float(cf));

    int i = 0;
    for (int k = 0; k < 52; k++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d, ", float_To_Fixed( log2f((float)i / 512.0) ));
          
            i++;
        }
        printf("\n");
    }
    
  



    return 0;

}
