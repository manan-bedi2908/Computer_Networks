#include<iostream>
#include<time.h>
#include<cstdlib>

using namespace std;

#define TIMER_MAX 5

int data_to_send[50], current = -1, dataSent = 0, timer = 0, sent_data, N;

void sender() {
  if (!dataSent) {
    current++;
    //To check if current has not gone out of bounds
    if (current >= N)
      return;

    //Start or initialize the timer     
    timer = TIMER_MAX;
    cout << "\nSender:Sent frame " << current + 1 << " with data " << data_to_send[current];
    sent_data = data_to_send[current];
    dataSent = 1;
  } else {
    // If timer has not expired, sender is waiting for acknowledgment 
    if (timer > 0) {
      cout << "\nSender:Waiting for ack";
    }

    //If timer expired, retransmit the data frame
    else {
      cout << "\nSender:Timer Expired.";
      dataSent = 0;
      current--;
    }
  }
  timer--;
}

void receiver() {
  if (dataSent) {
    int isReceived = rand() % 2;

    //If data is received, send acknowledgment 
    if (isReceived) {
      cout << "\nReceiver: Frame " << current + 1 << " with data " << sent_data << " received. Sending ack.";
      dataSent = 0;
    }
  } else {
    cout << "\nReceiver:Waiting for data.";
  }
  timer--;
}

int main() 
{
  srand(time(NULL));
  cout << "\nEnter the number of frames to send:";
  cin >> N;
  cout << "\nEnter the data to send:";
  for (int i = 0; i < N; i++) 
  {
    cin >> data_to_send[i];
  }
  while (current < N) 
  {
    int turn = rand() % 2;
    if (turn) 
    {
      sender();
    } else 
      receiver();
  }
  cout << "\n";
  return 0;
}
