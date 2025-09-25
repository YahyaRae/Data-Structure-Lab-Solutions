#include <iostream>
using namespace std;
//secret code using pointers function
void secretNum(int num){
    if (num==0){
        cout<<"The secret number is 1 "<<endl;
        
    }
    int result=1;
    int *resultptr=&result;
    for (int i = num; i>0; i--){
        *resultptr *= i;
    
    }
    cout<<"The secret number is ";
    cout<<*resultptr<<endl;

}

void (*pSecretNum)(int)=secretNum;
int main()
{
    (*pSecretNum)(4);
    return 0;
}