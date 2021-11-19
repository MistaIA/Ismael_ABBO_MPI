#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

//Constants
#define MAX_TABLE_SIZE 25
#define MAX_STRING_SIZE 255
#define BUFFER_SIZE 3
#define COMMAND_LINE_SIZE 17
#define MINIMUM_AMOUNT_TO_RETRIEVE 50
const int linesOfWithdrawal[11] = {503600, 400000, 300000, 200000, 100000, 80000, 50000, 25000, 13500, 10000, 6500};
const int colsOfWithdrawal[11] = {400000, 300000, 200000, 100000, 80000, 50000, 25000, 13500, 10000, 6500, 50};
//Declaration of functions
int Menu(void);
//Parallel program performance
void ParallelismPerformance();
double SpeedUp(unsigned int, unsigned int);
double Efficiency(double, unsigned int);
//Comparison between parallel and sequential code
void CompareSequentialAndParallelCode();
int GetSumOfTableEntries();
void ComputeParallelCode();
/**
 * Save old command result
 * */
void ParallelCodeExecutionResult(char*, char*, char*);
/**
* Maama Hali
**/
void GetWithdrawalBetterType();
int GetWithdrawalFees(int);
int GetWithdrawalFeesOfChunks(int, int);
/**
 * Sequential vs Parallel vs Parallel with transformation
 **/
void CompareParallelTransformationAndSequentialCode();

//Utilities
void DisplayMatrix(size_t, int**);
void MapMatrix(size_t, int**);
void ClearInputBuffer();
int GenRandoms(int, int);