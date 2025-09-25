#include <iostream>
using namespace std;

int main() {
    
// cafe bill using pointers

    float Espresso = 1.99;
    float Latte = 2.99;
    float Cappuccino = 3.49;

    float* pEspresso = &Espresso;
    float* pLatte = &Latte;
    float* pCappuccino = &Cappuccino;

    int EspressoCount = 0;
    int LatteCount = 0;
    int CappuccinoCount = 0;
    int* pEspressoCount = &EspressoCount;
    int* pLatteCount = &LatteCount;
    int* pCappuccinoCount = &CappuccinoCount;

    float Total = 0.0;
    float* pTotal = &Total;
    
    cout<<"Welcome to the Cafe!\n";
    cout<<"Enter the number of coffees you Want:\n";
    cout<<"Espresso ($1.99): ";
    cin>>*pEspressoCount;
    cout<<"Latte ($2.99): ";
    cin>>*pLatteCount;
    cout<<"Cappuccino ($3.49): ";
    cin>>*pCappuccinoCount;
    *pTotal = (*pEspresso * *pEspressoCount) + (*pLatte * *pLatteCount) + (*pCappuccino * *pCappuccinoCount);
    cout<<"Your total bill is: $"<<*pTotal<<"\n";
    cout<<"Thank you for visiting the Cafe!\n";
    return 0;
}