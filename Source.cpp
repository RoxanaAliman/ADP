#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>



#define N 10//dimenisunea vectorului
#define NUMAR 2//numarul cautat
//tema2a

int main(int argc, char *argv[])
{
	int proc, procid, gasit=0;
	int ok=0;
	int recvbuff;
	int vector1[N]={9,2,7,6,2,4,3,2,1,0};//vectorul in care caut
	//int vector2[N];vectorul in care stochez indicii unde gasesc elementtul cautat in vectroul v1;

	MPI_Init(&argc, &argv);//initializez mpi
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);//id-ul unic al procesului curent
	MPI_Comm_size(MPI_COMM_WORLD, &proc);//nr total de procese

	MPI_Bcast(vector1, N, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i =( N/proc)*procid; i <= (N/proc)*(procid+1)-1; i++) {//dimensiunea fiecarui segment..in functie de procese
		if (vector1[i] == NUMAR) {//daca gasesc numarul,retin indicele
			gasit=i;
			ok=1;

		}
		
	}	
	MPI_Reduce(&gasit, &recvbuff, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);	


	if (ok==0){

		printf("nu am gasit\n");
	}
	else {
	
		printf("elementul %d se afla pe pozitia finala %d:\n ",NUMAR, recvbuff);
	}

	MPI_Finalize();

}