#include<iostream>
#include<stdlib.h>
#include<stdlib.h>

using namespace std;

int main()
{
	int temp1=0, temp2=0, temp3=0, temp4=0, temp5=0,i, window_size = 8, no_frames, more_frames,data_to_send[50];
	char c;
	int receiver(int);
	int simulate(int);
	int ack(int);
	cout << "\nEnter the Number of Frames: ";
	cin >> no_frames;
	cout << "\nEnter the data to send: ";
    	for(int i = 0; i < no_frames; i++){
        	int a;
        	cin >> a;
        	data_to_send[i] = a;
    	}
	more_frames = no_frames;
	while (more_frames >= 0)
	{
		temp1 = simulate(window_size);
		window_size -= temp1;
		temp4 += temp1;
		if (temp4 > no_frames)
				temp4 = no_frames;
		for (i = no_frames - more_frames; i <= temp4; i++)
				cout << "\nSending Frame " << i;
		temp2 = receiver(temp1);
		temp3 += temp2;
		if (temp3 > no_frames)
				temp3 = no_frames;
		temp2 = ack(temp1);
		temp5 += temp2;
		if (temp5 != 0)
		{
			cout << "\nNo Acknowledgement for the Frame " << temp5;
			for (i = 1; i < temp5; i++);
			cout << "\nRe-Transmitting Frame " << temp5;
		}
		more_frames -= temp1;
		if(window_size <= 0)
				window_size = 8;
	}
	cout << "\nAll Frames Successfully Transmitted!! End of Selective Repeat!!";
	cout << "\n";
	return 0;
}

int receiver(int temp1)
{
	int i;
	for (i = 1; i < 100; i++)
		rand();
	i = rand() % temp1;
	return i;
}

int ack(int temp1)
{
	int i;
	for (i = 1; i < 100; i++)
		rand();
	i = rand() % temp1;
	return i;
}

int simulate(int window_size)
{
	int temp1, i;
	for (i = 1; i < 50; i++)
		temp1 = rand();
	if(temp1 == 0)
		temp1 = simulate(window_size);
	i = temp1 % window_size;
	if (i == 0)
	{
		return window_size;
	}
	else
	{
		return temp1 % window_size;
	}
}
