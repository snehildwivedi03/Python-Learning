#include<iostream>
using namespace std;


int main(){
int n;
cout<<"Enter no of rows: ";
cin>>n;

for(int i=0;i<n;i++){
    for(int j = 0;j<=i;j++){
       cout<<j+1;
    }
 int space  = 2*n - 2*i -2;
    for(int j = 0;j<space;j++){
        cout<<" ";
    }
    for(int j = i+1;j>0;j--){
       cout<<j;
    }
    cout<<endl;
   
    
}

    return 0;
}