/*
	FIFO Page Replacement Algorithm
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

int pointer;
int faults ,hits;
// Prints the contents of the FIFO page replacement algorithm
void print(int frame_size,int frame[])
{
	int i;
	//printf("Printing the Frames: ");
	for(i=0;i<frame_size;i++)
	{
		if(frame[i]==-1)
			printf("- ");
		else
			printf("%d ",frame[i]);
	}

	printf("\n");
}

// Returns the index of the frame to be replaced
int fifo(int frame_size,int frame[],int page)
{
	int i;
	for(i=0;i<frame_size;i++)
	{
		if(frame[i]==-1)
		{
			frame[i]=page;
			return i;
		}
	}
	// If all frames are full
	// Replace the frame with the lowest index
	int min=frame[0];
	int min_index=0;
	for(i=0;i<frame_size;i++)
	{
		if(frame[i]<min)
		{
			min=frame[i];
			min_index=i;
		}
	}
	frame[min_index]=page;
	return min_index;
}
void add_reference(int frame_size,int frame[], int reference)
{
	int i;
	bool alloted = false;
	for(i=0;i<frame_size;i++)
	{
		if(frame[i]==reference)
		{
			alloted = true;
			printf("  Hit for %d | ", reference);
			hits++;
			break;
		}
		else if(frame[i]==-1)
		{
			alloted = true;
			frame[i] = reference;
			printf("Fault for %d | ", reference);
			faults++;
			break;
		}
	}
	if(alloted == false)
	{
		faults++;
		printf("Fault for %d | ", reference);
		frame[pointer] = reference;
		pointer = (pointer+1)%frame_size;
	}
	print(frame_size, frame);
}

int main()
{
	int frame_size,i,number_of_references;
	printf("Enter frame size: ");
	scanf("%d",&frame_size);
	int frame[frame_size];
	for(i=0;i<frame_size;i++)
	{
		frame[i] = -1;
	}

	print(frame_size,frame);
	
	printf("Enter the number of references: ");
	scanf("%d",&number_of_references);
	int reference[number_of_references];
	
	for(i=0;i<number_of_references;i++)
	{
		scanf("%d",&reference[i]);
		add_reference(frame_size,frame,reference[i]);
	}
	printf("\nNumber of faults: %d \nNumber of hits: %d\n",faults,hits );
}
