//
//  Banking_System_ver2.cpp
//  237Projects
//
//  Created by 형성모 on 2018. 12. 26..
//
//  Banking System 입니다.
//  ver2. 구조체를 클래스로 변경하고, 기존의 배열을 포인터 배열로 변경하였으며 동적할당으로 메모리사용을 최적화하였습니다.
//

#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

//전역변수
const int NAME_LEN=20;
int AccountNumberCount = 0;

//Fuction Protocol
void ShowMenu(void);
void OpenAccount(void);
void DepositMoney(void);
void WithdrawMoney(void);
void ShowAllAccount(void);

namespace MENU
{
enum {OPEN = 1, DEPOSIT, WITHDRAW, VIEW, EXIT};
}

//Class
class Account
{
private:
    int accountID;
    char *customer_name;
    int balance;
public:
    Account(int account, char *name, int money) :accountID(account), balance(money)
    {
        customer_name = new char[strlen(name)+1];
        strcpy(customer_name, name);
    }
    int GetAccount() const
    {
        return accountID;
    }
    void Deposit(int money)
    {
        balance += money;
    }
    int Withdraw(int money)
    {
        if(balance < money) return 0;
        balance -= money;
        return money;
    }
    void ShowAccount() const
    {
        cout<<"계좌번호 : "<<accountID<<endl;
        cout<<"이   름 : "<<customer_name<<endl;
        cout<<"잔   액 : "<<balance<<endl;
    }
    ~Account()
    {
        delete []customer_name;
    }
};

Account *customer[100] = {NULL};

//main
int main(void)
{
    int Select = 0;
    
    while(1)
    {
        ShowMenu();
        cout<<endl<<"메뉴를 선택해주세요.";
        cin>>Select;
        cout<<endl;
        
        switch(Select)
        {
            case MENU::OPEN:
                OpenAccount();
                break;
            case MENU::DEPOSIT:
                DepositMoney();
                break;
            case MENU::WITHDRAW:
                WithdrawMoney();
                break;
            case MENU::VIEW:
                ShowAllAccount();
                break;
            case MENU::EXIT:
                for(int i = 0; i < AccountNumberCount; i++)
                {
                    delete customer[i];
                }
                return 0;
            default:
                cout<<"다시 번호를 입력해주세요."<<endl;
        }
    }
    return 0;
}

//함수 정의
void ShowMenu(void)
{
    cout<<"-----Menu-----"<<endl;
    cout<<"1. 계좌개설"<<endl;
    cout<<"2. 입   금"<<endl;
    cout<<"3. 출   금"<<endl;
    cout<<"4. 계좌정보 전체 출력"<<endl;
    cout<<"5. 프로그램 종료"<<endl;
}

void OpenAccount(void)
{
    int myaccount = 0, mymoney = 0;
    char myname[NAME_LEN];
    
    cout<<"[계좌개설]"<<endl;
    cout<<"계좌번호 : ";
    cin>>myaccount;
    cout<<"이   름 : ";
    cin>>myname;
    cout<<"입금금액 : ";
    cin>>mymoney;
    cout<<endl;
    
    customer[AccountNumberCount++] = new Account(myaccount, myname, mymoney);
    cout<<"계좌가 성공적으로 개설되었습니다."<<endl<<endl;
    
    AccountNumberCount++;
}

void DepositMoney(void)
{
    int myaccount = 0, money = 0;
    
    cout<<"[입   금]"<<endl;
    cout<<"계좌번호 : ";
    cin>>myaccount;
    cout<<"입금금액 : ";
    cin>>money;
    cout<<endl;
    
    for(int i = 0; i < AccountNumberCount; i++)
    {
        if(customer[i]->GetAccount() == myaccount)
        {
            customer[i]->Deposit(money);
            cout<<"*입금완료"<<endl;
            return;
        }
    }
    cout<<"일치하는 계좌정보가 없습니다."<<endl;
}

void WithdrawMoney(void)
{
    int myaccount = 0, money = 0;
    
    cout<<"[출   금]"<<endl;
    cout<<"계좌번호 : ";
    cin>>myaccount;
    cout<<"출금금액 : ";
    cin>>money;
    cout<<endl;
    
    for(int i = 0; i < AccountNumberCount; i++)
    {
        if(customer[i]->GetAccount() == myaccount)
        {
            if(customer[i]->Withdraw(money) == 0)
            {
                cout<<"잔액이 부족합니다."<<endl;
                return;
            }
            cout<<"*출금완료"<<endl<<endl;
            return;
        }
    }
    cout<<"일치하는 계좌정보가 없습니다."<<endl;
}

void ShowAllAccount(void)
{
    for(int i = 0; i < AccountNumberCount; i++)
    {
        customer[i]->ShowAccount();
        cout<<endl;
    }
}
