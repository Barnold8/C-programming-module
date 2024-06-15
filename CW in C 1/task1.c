#include <stdio.h>

unsigned int drake_equation(double R, double fp, int ne, double fl, double fi, double fe, int L){ /* All params double except n and L */
    

    return R * fp * ne * fl * fi * fe * L;

}

void printout(double R, double fp, int ne, double fl, double fi, double fe, int L){

    int N = drake_equation(R,fp,ne,fl,fi,fe,L);
    printf("N=%d R*=%0.1f fp=%0.1f ne=%d fl=%0.1f fi=%0.1f fc=%0.1f L=%d\n",N,R,fp,ne,fl,fi,fe,L);

}



int main(int argc, char** argv)
{
    printout(1.0,0.2,1,1.0,1.0,0.1,1000); 
    printout(1.0,0.5,5,1.0,1.0,0.2,1000000000);
    printout(1.5,1.0,3,1.0,0.0001,0.001,304);
    printout(3.0,1.0,5,1.0,1.0,0.1,10000000);

    return 0;    
}


