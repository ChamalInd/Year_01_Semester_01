#include <stdio.h>

#define N 2

void multiply(int A[N][N], int B[N][N], int C[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < N; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

int main()
{
	int A[N][N], B[N][N], C[N][N];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("Enter a element for A[%i][%i] : ", i, j);
			scanf("%i", &A[i][j]);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("Enter a element for B[%i][%i] : ", i, j);
			scanf("%i", &B[i][j]);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%i ", C[i][j]);
		}
		printf("\n");
	}
}
