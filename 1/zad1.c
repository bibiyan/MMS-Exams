#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cylinder(double r, double h, double* V, double* S)
{
    if (r <=0 || h <=0)
    {
        fprintf(stderr, "Invalid sizes!\n");
        return -1;
    }
    *S = 2 * 3.14 * r * h + 2 * 3.14 * pow(r, 2);
    *V = 3.14 * pow(r, 2) * h;
    return 0;
}
int main()
{
    int result;
    double r, h, V, S;
    while (scanf("%lf %lf", &r, &h)!=EOF)
    {
        result = cylinder(r, h, &V, &S);
        printf("%d\n",result);
        if (result == 0)
        {
            printf("V = %.2lf, S = %.2lf\n", V, S);
        }
    }
    
    return 0;
}
