#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

//input and output polynomial
void polynomial(int degree, int pol[]){
	for(int i=0; i<=degree; i++){
		cout<<"Enter the coefficient of x^"<<(degree-i)<<" : ";
		cin>>pol[i];
	}
	
	cout<<endl<<"Polynomial: ";
	for(int i=0; i<=degree; i++){
		if(i == degree){
			cout<<pol[degree];
		}
		else{
			cout<<pol[i]<<"x^"<<(degree-i)<<" + ";	
		}
	}
}

//Bit stream
void bit_stream(int degree, int pol[], int bs[]){
	for(int i=0;i<=degree;i++)
    {
        if(pol[i]>0)
        {
            bs[i]=1;
        }
        else
            bs[i]=0;
    }
    cout<<endl<<endl<<"Polynomial in binary stream (Divisor): ";
    for(int i=0;i<=degree;i++)
    {
        cout<<bs[i];
    }
}

//Input and output data word
void data_word(int ndw, int dw[]){
	cout<<"Enter bits of data word: "<<endl;
	for(int i=0; i<ndw; i++){
		cin>>dw[i];
	}
	
	cout<<endl<<"Data word: ";
	for(int i=0; i<ndw; i++){
		cout<<dw[i];
	}
}

//Append 0's in data word
void append(int degree, int ndw, int dw[], int dividend[]){
	for(int i=0; i<(ndw+degree); i++){
		if(i<ndw){
			dividend[i] = dw[i];
		}
		else{
			dividend[i] = 0;
		}
	}
	
	cout<<endl<<"Dividend: ";
	for(int i=0; i<(ndw+degree); i++){
		cout<<dividend[i];
	}
}

//Division
void division(int degree, int ndw, int dividend[], int bs[], int crc[]){
	int x = 0;
	int ct=0;
	int *temp;
	temp = new int[degree+1];
	for(int i=0; i<=degree; i++){
		temp[i] = dividend[i];
		ct++;
	}
	
	for(int i=0; i<=degree; i++){
		temp[i] = temp[i]^bs[i];
	}
	for(int i=0; i<degree; i++){
		temp[i] = temp[i+1];
	}
	temp[degree] = dividend[ct];
	ct++;
	
	while(x<ndw-1){
		if(temp[0] == 0){
			for(int i=0; i<degree; i++){
				temp[i] = temp[i+1];
			}
			temp[degree] = dividend[ct];
			ct++;
			x++;
			continue;
		}
		for(int i=0; i<=degree; i++){
			temp[i] = temp[i]^bs[i];
    	}
    	for(int i=0; i<degree; i++){
			temp[i] = temp[i+1];
		}
		temp[degree] = dividend[ct];
		ct++;
		x++;
	}
	for(int i=0; i<degree; i++){
		crc[i] = temp[i];
	}
	cout<<endl<<"crc bits: ";
	for(int i=0; i<degree; i++){
		cout<<crc[i];
	}
}

//Code word
void code_word(int ndw, int degree, int dw[], int crc[], int cw[]){
	int temp=0;
	for(int i=0;i<ndw;i++){
		cw[temp++]=dw[i];
	}
	for(int i=0;i<degree;i++){
		cw[temp++]=crc[i];
	}
	
	cout<<endl<<"Code Word: ";
	for(int i=0; i<(ndw+degree); i++){
		cout<<cw[i];
	}
	cout<<endl;
}

//To Generate error
void error_generator(int cw[], int degree, int ndw){
	int  x=rand()%(degree+ndw);
	if(cw[x]==0)
		cw[x]=1;
	cout<<"The codeword recieved by user is : ";
	for(int i=0;i<(ndw+degree);i++)
	cout<<cw[i];
	cout<<endl;
	cout<<"_____________________________________";
}

//To check error
void check_error(int degree, int ndw, int dividend[], int bs[], int crc[], int cw[]){
	division(degree, ndw, cw, bs, crc);
	int flag=0;
	for(int i=0;i<degree;i++)
	{
		if(crc[i]!=0)
		{
		flag++;
		break;
		}
	}
	if(flag==0)
	cout<<"\n \n*****There's no error in the transmission*****"<<endl;
	else
	cout<<"\n \n*****There's an error in the transmission, send the codeword again*****"<<endl;
}


int main(){
	int degree, ndw;
	int *pol, *bs, *dw, *dividend, *crc, *cw;
	cout<<"Enter the degree of the polynomial: ";
	cin>>degree;
	pol = new int[degree+1];
	bs = new int[degree+1];
	polynomial(degree, pol);
	bit_stream(degree, pol, bs);
	cout<<endl<<"Enter the number of bits in data word: ";
	cin>>ndw;
	dw = new int[ndw];
	data_word(ndw, dw);
	dividend = new int(ndw+degree);
	append(degree, ndw, dw, dividend);
	crc = new int[degree];
	division(degree, ndw, dividend, bs, crc);
	cw = new int[ndw+degree];
	code_word(ndw, degree, dw, crc, cw);
	error_generator(cw, degree, ndw);
	check_error(degree, ndw, dividend, bs, crc, cw);
	cout << "\n";
	return 0;
}

