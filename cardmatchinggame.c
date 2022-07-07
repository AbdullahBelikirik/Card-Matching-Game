#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int input(int border, int type);
int matrix(char output[8][8], int numbers[8][8], int border, int firstX, int firstY, int secondX, int secondY);
int simpleMatrix(int numbers[8][8], int border);
int body(char *difftext, int score, int pcscore, int goal, int turn);
int finish(char *difftext, int score, int pcscore, int goal, int turn,int numbers[8][8], int border, int moveCounter);
int addMemory(int memory[16][2], int memoryCap, int memoryLength, int firstX, int firstY, int secondX, int secondY);
int deleteMemory(int memory[16][2],int memoryLength, int index);

int main(int argc, char *argv[]) {
	srand(time(NULL));
	int memory[16][2], memoryLength=0, pcscore=0, score=0, control1=2, control2=0, moveCounter=0, i, j, random1, random2, tmp, diff, border, goal, userFirstX, userFirstY, userSecondX, userSecondY, pcFirstX, pcFirstY, pcSecondX, pcSecondY, memoryCap;
	char output[8][8],*difftext;
	int numbers[8][8] = {{1,1,2,2,9,9,19,19},{3,3,4,4,10,10,20,20},{5,5,6,6,11,11,21,21},{7,7,8,8,12,12,22,22},{13,13,14,14,15,15,23,23},{16,16,17,17,18,18,24,24},{25,25,26,26,27,27,28,28},{29,29,30,30,31,31,32,32}};
	char empty[8][8] = {{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '}};
	
	printf("\n\t*******CARD MATCHING GAME*******\n\n\n\tFor easy mode (16 card , Computer remembers last two moves , Goal Score : 5) type 1\n\tFor normal mode (36 card , Computer remembers last six moves , Goal Score : 10) type 2\n\tFor hard mode (64 card , Computer remembers last 16 moves , Goal Score : 17) type 3 .\n");
	
	diff = input(3,0);
	if(diff == 1){	
		difftext = "Easy";
		border = 4;
		memoryCap = 2;
	}
	else if(diff == 2)
	{
		difftext = "Normal";
		memoryCap = 6;
		border = 6;
	}
	else if(diff == 3)
	{               
		difftext = "Hard";
		border = 8;
		memoryCap = 16;
	}
	goal = (border*border/4)+1;
	
	for(i=0; i<border; i++)
	{
		for(j=0; j<border; j++)
		{
			random1 = rand()%border;
			random2 = rand()%border;
			tmp = numbers[random1][random2];
			numbers[random1][random2] = numbers[i][j];
			numbers[i][j] = tmp;
		}
	}
	
	for(i=0; i<border; i++)
	{
		for(j=0; j<border; j++)
		{
			output[i][j] = '*';
		}
	}
	
	while (((score<goal) && (pcscore<goal)) && (score+pcscore!=border*border/2))
	{	
		control1 = control1 - 2;
		if(control1 == 0)
		{
			body(difftext,score,pcscore,goal,1);
			matrix(output,numbers,border,9,9,9,9);
			
			//İlk kartın değerlerinin alınması
			userFirstX = input(border,1) - 1;
			userFirstY = input(border,2) - 1;
			while (output[userFirstX][userFirstY] == 45)
			{
				printf("\n\tYou cant open a card that already matched.");
				userFirstX = input(border, 1) - 1;
				userFirstY = input(border, 2) - 1;
			}
			
			body(difftext,score,pcscore,goal,1);
			matrix(output,numbers,border,userFirstX,userFirstY,9,9);
			
			//İkinci kartın değerlerinin alınması
			userSecondX = input(border,3) - 1;
			userSecondY = input(border,4) - 1;
			while (output[userSecondX][userSecondY] == 45)
			{
				printf("\n\tYou cant open a card that already matched.");
				userSecondX = input(border,3) - 1;
				userSecondY = input(border,4) - 1;
			}
			while ((userFirstX == userSecondX) && (userFirstY == userSecondY))
			{
				printf("\n\tYour second card has to be different than your first card.");
				userSecondX = input(border,3) - 1;
				userSecondY = input(border,4) - 1;
			}
			
			body(difftext,score,pcscore,goal,1);
			matrix(output,numbers,border,userFirstX,userFirstY,userSecondX,userSecondY);
			Sleep(1000);
			
			if(numbers[userFirstX][userFirstY] == numbers[userSecondX][userSecondY])
			{
				body(difftext,score,pcscore,goal,1);
				matrix(empty,numbers,border,userFirstX,userFirstY,userSecondX,userSecondY);
				Sleep(1500);
				printf("\n\tYou matched cards. Your turn again.\n");
				Sleep(1000);
				score++;
				output[userFirstX][userFirstY] = 45;
				output[userSecondX][userSecondY] = 45;
				control1 = 2;
				for(i=0;i<memoryLength;i++)
				{
					if(((memory[i][0] == userFirstX) && (memory[i][1] == userFirstY)) || ((memory[i][0] == userSecondX) && (memory[i][1] == userSecondY)))
					{
						deleteMemory(memory,memoryLength,i);
						memoryLength--;
						i--;
					}
				}
			}
			else
			{
				printf("\n\tYou failed. Computer's turn\n");	
				Sleep(1000);
				control1=1;
				addMemory(memory,memoryCap,memoryLength,userFirstX,userFirstY,userSecondX,userSecondY);
				if(memoryLength<memoryCap)
				{
					memoryLength+=2;
				}
				for(i=0;i<memoryLength-2;i++)
				{
					if(((memory[i][0] == userFirstX) && (memory[i][1] == userFirstY)) || ((memory[i][0] == userSecondX) && (memory[i][1] == userSecondY)))
					{
						deleteMemory(memory,memoryLength,i);
						memoryLength--;
					}
				}
			}
		moveCounter++;
		} 
		i = 0;
		if(control1 == 1)
		{
			control2 = 0;
			while((i < memoryLength-1) && (control2 == 0))
			{
				j = i+1;
				while(j < memoryLength)
				{
					if(numbers[memory[i][0]][memory[i][1]] == numbers[memory[j][0]][memory[j][1]])
					{
						pcFirstX = memory[i][0];
						pcFirstY = memory[i][1];
						pcSecondX = memory[j][0];
						pcSecondY = memory[j][1];
						control2 = 1;
						j+=16;
					}
					j++;
				}
				i++;	
			}	
			
			i = 0;
			if(control2 == 0)
			{
				pcFirstX = rand()%border;
				pcFirstY = rand()%border;
				while(output[pcFirstX][pcFirstY] == 45)
				{
					pcFirstX = rand()%border;
					pcFirstY = rand()%border;
				}
				while(i<memoryLength)
				{
					if((numbers[pcFirstX][pcFirstY] == numbers[memory[i][0]][memory[i][1]]) && !((pcFirstX == memory[i][0]) && (pcFirstY == memory[i][1])))
					{
						pcSecondX = memory[i][0];
						pcSecondY = memory[i][1];
						control2 = 1;
						i+=16;
					}
					i++;
				}
			}
		
			if(control2 == 0)
			{
				pcSecondX = rand()%border;
				pcSecondY = rand()%border;
				while((output[pcSecondX][pcSecondY] == 45) || ((pcFirstX == pcSecondX) && (pcFirstY == pcSecondY)))
				{
					pcSecondX = rand()%border;
					pcSecondY = rand()%border;
				}
			}
			
			//Bilgisayarın output işlemleri
			body(difftext,score,pcscore,goal,2);
			matrix(output,numbers,border,9,9,9,9);
			printf("\n\tComputer is making first move...\n");
			Sleep(2000);
			
			body(difftext,score,pcscore,goal,2);
			matrix(output,numbers,border,pcFirstX,pcFirstY,9,9);
			printf("\n\tComputer is making second move...\n");
			Sleep(2000);
			
			body(difftext,score,pcscore,goal,2);
			matrix(output,numbers,border,pcFirstX,pcFirstY,pcSecondX,pcSecondY);
			Sleep(2000);
	
			if(numbers[pcFirstX][pcFirstY] == numbers[pcSecondX][pcSecondY])
			{
				body(difftext,score,pcscore,goal,2);
				matrix(empty,numbers,border,pcFirstX,pcFirstY,pcSecondX,pcSecondY);
				Sleep(1500);
				printf("\n\tComputer matched cards. Computer's turn again.");
				Sleep(1000);
				pcscore++;
				output[pcFirstX][pcFirstY] = 45;
				output[pcSecondX][pcSecondY] = 45;
				control1 = 3;
				for(i=0;i<memoryLength;i++)
				{
					if(((memory[i][0] == userFirstX) && (memory[i][1] == userFirstY)) || ((memory[i][0] == userSecondX) && (memory[i][1] == userSecondY)))
					{
						deleteMemory(memory,memoryLength,i);
						memoryLength--;
						i--;
					}
				}
			}
			else
			{
				printf("\n\tComputer failed. Your turn.");
				Sleep(1000);	
				control1 = 2;
				addMemory(memory,memoryCap,memoryLength,pcFirstX,pcFirstY,pcSecondX,pcSecondY);
				if(memoryLength < memoryCap)
				{
					memoryLength+=2;
				}
			}
		}
	}
	finish(difftext,score,pcscore,goal,0,numbers,border,moveCounter);
	return 0;
}

input(int border, int type){
	int x;
	char *text;
	if (type == 0)
	{
		text = "difficulty";
	}
	else if(type == 1)
	{
		text = "first card's row";
	}
	else if(type == 2)
	{
		text = "first card's column";
	}
	else if(type == 3)
	{
		text = "second card's row";
	}
	else if(type == 4)
	{
		text = "second card's column";
	}

	printf("\n\n\tPlease write the value of %s : ",text);
	scanf("%d",&x);
	while ((x>border)||(x<1))
		{
			printf("\n\tPlease enter a value between 1 and %d.",border);
			x = input(border, type);
		}
	return x;
}
	
matrix(char output[8][8], int numbers[8][8], int border, int firstX, int firstY, int secondX, int secondY){
	int i,j;	
	for(i=0; i<border+1; i++)
	{
		printf("\t[%d]",i);
	}
	printf("\n\n");
	for(i=0; i<border; i++)
	{
		printf("\n\t[%d]",i+1);
		for(j=0; j<border; j++)
		{
			if((i==firstX)&&(j==firstY))
			{
				printf("\t %d",numbers[i][j]);
			}
			else if((i==secondX)&&(j==secondY))
			{
				printf("\t %d",numbers[i][j]);
			}
			else
			{
				printf("\t %c",output[i][j]);
			}
		}
		
		printf("\n\n");
		
	}
}	

simpleMatrix(int numbers[8][8], int border){
	int i,j;
	for(i=0; i<border; i++)
	{
		for(j=0; j<border; j++)
		{
			printf("\t%d",numbers[i][j]);
		}
		printf("\n\n");
		}
}

body(char *difftext, int score, int pcscore, int goal, int turn){
	char *notif;
	if(turn == 0)
	{
		notif = " ";
	}
	else if(turn == 1)
	{
		notif = "Player's turn";
	}
	else if(turn == 2)
	{
		notif = "Computer's turn";
	}
	
	system("cls");
	printf("\n\tPlayer Score : %d\t\tComputer Score : %d\t\tGoal Score : %d\t\tDifficulty : %s\n\n\t%s\n\n\n",score,pcscore,goal,difftext,notif);
}

finish(char *difftext, int score, int pcscore, int goal, int turn,int numbers[8][8], int border, int moveCounter){
	body(difftext,score,pcscore,goal,0);
	if(score>pcscore)
	{
		printf("\tCongrats you won. You made %d moves.\n\n\tThis is how all cards flipped :\n\n",moveCounter);
	}
	else if(score == pcscore)
	{
		printf("\tDraw . You made %d moves.\n\n\tThis is how all cards flipped :\n\n",moveCounter);
	}
	else if(pcscore>score)
	{
		printf("\tComputer won . You made %d moves.\n\n\tThis is how all cards flipped :\n\n",moveCounter);
	}
	simpleMatrix(numbers,border);
}

addMemory(int memory[16][2], int memoryCap, int memoryLength, int firstX, int firstY, int secondX, int secondY){
	int i;
	if(memoryLength<memoryCap)
	{	
		memory[memoryLength][0] = firstX ;
		memory[memoryLength][1] = firstY ;
		memoryLength++;
		memory[memoryLength][0] = secondX ;
		memory[memoryLength][1] = secondY ;
	}
	else
	{
		for(i = 0; i<memoryLength-2; i = i+2)
		{
			memory[i][0] = memory[i+2][0];
			memory[i][1] = memory[i+2][1];
			memory[i+1][0] = memory[i+3][0];
			memory[i+1][1] = memory[i+3][1];
		}
		memory[memoryLength-2][0] = firstX ;
		memory[memoryLength-2][1] = firstY ;
		memory[memoryLength-1][0] = secondX ;
		memory[memoryLength-1][1] = secondY ;
	}
}

deleteMemory(int memory[16][2],int memoryLength, int index){
	int i;	
	for(i=index; i<memoryLength; i++)
	{
		memory[i][0]=memory[i+1][0];
		memory[i][1]=memory[i+1][1];	
	}
	memory[i+1][0] = -1;
	memory[i+1][1] = -1;
}
