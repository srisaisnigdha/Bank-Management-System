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

void header()
{
  cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;            cout<<"\t\t\t\t\t<><><><><><><><><><><><>< SMS BANK ><><><><><><><><><><><><><>\t\t\t\t\t"<<endl;
  cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
}

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
        srand((unsigned)time(NULL));
        account_number = 10000 + (rand() % 90000);
        return account_number;
    }

public:
    int account_number;
    void createAccount();
    void depositMoney(); //.UPDATE
    void debitMoney();   //.UPDATE
    void showTransactions();  //*
    double getAmount(int); //.SELECT
    void getHolderName();  //*
    void getAccountType(); //.SELECT
};

class LoanAccount
{
    int CIF;
    string date, duedate;
    double emi = 1.00, principle;
    string type;
    int account_number;
    int period = 1;
    int generateLoanAccountNumber()
    {
        srand((unsigned)time(NULL));
        account_number = 10000 + (rand() % 90000);
        return account_number;
    }
    double getInterestRate()
    {
        double i;
        if (type == "GoldLoan")
        {
            i = 0.07; // rate=7%
        }
        else if (type == "PropertyLoan")
        {
            i = 0.097; // rete=9.7%
        }
        else
        {
            i = 0.01;
        }
        return i;
    }

public:
    void CreateNewLoan(); // done
    double generateEMI(); // done
    string getDueDate(int account_no);//done
    string findDueDate(string a);//done
    void payMonthlyEMI();//done
    void getLoanType();     // done
    void getEMI();          // done
    void getTotalLoanAmt(); // done
};

class Bank
{
    string name, father_name, address;
    long long int mobile_no;
    int generateCIF()
    {
        srand((unsigned)time(NULL));
        CIF = 100 + (rand() % 900);
        return CIF;
    }

public:
    int CIF;
    void newCustomer(); // GENERATE CIF()
    void searchAboutCIF();
    void searchFromCIF();   // acc num,acc type where cif=?
    void depositAccounts(); // acc num,acc tyPE,cif,balance
    void loanAccounts();    // acc num, acc type,cif,emi
    void loanAccountsDue(); //*
};

int main()
{
    //header();
    //connection();
    //DepositAccount a;
    //Bank b;
    //LoanAccount c;

    //b.newCustomer();

    // a.createAccount();
     //c.CreateNewLoan();
    //b.searchAboutCIF();
    //b.searchFromCIF();
    //b.depositAccounts();
    //b.loanAccounts();

    // a.depositMoney();
    // a.debitMoney();
    // a.getAccountType();
    // int acc = 4000;
    // a.getAmount(acc);

    //LoanAccount c;
    //c.CreateNewLoan();
    //c.getLoanType();
    //c.getEMI();
    //c.getTotalLoanAmt();
    //c.payMonthlyEMI();
    //sqlite3_close(db);
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
double LoanAccount::generateEMI()
{
    double emi_amt, i;
    i = getInterestRate();
    i = i / (12 * 100);   // one month interest
    period = period * 12; // one month period
    emi_amt = (principle * i * pow(1 + i, period)) / (pow(1 + i, period) - 1);
    return emi_amt;
}
string LoanAccount::getDueDate(int account_no)
{
    string d;
    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

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
            d= string( reinterpret_cast< const char* >(sqlite3_column_text(stmt, 6)));
            cout<<d;
            return findDueDate(d);
        }
    }
    return "";

}
string LoanAccount::findDueDate(string d)
{
string due;
    char day;
    string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    string number_of_days[12] = {"31", "28", "31", "30","31", "30", "31", "31", "30", "31", "30", "31"};
    int year=stoi(d.substr(7,8));
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){number_of_days[1]="29";}
    for(int m=0;m<12;m++){
    if(d.substr(0, 3)==month[m]){
        if(m==12){m=-1;}
        if(stoi(number_of_days[m+1])<stoi(number_of_days[m])){
            due=month[m+1]+ ' '+ number_of_days[m+1] +d.substr(6,8);}
        else{
        due=month[m+1]+d.substr(3,7);}
        break;
    }
    }
    return due;
}
void LoanAccount::CreateNewLoan()
{
    char x;
    cout << "CIF Number:";
    cin >> CIF;
    account_number = generateLoanAccountNumber() ;
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
    date = __DATE__;
    string s = "-";
    string due_date;
    int period = 1;
    cout << "Principle:";
    cin >> principle;
    emi = generateEMI();
    due_date=findDueDate(__DATE__);
    query = "INSERT INTO  LOANACC(ACCNO, TYPE, CIF,DATEISSUED,EMI,PERIOD,DUEDATE, TRANSACTIONS) VALUES(?,?,?,?,?,?,?,?);";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);
    sqlite3_bind_text(stmt, 2, type.c_str(), type.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, CIF);
    sqlite3_bind_text(stmt, 4, date.c_str(), date.length(), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 5, emi);
    sqlite3_bind_int(stmt, 6, period);
    sqlite3_bind_text(stmt, 7, due_date.c_str(), due_date.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, s.c_str(), s.length(), SQLITE_TRANSIENT);

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
void LoanAccount::payMonthlyEMI()
{
    cout << "Account Number:";
    cin >> account_number;
    string due_date=findDueDate(getDueDate(account_number));
    query = "UPDATE LOANACC SET DUEDATE = ? WHERE ACCNO = ?;";
    result=sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 7, due_date.c_str(), due_date.length(), SQLITE_TRANSIENT);
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
        }
}
void LoanAccount::getLoanType()
{
    cout << "Enter the account number to get the given account type : ";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

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
void LoanAccount::getEMI()
{
    double depo_amt;
    cout << "\n Type account to get total loan amount: \n";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

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
            cout << "your total loan amount is: " << sqlite3_column_double(stmt, 4) << endl;
            return;
        }
        cout << "The account with given account number does not exist " << endl;
    }
}
void LoanAccount::getTotalLoanAmt()
{
    double depo_amt;
    cout << "\n Type account to get total loan amount: \n";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

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
            cout << "your total loan amount is: " << (period * 12) * (sqlite3_column_double(stmt, 4)) << endl;
            return;
        }
        cout << "The account with given account number does not exist " << endl;
    }
}

void Bank::newCustomer()
{
    CIF = generateCIF();
    cout << "Enter the holder's name :";
    getline(cin, name);

    cout << "Enter the holder father's name :";
    getline(cin, father_name);

    cout << "Enter the holder's mobile number :";
    cin >> mobile_no;
    getchar();

    cout << "Enter the holder's address :";
    getline(cin, address);
    query = "INSERT INTO  CUSTOMERLIST(CIF,NAME,FATHERNAME,MOBILENO,ADDRESS) VALUES(?,?,?,?,?);";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);
    sqlite3_bind_text(stmt, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, father_name.c_str(), father_name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 4, mobile_no);
    sqlite3_bind_text(stmt, 5, address.c_str(), address.length(), SQLITE_TRANSIENT);

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
void Bank::searchAboutCIF()
{
    cout << "Enter the CIF number to search details of that CIF number : ";
    cin >> CIF;
    getchar();

    query = "SELECT * FROM CUSTOMERLIST WHERE CIF = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);

    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "Account holder name is: " << sqlite3_column_text(stmt, 1) << endl;
            cout << "Account holder father name is: " << sqlite3_column_text(stmt, 2) << endl;
            cout << "Account holder mobile number is: " << sqlite3_column_int64(stmt, 3) << endl;
            cout << "Account holder address is: " << sqlite3_column_text(stmt, 4) << endl;
            return;
        }
        cout << "The holder with given CIF number does not exist " << endl;
    }
}
void Bank::searchFromCIF()
{
    cout << "Enter the CIF number to get the available accounts of that CIF number : ";
    cin >> CIF;
    getchar();

    query = "SELECT * FROM DEPOSITACC WHERE CIF = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);

    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        // cout<<"The deposit accounts on this CIF number are : "<<endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "Account number is: " << sqlite3_column_int(stmt, 0) << " & ";
            cout << "Account type is: " << sqlite3_column_text(stmt, 1) << endl;
        }
    }

    query = "SELECT * FROM LOANACC WHERE CIF = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);

    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        // cout<<"The loan accounts on this CIF number are : "<<endl;
        cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<left<<setw(25) << "Account number" << setw(25) << "Account type "<<endl;
        cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout <<left<<setw(25) << sqlite3_column_int(stmt, 0)
                             <<setw(25) << sqlite3_column_text(stmt, 1) << endl;
        }
        cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    }
}
void Bank::depositAccounts()
{
  query = "SELECT * FROM DEPOSITACC;";
  result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

  if (result != SQLITE_OK)
  {
      cout << "ERROR: " << sqlite3_errmsg(db) << endl;
  }
  else
  {
      cout<<"All the deposit accounts are : "<<endl;
      cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
      cout<<left<<setw(25) <<"Account number"
                       <<setw(25) <<"Account type"
                       << setw(25) <<"CIF"
                       << setw(25) <<"BALANCE "<<endl;
      cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
       while (sqlite3_step(stmt) == SQLITE_ROW)
      {
          cout <<left<<setw(25)<< sqlite3_column_int(stmt, 0)
                            <<setw(25)<< sqlite3_column_text(stmt, 1)
                            <<setw(25)<< sqlite3_column_int(stmt, 2)
                            <<setw(25)<< sqlite3_column_double(stmt, 3) << endl;
      }
      cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
  }
}
void Bank::loanAccounts()
{
  query = "SELECT * FROM LOANACC;";
  result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

  if (result != SQLITE_OK)
  {
      cout << "ERROR: " << sqlite3_errmsg(db) << endl;
  }
  else
  {
      cout<<"All the loan accounts are : "<<endl;
      cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
      cout<<left<<setw(25) <<"Account number"
                       <<setw(25) <<"Account type"
                       << setw(25) <<"CIF"
                       << setw(25) <<"EMI"<<endl;
      cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
      while (sqlite3_step(stmt) == SQLITE_ROW)
      {
           cout <<left<<setw(25)<< sqlite3_column_int(stmt, 0)
                            <<setw(25)<< sqlite3_column_text(stmt, 1)
                            <<setw(25)<< sqlite3_column_int(stmt, 2)
                            <<setw(25)<< sqlite3_column_double(stmt, 4) << endl;
      }
      cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
  }
}
