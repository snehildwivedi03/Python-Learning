#include<iostream>
using namespace std;


int main(){
int n;
cout<<"Enter no of rows: ";
cin>>n;

//reverse of pattern 7


for(int i=0;i<n;i++){
 
  for(int k =0;k<=i;k++){
    cout<<" ";
  }
    for(int j=0;j<2*n-2*i-1;j++){
    cout<<"*";
  }
 
  for(int l  =0;l<=i;l++){
    cout<<" ";  
}

    cout<<endl;
}
    return 0;
}