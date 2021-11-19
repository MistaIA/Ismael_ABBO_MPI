#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const int MAX_TABLE_SIZE = 25;

int GenRandoms(int, int);

int main(int argc, char* argv[]) 
{
  char processorName[MPI_MAX_PROCESSOR_NAME];
  int commSize, myRank, nameLength, elementPerProcess, elementsReceived;
  double startTime, endTime;
  // int matrixOrder = GenRandoms(2, 10);
  int matrixOrder = 4;

  printf("\n");
  int baseMatrix[matrixOrder][matrixOrder], matrix[matrixOrder][matrixOrder];
  for(int i = 0; i < matrixOrder; i++)
  {
    for(int j = 0; j < matrixOrder; j++)
    {
      matrix[i][j] = GenRandoms(0, 100);
    }
  }

  //Avoid commutation
  memcpy(baseMatrix, matrix, matrixOrder * matrixOrder * sizeof(int));

  MPI_Status status;
  MPI_Init(&argc, &argv);
  startTime   = MPI_Wtime();

  MPI_Comm_size(MPI_COMM_WORLD, &commSize);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Get_processor_name(processorName, &nameLength);

//master process
  if(myRank == 0)
  {
    int index, counter;
    elementPerProcess = matrixOrder / commSize;
    //Whether more than 1 processes are run
    if(commSize > 1)
    {
      //Dispatch to other processes
      for(counter = 1; counter < commSize - 1; counter++)
      {
        index = counter * elementPerProcess;
  
        MPI_Send(&elementPerProcess, 1, MPI_INT, counter, 0, MPI_COMM_WORLD);
        MPI_Send(&index, elementPerProcess, MPI_INT, counter, 0, MPI_COMM_WORLD);
      }

      //Get remaining tasks
      index = counter * elementPerProcess;
      int elementsLeft = matrixOrder - index;

      MPI_Send(&elementsLeft, 1, MPI_INT, counter, 0, MPI_COMM_WORLD);
      MPI_Send(&index, elementsLeft, MPI_INT, counter, 0, MPI_COMM_WORLD);
    }

//Master own operation
    for(int i = 0; i < elementPerProcess; i++)
    {
      for(int j = 0; j < matrixOrder; j++)
      {
        matrix[i][j] = (i + 2) * j;
        // printf("\t%d", matrix[i][j]);
      }
      // printf("\n\t");
    }

    //Collect partial results from other
    // int tempRows[matrixOrder];
    // for(counter = 1; counter < commSize; counter++)
    // {
    //   MPI_Recv(&tempRows, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      
    //   int sender = status.MPI_SOURCE;
      
    //   matrix[] += tempRows;
    // }
  }else{
    MPI_Recv(&elementsReceived, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  
    // Save received elements
    int tempRows[matrixOrder];
    MPI_Recv(&tempRows, elementsReceived, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    
    //job
    for(int i = 0; i < elementsReceived; i++)
    {
      for(int j = 0; j < matrixOrder; j++)
      {
        matrix[i][j] = (i + 2) * j;
      }
    }
  }
  endTime = MPI_Wtime();

  printf("processor %s, process rank %d of %d ! Computed in %lf ms.\n", processorName, myRank, commSize, (endTime - startTime) * 1000);
  MPI_Finalize();

  printf("\n\t Base matrix : \n\t");
  for(int i = 0; i < matrixOrder; i++)
  {
    for(int j = 0; j < matrixOrder; j++)
    {
      printf("\t%d", baseMatrix[i][j]);
    }
    printf("\n\t");
  }

  printf("Computed one : \n");
  for(int i = 0; i < matrixOrder; i++)
  {
    for(int j = 0; j < matrixOrder; j++)
    {
      printf("\t%d", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int GenRandoms(int lower, int upper)
{
  return (rand() % (upper - lower + 1)) + lower;
}