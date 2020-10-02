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

    printf("%f\n", fixed_To_Float(-134217728));


    printf("%d\n", float_To_Fixed(0.456));
    /*int i = 1;
    for (int k = 0; k < 52; k++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d, ", float_To_Fixed( powf((float)2, ((float)i / 512.0)) ));
          
            i++;
        }
        printf("\n");
    }*/


    
  



    return 0;

}
