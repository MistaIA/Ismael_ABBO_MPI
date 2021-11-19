/**
 * @author Ismael ABBO
 * @description functions
 * @modules save old command result, format to a custom result, print new display to user
 * @version 1.00
 * */

#include "PPADLibrary.h"

//Definitions of functions

int Menu(void)
{
    // system("color 0C");//red on black
    int choice = 0;
    char choiceConfirmed;

    printf("\n\n\n\t**---------------------------------------------------------------------------**");
    printf("\n\t*                      WELCOME ! PPAD MAIN MENU OF TPs & TDs!                *\n");
    printf("\t**---------------------------------------------------------------------------**\n\n");

    printf("\n\n\t\t\t\t88   88  888888  88e   88  88  88");
    printf("\n\t\t\t\t888 888  88      88e   88  88  88");
    printf("\n\t\t\t\t88 8 88  8888    88 88 88  88e 88");
    printf("\n\t\t\t\t88   88  88      88  8888  88ee88");
    printf("\n\t\t\t\t88   88  888888  88   888  888ee8");

    printf("\n\n\t\t�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t�                1. Parallelism program performance ;          �");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t�                  2. Parallax VS Sequential code ;            �");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t�                         3. Maama Hali ;                      �");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t�        4. Parallax transformation VS Sequential code ;       �");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t�                            5. Exit ;                         �");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t�-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-�");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t� All Rights Reserved. @MistaIA-x-x-x-x- #PPAD By Dr. Tchafros �");
    printf("\n\t\tx                                                               x");
    printf("\n\t\t�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�");

    printf("\n\n\t\t\t\t Enter your choice here :  ");
    // scanf("%d", &choice);
    if(scanf("%d%c", &choice, &choiceConfirmed) != 2 || choiceConfirmed != '\n')
    {
      printf("\nPlease enter a valid choice !\n");
      return 0;
    }
    else
      return (choice);
}

void ParallelismPerformance()
{
  int decision = 1;
  // char nChar[] = "", pChar[] = "";
  unsigned int n = 0, p = 0;
  double speedUp = 0, efficiency = 0;

  printf("\n\n\n\t**-----------------------------------------------------------------------------------**");
  printf("\n\t *                            PARALLELISM PERFORMANCE !                             *\n");
  printf("\t**-----------------------------------------------------------------------------------**\n\n");

  printf("\n\t *  We ll evaluate here the speed up and the efficiency of a parallel program  *\n");
  printf("\t *    depending on the values of << n >> and << p >> that you'll enter !   *\n");

  do{
    printf("\n\t\t\t\t Enter the value of << n >> here :  ");
    scanf("%u", &n);
    // n = atoi(nChar);

    printf("\n\t\t\t\t Enter the value of << p >> here :  ");
    scanf("%u", &p);
    // p = atoi(pChar);
    ClearInputBuffer();
    printf("\n\t\t\t\t You entered as << n : %u >>, and as << p : %u >>", n, p);
    
    speedUp = SpeedUp(n, p);
    efficiency = Efficiency(speedUp, p);

    printf("\n\t\t\t\t SpeedUp = %lf \n\t\t\t\t Efficiency = %lf \n", speedUp, efficiency);
    printf("\t**-----------------------------------------------------------------------------------**\n\n");
    
    printf("\t\tEnter 1 to input another values otherwise to return up to Menu :  ");
    scanf("%d", &decision);
  }
    while(decision == 1);
}

double SpeedUp(unsigned int n, unsigned int p)
{
  int serialTime  = n * n;
  double parallaxTime = (serialTime / p) + log2(p);

  return serialTime / parallaxTime;
}

double Efficiency(double speedUp, unsigned int p)
{
  return speedUp / p;
}

void CompareSequentialAndParallelCode()
{
  int choice;

  printf("\n\n\n\t**-----------------------------------------------------------------------------------**");
  printf("\n\t  *                    EVALUATE SEQUENTIAL AND PARALLEL CODE!                        *\n");
  printf("\t**-----------------------------------------------------------------------------------**\n\n");

  do
  {
    //Timed sequential code here
    printf("\n\n\n\t---- SEQUENTIAL CODE EVALUATION \n");

    clock_t start  = clock();
    int tableSum  = GetSumOfTableEntries();
    clock_t end  = clock();
    printf("\n\t Sum = %d computed in %lf ms", tableSum, ((double)(end - start) / CLOCKS_PER_SEC) * 1000);

    //Timed parallel code here
    printf("\n\n\n\t---- PARALLEL CODE EVALUATION \n");
    
    ComputeParallelCode();

    //Restart evaluation
    printf("\n\n\tType 1 to amend, 0 otherwise here : ");
    scanf("%d", &choice);
  }
    while(1 == choice);
}

int GetSumOfTableEntries()
{
  int sizeOfTable, sum = 0;

  do
  {
    printf("\n\t Enter the number of table's elements here : ");
    scanf("%d", &sizeOfTable);

    if(MAX_TABLE_SIZE < sizeOfTable)
      printf("\n\t Size of the table must not exceed 25 !");
  }
    while(MAX_TABLE_SIZE < sizeOfTable);
  
  printf("\n");
  int tableOfIntegers[sizeOfTable];
  for(int i = 0; i < sizeOfTable; i++)
  {
    printf("\tEnter table's element no%d : ", i+1);
    scanf("%d", &tableOfIntegers[i]);

    sum += tableOfIntegers[i];
  }

  return sum;
}

void ComputeParallelCode()
{
  char linuxCommandLineResult[MAX_STRING_SIZE], fileName[MAX_STRING_SIZE] = "mpi_hello", commandLine[COMMAND_LINE_SIZE] = "mpiexec -n ";
  char processNumberChar[BUFFER_SIZE];
  int processNumber = 1;
  
  do
  {
    printf("\n\tEnter the number of process to compute here : ");
    scanf("%d", &processNumber);
    if(1 > processNumber || 99 < processNumber)
      printf("\n\tEnter a valid number between 1 and 99 !");
  }
    while(1 > processNumber || 99 < processNumber);
  snprintf(processNumberChar, BUFFER_SIZE, "%d", processNumber);
  
  printf("\tEnter the filename of the parallel code source here : ");
  scanf("%s", fileName);
  printf("\n");
  strcat(commandLine, processNumberChar);
  strcat(commandLine, " ./");

  ParallelCodeExecutionResult(linuxCommandLineResult, commandLine, fileName);
}

/**
 * Save old command result
 * */
void ParallelCodeExecutionResult(char *commandResult, char *commandLine, char *fileName)
{
  FILE *file = NULL;
  char *openFileMode = "r";

  strcat(commandLine, fileName);
  if((file = popen(commandLine, openFileMode)) == NULL)
  {
    perror("Error : ");
    exit(EXIT_FAILURE);
  }
  while(fgets(commandResult, MAX_STRING_SIZE, file) != NULL)
    printf("\t %s", commandResult);

  pclose(file);
}

/**
 * Maama Hali
*/
void GetWithdrawalBetterType()
{
  int choice;
  int amountToRetrieve, startPointIndext = 0 /*, vectorOfWithdrawalProcess[11] = {}, endPointIndex = 0*/;
  int withdrawalFees, withdrawalFeesOfChunks;

  printf("\n\n\n\t**-----------------------------------------------------------------------------------**");
  printf("\n\t  *                    EVALUATE BETTER CHOICE OF WITHDRAWAL                       *\n");
  printf("\t**-----------------------------------------------------------------------------------**\n\n");

  printf("\tWish you want to evaluate withdrawal choices (1) ?\n\n");
  printf("\t\t Enter a number here please : ");
  scanf("%d", &choice);

  do
  {
    printf("\n\tEnter the amount you want to withdraw here : ");
    scanf("%d", &amountToRetrieve);

    if(MINIMUM_AMOUNT_TO_RETRIEVE > amountToRetrieve)
    {
      printf("\n\tMinimum amount to withdraw must be : 50 FCFA.\n");
      continue;
    }

    withdrawalFees = GetWithdrawalFees(amountToRetrieve);

    for(int i = 0; i < 11; i++)
    {
      if(amountToRetrieve >= linesOfWithdrawal[i])
      {
        if(i == 10 || amountToRetrieve > linesOfWithdrawal[i])
        {
          startPointIndext = i;
        }else{
          startPointIndext = i + 1;
        }
        break;
      }
    }
    withdrawalFeesOfChunks = GetWithdrawalFeesOfChunks(startPointIndext, amountToRetrieve/*, vectorOfWithdrawalProcess*/);

    //Withdrawal of the whole amount
    printf("\n\t---- SINGLE WITHDRAWAL");
    printf("\n\tWithdrawal of %d FCFA costs %d FCFA.", amountToRetrieve, withdrawalFees);

    //Withdrawal of the whole amount
    printf("\n\t---- CHUNKS WITHDRAWAL");
    printf("\n\tWithdrawal of %d FCFA in chunks will cost %d FCFA.\n", amountToRetrieve, withdrawalFeesOfChunks);

    // int sizeOfChunks = sizeof(vectorOfWithdrawalProcess);
    // for(int i = 0; i < sizeOfChunks; i++)
    // {
    //   printf("\n\tElement no%d retrieves %d", i + 1, vectorOfWithdrawalProcess[i]);
    // }

    //Restart evaluation
    printf("\n\n\tType 1 to amend, 0 otherwise here : ");
    scanf("%d", &choice);
  }
    while(1 == choice || MINIMUM_AMOUNT_TO_RETRIEVE > amountToRetrieve);
}

int GetWithdrawalFees(int amountToRetrieve)
{
  if(50 <= amountToRetrieve && 6500 >= amountToRetrieve)
    return (3 * amountToRetrieve) / 100;

  if(6500 < amountToRetrieve && 10000 >= amountToRetrieve)
    return 180;

  if(10000 < amountToRetrieve && 13500 >= amountToRetrieve)
    return 300;

  if(13500 < amountToRetrieve && 25000 >= amountToRetrieve)
    return 350;

  if(25000 < amountToRetrieve && 50000 >= amountToRetrieve)
    return 700;

  if(50000 < amountToRetrieve && 80000 >= amountToRetrieve)
    return 1350;

  if(80000 < amountToRetrieve && 100000 >= amountToRetrieve)
    return 1800;

  if(100000 < amountToRetrieve && 200000 >= amountToRetrieve)
    return 2150;

  if(200000 < amountToRetrieve && 300000 >= amountToRetrieve)
    return 2600;

  if(300000 < amountToRetrieve && 400000 >= amountToRetrieve)
    return 3100;

  if(400000 < amountToRetrieve && 503600 >= amountToRetrieve)
    return 3600;

  return 0;
}

int GetWithdrawalFeesOfChunks(int startPointIndex, int amountToRetrieve/*, int* vectorOfWithdrawalProcess*/)
{
  int newBalance, 
    sumOfWithdrawalFees = 0, 
    j = 0, i
  ;

  if(amountToRetrieve - linesOfWithdrawal[startPointIndex] > 0)
  {
    newBalance = amountToRetrieve - linesOfWithdrawal[startPointIndex];

    sumOfWithdrawalFees += GetWithdrawalFees(linesOfWithdrawal[startPointIndex]);
    // vectorOfWithdrawalProcess[j] = linesOfWithdrawal[startPointIndex];

    if(startPointIndex + 1 >= 11 && newBalance > 0)
    {
      sumOfWithdrawalFees += GetWithdrawalFees(newBalance);
    }else{
      i = startPointIndex + 1;
      for(; i < 11;  i++)
      {
        j++;

        if(6500 >= newBalance)
        {
          sumOfWithdrawalFees += GetWithdrawalFees(newBalance);
          // vectorOfWithdrawalProcess[j] = newBalance;
          
          break;
        }else{
          newBalance -= linesOfWithdrawal[i];
          sumOfWithdrawalFees += GetWithdrawalFees(linesOfWithdrawal[i]);
          // vectorOfWithdrawalProcess[j] = linesOfWithdrawal[i];
        }
      }
    }
  }else{
    newBalance = amountToRetrieve;

    sumOfWithdrawalFees += GetWithdrawalFees(amountToRetrieve);
    // vectorOfWithdrawalProcess[j] = amountToRetrieve;
  }
  
  return sumOfWithdrawalFees;
}

/**
 * Sequential vs Parallel vs Parallel with transformation
 */
void CompareParallelTransformationAndSequentialCode()
{
  int choice;
  int matrixOrder = 4;

  printf("\n\n\n\t**---------------------------------------------------------------------------------------------**");
  printf("\n\t  *                    EVALUATE SEQUENTIAL AND PARALLEL TRANSFORMATION CODE!                  *\n");
  printf("\t**-----------------------------------------------------------------------------------------------**\n\n");

  do
  {
      //Timed sequential code here
    printf("\n\t---- SEQUENTIAL CODE EVALUATION \n");
    do
    {
      printf("\n\t Enter the order of your matrix here : ");
      scanf("%d", &matrixOrder);

      if(MAX_TABLE_SIZE < matrixOrder)
        printf("\n\t Matrix order must not exceed 25 !");
    }
      while(MAX_TABLE_SIZE < matrixOrder);
    
    printf("\n");
    int baseMatrix[matrixOrder][matrixOrder], matrix[matrixOrder][matrixOrder];
    for(int i = 0; i < matrixOrder; i++)
    {
      for(int j = 0; j < matrixOrder; j++)
      {
        printf("\tEnter row %d's column no%d : ", i+1, j+1);
        scanf("%d", &matrix[i][j]);
      }
    }

    //Avoid commutation
    memcpy(baseMatrix, matrix, matrixOrder * matrixOrder * sizeof(int));

    printf("\n\t You entered : \n\t");
    for(int i = 0; i < matrixOrder; i++)
    {
      for(int j = 0; j < matrixOrder; j++)
      {
        printf("\t%d", baseMatrix[i][j]);
      }
      printf("\n\t");
    }

    printf("\n\t Base operation is mapping : M(i, j) = (i + 2) * j.\n\t");
    clock_t start  = clock();
    for(int i = 0; i < matrixOrder; i++)
    {
      for(int j = 0; j < matrixOrder; j++)
      {
        matrix[i][j] = (i + 2) * j;
        printf("\t%d", matrix[i][j]);
      }
      printf("\n\t");
    }
    clock_t end  = clock();
    printf("\n\t Mapping of matrix computed in %lf ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000);

    //Timed parallel code here
    printf("\n\t---- PARALLEL TRANSFORMATION CODE EVALUATION \n");

    //Restart evaluation
    printf("\n\tType 1 to amend, 0 otherwise here : ");
    scanf("%d", &choice);
  }
    while(1 == choice);
}

/**
 * Utilities
 */
void DisplayMatrix(size_t matrixOrder, int** matrix)
{
  //here
}

void MapMatrix(size_t matrixOrder, int** matrix)
{
  //here
}

void ClearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }
}

int GenRandoms(int lower, int upper)
{
  return (rand() % (upper - lower + 1)) + lower;
}