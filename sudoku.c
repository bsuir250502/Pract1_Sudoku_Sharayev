#include <stdio.h>
#include <stdlib.h>
#define N 9

int print_grid(int grid[N][N][N]);

int main()
{
  int i, j;
	int grid[N][N][N];
	FILE *fp;
	char buffer;
	fp=fopen("D:\Input.txt","r");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			grid[i][j][0]=getc(fp)-48;
		}
		getc(fp);
	}

	print_grid(grid);

	system("pause");
	return 0;
}

int print_grid(int grid[N][N][N])
{
	int i,j;
	printf(" _________________________");
	printf("\n\n");
	for(i=0;i<9;i++)
	{
		printf(" |");
		for(j=0;j<9;j++)
		{
			printf("%2d", grid[i][j][0]);
			if((j+1)%3==0) 
			{
				printf(" |");
			}
		}
		printf("\n");
		if((i+1)%3==0)
		{
			printf(" _________________________");	
			printf("\n\n");
		}
		
	}
	return 0;
}
