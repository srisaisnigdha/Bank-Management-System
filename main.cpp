#include<iostream>
#include<math.h>
#include "sqlite3.h"

using namespace std;
void connection();

enum AccountType
{
    savings_account,
    current_account
};
enum LoanType
{
    gold_loan,
    car_loan,
    house_loan,
    education_loan
};
sqlite3 *db;
sqlite3_stmt *stmt;
int result;
string query;

class Printer
{
};

class DepositAccount
{
    int account_number;
    int CIF;
    double amount;
    string type;
    int generateAccountNumber();//RANDOM
public:
    void createAccount();
    void depositMoney();//.UPDATE
    void debitMoney();//.UPDATE
    void showTransactions();
    void getAmount();//.SELECT
    void getHolderName();
    void getAccountType();//.SELECT
};

class LoanAccount
{
    double loan_amount;
    double loan_paid;
    string type;
    int account_no;
    int period;
    void generateLoanAccountNumber(){
        
    }
    double getInterestRate(){
        if (type=="GoldLoan"){
            return 0.07;// rate=7%
        }
        else if(type=="PropertyLoan"){
            return 0.097;//rete=9.7%
        }
    }
    void generateEMI(int principle){
        double emi_amt,i;
        i=getInterestRate();
        i = i / (12 * 100); // one month interest
    period = period * 12; // one month period
    emi_amt = (principle * i * pow(1 + i, period)) / (pow(1 + i, period) - 1);
    }
public:
    void CreateNewLoan();
    void getLoanType();
    void getTotalLoanAmt();
    void getLoanPaid();
    void getLoanOwed();
};

class Bank
{
    /*int generateCIF()
    {//random
    }*/

public:
    void newCustomer();//GENERATE CIF()
    void searchFromCIF();
    void searchDepositAccount();
    void searchLoanAccount();
    void getLoansByType();
    void loanAccountsDue();
};

int main()
{
    cout<<"Nidhi"<<endl;
    cout<<"Mahi"<<endl;
    connection();
    DepositAccount a;
    a.createAccount();
    a.depositMoney();
    sqlite3_close(db);
    return 0;
}

void connection()
{
    if(sqlite3_open("bank.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS DEPOSITACC(ACCNO INT, TYPE TEXT, CIF INT, BALANCE REAL);",-1,&stmt,NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result != SQLITE_OK){
            cout<<"Error: "<<sqlite3_errmsg(db)<<endl;
        }
        else
        {
            cout<<"Data Inserted Successfully."<<endl;
        }
    }
}

void DepositAccount::createAccount()
{
    char x;
     cout << "CIF Number:";
        cin >> CIF;
        account_number = 20000;
        cout << "\nSavings Account / Current Account :(S/C) ";
        cin >> x;
        if (x == 'S')
        {
            type = "SavingsAccount";
        }
        else
        {
            type = "CurrentAccount";
        }
        query = "INSERT INTO  DEPOSITACC(ACCNO, TYPE, CIF, BALANCE) VALUES(?,?,?,0);";
        result=sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, account_number);
        sqlite3_bind_text(stmt, 2, type.c_str(), type.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt,3,CIF);


        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result != SQLITE_OK){
            cout<<"Error: "<<sqlite3_errmsg(db)<<endl;
        }
        else
        {
            cout<<"Data Inserted Successfully."<<endl;
        }
}

void DepositAccount::depositMoney()
{
    int account_no;
    cout<<"\n Type account no. to deposit money: \n";
    cin>>account_no;
    getchar();

    cout<<"Enter the amount to be deposited: \n";
    cin>>amount;

    query="UPDATE DEPOSITACC SET BALANCE = ? WHERE ACCNO = ?;";
    result=sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_double(stmt,4,amount);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

        if(result != SQLITE_OK)
        {
            cout<<"FAILED: "<<sqlite3_errmsg(db)<<endl;
        }
        else
        {
            cout<<"Amount deposited Successfully."<<endl;
        }

}
