#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
//tema 2b

#define N 10//dimenisunea vectorului
#define NUMAR 2//numarul cautat


int main(int argc, char *argv[])
{
	int proc, procid, gasit=0 ;
	//int recvbuff;
	int vector1[N]={9,2,7,6,2,4,3,2,1,0};//vectorul in care caut
	int vector2[N];
	int vector3[N];//final vect
	int totalGasit=0;
	
	MPI_Init(&argc, &argv);//initializez mpi
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);//id-ul unic al procesului curent
	MPI_Comm_size(MPI_COMM_WORLD, &proc);//nr total de procese


    MPI_Scatter(vector1, N, MPI_INT, vector2, N, MPI_INT, 0, MPI_COMM_WORLD);//fiecarui proces ii trimit un segment diferit v1->v2
   // printf(" %d %d %d \n",vector2[0], vector2[1],vector2[2]);
	

   

	for (int i =( N/proc)*procid; i <= (N/proc)*(procid+1)-1; i++) {//dimensiunea fiecarui segment..in functie de procese
		if (vector1[i] == NUMAR) {//daca gasesc numarul,retin indicele
			vector2[gasit] = i ;
			cout<<"ID PROCES" <<procid <<"indice" <<i<<endl;
			gasit++;//de cate ori am gasit numarul





		}
		
	}	
	printf("gfdgdgd");
   MPI_Gather(vector2, gasit, MPI_INT,vector3, gasit, MPI_INT, 0, MPI_COMM_WORLD);//n
   if (gasit == 0)
	  {
		  printf("Nu am gasit numarul\n");
		  }
   else {
	    printf("Am gasit numarul pe pozitiile urmatoare : ");
	   for(int i = 0 ;i < 10; i++){
		  printf("%d ",vector3[i]);
	   }
   }
					
	MPI_Finalize();//se termina programul

}
				
			
		
	
	


	/*for (int i =( N/proc)*procid; i <= (N/proc)*(procid+1)-1; i++) {//dimensiunea fiecarui segment..in functie de procese
		if (vector1[i] == NUMAR) {//daca gasesc numarul,retin indicele
			vector2[gasit] = i ;
			gasit++;//de cate ori am gasit numarul-1

		}
		
	}	
	printf("Procesul %d am gasit elementul de %d ori\n ",procid, gasit);

	if (gasit==0){

		printf("nu am gasit\n");
	}
	else {

		printf("elementul %d se afla pe pozitia finala:\n ", recvbuff);
		
	
		
	}
	*/
