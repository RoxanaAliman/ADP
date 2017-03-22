#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define n 4 // marimea matricelor
#define nthreads 4//numarul de threaduri
int a[n][n],b[n][n],c[n][n];//a*b=c

void *inmultire(void *arg) //Fiecare Thread va face aceasta functie
{
   int *p=(int *)arg;// retine data
   int i,j,k;

    for(i=*p;i<(*p+(n/nthreads));i++)//aici vad cate elemente procesez pentru fiecare thread..de la p la p+d
    for(j=0;j<n;j++)
    for(k=0;k<n;k++)
       c[i][j]=c[i][j]+a[i][k]*b[k][j];

}

int main()
{

   int i,j,rand[nthreads];
   pthread_t tid[nthreads];
   for(i=0;i<n;i++) //Elementele vor avea valoarile
      for(j=0;j<n;j++){
            a[i][j]=i+j;
            b[i][j]=i*j;

      }

   //creez thread-uri
   for(i=0;i<nthreads;i++)
   {
     rand[i]=i*(n/nthreads);
     pthread_create(&tid[i],NULL,inmultire,&rand[i]);

   }

   //thread-ul principal asteapta executia fiecareu thread(join)
   for(i=0;i<nthreads;i++)
      pthread_join(tid[i],NULL);
   for(i=0;i<n;i++){//afisez matricea
      for(j=0;j<n;j++){
         printf("%d ",c[i][j]);
       }
       printf("\n");
   }

}
