
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 3                /* randuri in a */
#define NCA 3                /* coloane in a */
#define NCB 3                /* randuri in b */

int main ()
{
  int	 i, j, k;
  double	a[NRA][NCA],b[NCA][NCB],c[NRA][NCB];
	//declar un for loop paralel pentru a fi executat de thread-uri
  #pragma omp for schedule (static)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  #pragma omp for schedule (static)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  #pragma omp for schedule (static)

  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;
  //regiune paralela
  //a,b,c sunt shared intre thread-uri
  //i,j,k sunt private pentru fiecare thread
 #pragma omp parallel shared (a,b,c) private(i,j,k)
 {
   #pragma omp for schedule (static)

   for (i=0; i<NRA; i++)
     {
     for(j=0; j<NCB; j++)
       for (k=0; k<NCA; k++)
         c[i][j] += a[i][k] * b[k][j];
     }
   }
   // sfarsitul regiunii paralele

  printf("Matricea rezultat:\n");
  for (i=0; i<NRA; i++)
  {
    for (j=0; j<NCB; j++)
      printf("%f   ", c[i][j]);
  printf("\n");
  }

}
