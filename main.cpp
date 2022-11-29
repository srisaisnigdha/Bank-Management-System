#include <bits/stdc++.h>
#include "sqlite3.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
using namespace std;
void connection();

sqlite3 *db;
sqlite3_stmt *stmt;
int result;
string query;

class Printer
{
};

class DepositAccount
{
    int CIF;
    double amount;
    string type;
    int generateAccountNumber()
    {
      srand((unsigned) time(NULL));
      account_number = 10000 + (rand() % 90000);
      return account_number;
    }
public:
    int account_number;
    void createAccount();
    void depositMoney(); //.UPDATE
    void debitMoney();   //.UPDATE
    void showTransactions();
    double getAmount(int); //.SELECT
    void getHolderName();
    void getAccountType(); //.SELECT
};

class LoanAccount
{
    int CIF;
    string date,duedate;
    double loan_amount;
    double loan_paid;
    string type;
    int account_number;
    int period;
    void generateLoanAccountNumber()
    {
    }
    double getInterestRate()
    {
        if (type == "GoldLoan")
        {
            return 0.07; // rate=7%
        }
        else if (type == "PropertyLoan")
        {
            return 0.097; // rete=9.7%
        }
    }

public:
    void CreateNewLoan();
    void generateEMI(int principle);
    void findDueDate();
    void getLoanType();
    void getTotalLoanAmt();
    void getLoanPaid();
    void getLoanOwed();
};

class Bank
{
  int generateCIF()
  {
        srand((unsigned) time(NULL));
        CIF = 100 + (rand() % 900);
        return CIF;
  }
public:
    int CIF;
    void newCustomer(); // GENERATE CIF()
    void searchAboutCIF();
    void searchFromCIF();   // acc num,acc type where cif=?
    void depositAccounts(); // acc num,acc tyPE,cif
    void loanAccounts();    // acc num, acc type,cif
    void loanAccountsDue();
};

int main()
{
    connection();
    DepositAccount a;
    // a.createAccount();
    // a.depositMoney();
    // a.debitMoney();
    a.getAccountType();
    // int acc = 4000;
    // a.getAmount(acc);
    LoanAccount b;
    b.CreateNewLoan();
    sqlite3_close(db);
    return 0;
}

void connection()
{
    if (sqlite3_open("bank.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS DEPOSITACC(ACCNO INT, TYPE TEXT, CIF INT, BALANCE REAL);", -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_OK)
        {
            cout << "Error: " << sqlite3_errmsg(db) << endl;
        }
        else
        {
            cout << "Data Inserted Successfully." << endl;
        }
    }
}

void DepositAccount::createAccount()
{
    char x;
    cout << "CIF Number:";
    cin >> CIF;
    account_number = generateAccountNumber();
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
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);
    sqlite3_bind_text(stmt, 2, type.c_str(), type.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, CIF);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_OK)
    {
        cout << "Error: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Data Inserted Successfully." << endl;
    }
}

void DepositAccount::depositMoney()
{
    double depo_amt;
    cout << "\n Type account no. to deposit money: \n";
    cin >> account_number;
    getchar();

    cout << "Enter the amount to be deposited: \n";
    cin >> depo_amt;

    double pre_bal = getAmount(account_number);

    query = "UPDATE DEPOSITACC SET BALANCE = ? WHERE ACCNO = ?;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_double(stmt, 1, (depo_amt + pre_bal));
    sqlite3_bind_int(stmt, 2, account_number);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_OK)
    {
        cout << "FAILED: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Amount deposited Successfully." << endl;
        getAmount(account_number);
    }
}

void DepositAccount::debitMoney()
{
    double debit_amt;
    cout << "\n Type account no. to debit money: \n";
    cin >> account_number;
    getchar();

    cout << "Enter the amount to be debited : \n";
    cin >> debit_amt;

    double pre_bal = getAmount(account_number);
    if (pre_bal < debit_amt)
    {
        cout << "The balance in your account is less than the amount you need to debit !!" << endl;
    }
    else
    {
        query = "UPDATE DEPOSITACC SET BALANCE = ? WHERE ACCNO = ?;";
        result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

        sqlite3_bind_double(stmt, 1, (pre_bal - debit_amt));
        sqlite3_bind_int(stmt, 2, account_number);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_OK)
        {
            cout << "FAILED: " << sqlite3_errmsg(db) << endl;
        }
        else
        {
            cout << "Amount debited Successfully." << endl;
            getAmount(account_number);
        }
    }
}

double DepositAccount::getAmount(int account_no) // ask the account number in main before calling the get amount function.
{
    query = "SELECT * FROM DEPOSITACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_no);

    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            double r = sqlite3_column_double(stmt, 3);
            cout << "The balance in your account is: " << r << endl;
            return r;
        }
        cout << "The account with given account number does not exist " << endl;
    }
    return 0;
}
void DepositAccount::getAccountType()
{
    cout << "Enter the account number to get the given account type : ";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM DEPOSITACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);

    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "your account type is: " << sqlite3_column_text(stmt, 1) << endl;
            return;
        }
        cout << "The account with given account number does not exist " << endl;
    }
}
void LoanAccount::generateEMI(int principle)
{
    double emi_amt, i;
    i = getInterestRate();
    i = i / (12 * 100);   // one month interest
    period = period * 12; // one month period
    emi_amt = (principle * i * pow(1 + i, period)) / (pow(1 + i, period) - 1);
}
void LoanAccount::findDueDate(){

}
void LoanAccount::CreateNewLoan()
{
    char x;
    cout << "CIF Number:";
    cin >> CIF;
    account_number = 13400;
    cout << "\nGoldLoan /  PropertyLoan:(G/P) ";
    cin >> x;
    if (x == 'G')
    {
        type = "GoldLoan";
    }
    else
    {
        type = "PropertyLoan";
    }
    date=__DATE__;
    string s="-";
    int period=1;
    //due_date=findDueDate();
    query = "INSERT INTO  LOANACC(ACCNO, TYPE, CIF,DATEISSUED,PERIOD,DUEDATE, TRANSACTIONS) VALUES(?,?,?,?,?,?,?);";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);
    sqlite3_bind_text(stmt, 2, type.c_str(), type.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, CIF);
    sqlite3_bind_text(stmt, 4, date.c_str(), date.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, period);
    sqlite3_bind_text(stmt, 6, date.c_str(), date.length(), SQLITE_TRANSIENT);//shouldnt be initial date
    sqlite3_bind_text(stmt, 7, s.c_str(), s.length(), SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_OK)
    {
        cout << "Error: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Data Inserted Successfully." << endl;
    }
}
void Bank::newCustomer()
{
  CIF = generateCIF();
}
