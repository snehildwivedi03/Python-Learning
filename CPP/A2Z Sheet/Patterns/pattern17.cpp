#include<iostream>
using namespace std;


int main(){
int n;
cout<<"Enter no of rows: ";
cin>>n;
for(int i=0;i<n;i++){
  //spaces
  for(int j=0;j<n-i-1;j++){
    cout<<" ";
  }
  char ch = 'A';
  int breakpoint = (2*i+1)/2;
for(int k =0;k<2*i +1 ;k++){
    cout<<ch;
    if(k<breakpoint){
        ch++;
    }else{
        ch--;
    }
}


//spaces
  for(int j=0;j<n-i-1;j++){
    cout<<" ";
  }
  
  cout<<endl;
}
    
 
   
    


    return 0;
}


