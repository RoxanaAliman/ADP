#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define N 10//dimenisunea vectorului
#define NUMAR 2//numarul cautat


int main(int argc, char *argv[])
{
	int proc, procid, gasit=0;
	int vector1[N]={9,8,7,6,5,4,3,2,1,0};//vectorul in care caut
	int vector2[N];//vectorul in care stochez indicii unde gasesc elementtul cautat in vectroul v1;

	MPI_Init(&argc, &argv);//initializez mpi
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);//id-ul unic al procesului curent
	MPI_Comm_size(MPI_COMM_WORLD, &proc);//nr total de procese
	


	for (int i =( N/proc)*procid; i <= (N/proc)*(procid+1)-1; i++) {//dimensiunea fiecarui segment..in functie de procese
		if (vector1[i] == NUMAR) {//daca gasesc numarul,retin indicele
			vector2[gasit] = i ;
			gasit++;//de cate ori am gasit numarul-1

		}
		
	}	
	printf("am gasit elementul de %d ori\n ",gasit);

	if (gasit==0){

		printf("nu am gasit\n");
	}
	else {

		printf("elementul %d se afla pe pozitiile:\n ", NUMAR);
		for (int j = 0; j < gasit; j++){
			printf("%d  ", vector2[j]);
		}
		printf("\n");
	
		
	}

	MPI_Finalize();//se termina programul

}