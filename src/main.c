#include "fixedpoint.h"
#include "math.h"

int main()
{

    for (int i = 1; i < 500; i++)
    {
        printf("log2[%d] = %lf\n", i, log2f((float)i));
    }
   
 
    return 0;
}