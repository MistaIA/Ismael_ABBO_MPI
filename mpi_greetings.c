#include <stdio.h>
#include <mpi.h>

const int MAX_STRING_SIZE = 100;

int main(void) 
{
    char    processorName[MPI_MAX_PROCESSOR_NAME];
    int commSize, myRank, nameLength;
    double startTime, endTime;

    MPI_Init(NULL, NULL);

    startTime   = MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Get_processor_name(processorName, &nameLength);

    printf("Greetings from processor %s, process rank %d of %d !", processorName, myRank, commSize);

    endTime = MPI_Wtime();

    printf(" Computed in %lf ms.\n", (endTime - startTime) * 1000);
    MPI_Finalize();
}
