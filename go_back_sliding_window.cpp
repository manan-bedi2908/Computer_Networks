#include<iostream>
#include<cstdlib>
#include<time.h>

using namespace std;

#define WINDOW_SIZE 4

int window[WINDOW_SIZE];
int N=0;
int data_sent=0,windowStart=0,data_to_send[50];

void slideWindow(int n){
    windowStart+=n;
    for(int i=0;i<WINDOW_SIZE;i++){
        window[i] = data_to_send[windowStart+i];
    }
}

void sender(){
    if(!data_sent){
        for(int i = 0; i < WINDOW_SIZE && i + windowStart < N; i++){
            window[i] = data_to_send[i+windowStart];
            cout << "\nSender: Sent data:" << window[i];
        }
        data_sent=1;
    }
    else{
        cout << "\nSender: Waiting for Acknowledgment";
    }
}

void receiver(){
    if(data_sent){
        int i;
        srand(time(NULL));
        for(i=0;i<WINDOW_SIZE && i+windowStart<N;i++){
            int isReceived = rand() % 5;
            if(isReceived){
                cout<<"\nReceiver:Received data "<<window[i];
            }
            else{
                break;
            }
        }
        cout<<"\nReceiver:Sending cumulative ack for ";
        for(int j=0;j<i;j++){
            cout<<window[j]<<" ";
        }
        data_sent = 0;
        slideWindow(i);
    }
    else{
        cout<<"\nReceiver:Waiting for data";
    }
}



int main(){
    srand(time(NULL));
    cout << "\nEnter the number of data frames to send: ";
    cin >> N;
    cout << "\nEnter the data to send: ";
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        data_to_send[i] = a;
    }

    while(windowStart < N){
        int turn = rand() % 2;
        if(turn){
            sender();
        }
        else{
            receiver();
        }
    }
    cout << "\n";
    return 0;
}
