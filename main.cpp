#include <bits/stdc++.h>
#include "sqlite3.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
using namespace std;

sqlite3 *db;
sqlite3_stmt *stmt;
int result;
string query;
class Initial
{
    public:
    void connection1()
{
    if (sqlite3_open("bank.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS DEPOSITACC(ACCNO INT, TYPE TEXT, CIF INT, BALANCE REAL);", -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_OK)
        {
            cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
        }
        else
        {
            cout << "Data Inserted Successfully." << endl;
        }
    }
}

void connection2()
{
    if (sqlite3_open("bank.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS CUSTOMERLIST(CIF INT, NAME TEXT, FATHERNAME TEXT, MOBILENO INT, ADDRESS TEXT);", -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_OK)
        {
            cout << "\n\n\n\t|| ERROR : " << sqlite3_errmsg(db) << "|| \n\n\n\n" << endl;
        }
        else
        {
            cout << "Data Inserted Successfully." << endl;
        }
    }
}

void connection3()
{
    if (sqlite3_open("bank.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS LOANACC(ACCNO INT, TYPE TEXT, CIF INT, DATEISSUED TEXT, EMI REAL, PERIOD INT, DUEDATE TEXT, TRANSACTIONS TEXT);", -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_OK)
        {
            cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
        }
        else
        {
            cout << "\n\n\n\tData Inserted Successfully." << "\n\n\n\n" << endl;
        }
    }
}

};

class Printer
{
    public:
    void windowChange();
    void line1();
    void line2();
    void header();
    int menu();
    char menuForChoice1();
    char menuForChoice2();
};

class Bank: public Printer
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
    void newCustomer();
    void searchAboutCIF();
    void searchFromCIF();
    void depositAccounts();
    void loanAccounts();
    void customerList();
    int checkCIF(int);
    friend class DepositAccount;
    friend class LoanAccount;
};

class DepositAccount: Printer
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
    void createAccount(Bank &);
    void depositMoney();
    void debitMoney();
    double getAmount(int);
    void getAccountType();
    void deleteDepositAccount(int account_no);
};

class LoanAccount: public Printer
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
            i = 0.097; // rate=9.7%
        }
        else
        {
            i = 0.01;
        }
        return i;
    }

public:
    double generateEMI();
    string findDueDate(string a);
    string getDateIssued(int account_no);
    string getDueDate(int account_no);
    void fetchDueDate(int );
    void createNewLoan(Bank &);
    bool isPeriodOver(int);
    int getPeriod(int);
    void payMonthlyEMI();
    int checkAccountNumber(int);
    void getLoanType();
    void getEMI();
    void getTotalLoanAmt();
    void deleteLoanAccount(int);
};

int main()
{
    Initial z;
    Printer p;
    DepositAccount obj_a;
    Bank obj_b;
    LoanAccount obj_c;

    z.connection1();
    z.connection2();
    z.connection3();

    p.windowChange();
    int option = p.menu();

    switch (option)
    {
    case 1:
    {
        p.windowChange();
        char choice1 = p.menuForChoice1();

        switch (choice1)
        {
        case 'a':
        {
            p.windowChange();
            obj_a.createAccount(obj_b);
            break;
        }
        case 'b':
      {
              p.windowChange();
            obj_a.depositMoney();
            break;
       }
        case 'c':
      {
             p.windowChange();
           obj_a.debitMoney();
            break;
      }
        case 'd':
      {
             p.windowChange();
           obj_a.getAccountType();
            break;
      }
        case 'e':
        {
             p.windowChange();
               int acc;
            cout << "\n\tAccount Number : ";
            cin >> acc;
            obj_a.getAmount(acc);
              break;
        }
        case 'f':
        {
             p.windowChange();
            cout << "\n\n\n\t|| Exited from Deposits Section. ||" << "\n\n\n\n" << endl;
            break;
        }
        default:
        {
              p.windowChange();
            cout << "\n\n\n\t|| ERROR: INVALID INPUT. ||" << "\n\n\n\n" << endl;
            break;
        }
        }
        break;
    }
    case 2:
    {
        p.windowChange();
        char choice2 =p.menuForChoice2();

        switch (choice2)
        {
        case 'a':
        {
            p.windowChange();
            obj_c.createNewLoan(obj_b);
            break;
        }
        case 'b':
        {
            p.windowChange();
            int acc;
            cout << "\n\tAccount Number : ";
            cin >> acc;
            obj_c.fetchDueDate(acc);
            break;
        }
        case 'c':
        {
            p.windowChange();
            obj_c.payMonthlyEMI();
            break;
        }
        case 'd':
        {
            p.windowChange();
            obj_c.getLoanType();
            break;
        }
        case 'e':
        {
            p.windowChange();
            obj_c.getEMI();
            break;
        }
        case 'f':
        {
            p.windowChange();
            obj_c.getTotalLoanAmt();
            break;
        }
        case 'g':
        {
            p.windowChange();
            cout << "\n\n\n\tExited from Loans Section." << "\n\n\n\n" << endl;
            break;
        }
        default:
        {
            p.windowChange();
            cout << "\n\n\n\t|| ERROR: INVALID INPUT ||" << "\n\n\n\n" << endl;
            break;
        }
        }
        break;
    }
    case 3:
    {
        p.windowChange();
        obj_b.searchFromCIF();
        break;
    }
    case 4:
    {
        p.windowChange();
        obj_b.searchAboutCIF();
        break;
    }
    case 5:
    {
        p.windowChange();
        obj_b.depositAccounts();
        break;
    }
    case 6:
    {
        p.windowChange();
        obj_b.loanAccounts();
        break;
    }
    case 7:
    {
        p.windowChange();
        obj_b.customerList();
        break;
    }
    case 8:
    {
        p.windowChange();
        obj_b.newCustomer();
        break;
    }
    case 9:
    {
        p.windowChange();
        cout << "\n\n\n\t\t\t\t\t\t\t\t\t- THANK YOU -" << "\n\n\n\n" << endl;
        exit(1);
        break;
    }
    default:
    {
        p.windowChange();
        cout << "\n\n\n\t|| ERROR: INVALID INPUT ||" << "\n\n\n\n" << endl;
        break;
    }
    }
    sqlite3_close(db);
    return 0;
}

void Printer::windowChange()
 {
            system("clear");
            cout.flush();
            sleep(2);
            header();
 }
 void Printer::line1()
 {
 	cout << "   ----------------------------------------------------------------------------------------------------------------------------------------------------" << endl<<endl;
 }
 void Printer::line2()
 {
 	cout << "--------------------------------------------------------------------------------------------" << endl<<endl;
 }
 void Printer::header()
    {
        line1();
        cout << "\t\t\t\t\t\t<><><><><><><><><><><><    S M S BANK   ><><><><><><><><><><><>\t\t\t\t\t" << endl<<endl;
        line1();
    }
    int Printer::menu()
    {
        int option;
        cout << "  [1]\t  DEPOSITS \n\n";
        cout << "  [2]\t  LOANS \n\n";
        cout << "  [3]\t  GET ACCOUNTS FROM CIF \n\n";
        cout << "  [4]\t  GET CIF DETAILS\n\n";
        cout << "  [5]\t  DEPOSIT LIST \n\n";
        cout << "  [6]\t  LOANS LIST\n\n";
        cout << "  [7]\t  CUSTOMER LIST \n\n";
        cout << "  [8]\t  NEW CUSTOMER \n\n";
        cout << "  [9]\t  EXIT\n\n";
        cin >> option;
        getchar();
        return option;
    }
    char Printer::menuForChoice1()
    {
        char choice;
        cout << "  [a]\t  NEW ACCOUNT \n\n";
        cout << "  [b]\t  DEPOSIT MONEY \n\n";
        cout << "  [c]\t  DEBIT MONEY\n\n";
        cout << "  [d]\t  GET ACCOUNT TYPE \n\n";
        cout << "  [e]\t  FETCH BALANCE \n\n";
        cout << "  [f]\t   EXIT \n\n";
        cin >> choice;
        getchar();
         return choice;
    }
    char Printer::menuForChoice2()
    {
        char choice;
        cout << "  [a]\t  NEW LOAN\n\n";
        cout << "  [b]\t  GET DUE DATE \n\n";
        cout << "  [c]\t  PAY MONTHLY EMI\n\n";
        cout << "  [d]\t  GET LOAN TYPE\n\n";
        cout << "  [e]\t  GET EMI \n\n";
        cout << "  [f]\t   GET TOTAL LOAN AMOUNT\n\n";
        cout << "  [g]\t  EXIT\n\n";
        cin >> choice;
        getchar();
        return choice;
    }
 void Bank::newCustomer()
{
    CIF = generateCIF();
    cout << "\tEnter the Holder's Name :";
    getline(cin, name);

    cout << "\n\tEnter the Holder's Father Name :";
    getline(cin, father_name);

    cout << "\n\tEnter the Holder's Mobile Number :";
    cin >> mobile_no;
    getchar();

    cout << "\n\tEnter the Holder's Address :";
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
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        cout << "\n\n\n\tData Inserted Successfully." << "\n\n\n\n" << endl;
    }
}
void Bank::searchAboutCIF()
{
    cout << "\tCIF Number : ";
    cin >> CIF;
    getchar();

    query = "SELECT * FROM CUSTOMERLIST WHERE CIF = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        line2();
        cout << left << setw(25) << "NAME"
             << setw(25) << "FATHER'S NAME"
             << setw(25) << "MOBILE NO"
             << setw(25) << "ADDRESS" << endl;
        line2();
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_text(stmt, 2)
                 << setw(25) << sqlite3_column_int64(stmt, 3)
                 << setw(25) << sqlite3_column_text(stmt, 4) << endl;

            return;
        }
        line2();
        cout << "\n\n\n\t|| ERROR: The given CIF Number does not exist. || " << "\n\n\n\n" << endl;
    }
}
void Bank::searchFromCIF()
{
    cout << "\tCIF Number : ";
    cin >> CIF;
    getchar();

    query = "SELECT * FROM DEPOSITACC WHERE CIF = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
       cout<<"\n\tDEPOSIT ACCOUNTS : "<<endl;
        line2();
        cout << left << setw(25) << "Account number" << setw(25) << "Account type " << endl;
        line2();
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1) << endl;
        }
        line2();
    }

    query = "SELECT * FROM LOANACC WHERE CIF = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
       cout<<"\tLOAN ACCOUNTS :"<<endl;
        line2();
        cout << left << setw(25) << "Account number" << setw(25) << "Account type " << endl;
        line2();
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1) << endl;
        }
        line2();
    }
}
void Bank::depositAccounts()
{
    query = "SELECT * FROM DEPOSITACC;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "|| \n\n\n\n" << endl;
    }
    else
    {
        cout << "\tDEPOSITS LIST   : " << endl;
        line2();
        cout << left << setw(25) << "Account number"
             << setw(25) << "Account type"
             << setw(25) << "CIF"
             << setw(25) << "BALANCE " << endl;
        line2();
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_int(stmt, 2)
                 << setw(25) << sqlite3_column_double(stmt, 3) << endl;
        }
        line2();
    }
}
void Bank::loanAccounts()
{
    query = "SELECT * FROM LOANACC;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        cout << "\tLOANS LIST  : " << endl;
        line2();
        cout << left << setw(25) << "Account number"
             << setw(25) << "Account type"
             << setw(25) << "CIF"
             << setw(25) << "EMI" << endl;
        line2();
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_int(stmt, 2)
                 << setw(25) << sqlite3_column_double(stmt, 4) << endl;
        }
        line2();
    }
}
void Bank::customerList()
{
    query = "SELECT CIF,NAME,FATHERNAME,MOBILENO FROM CUSTOMERLIST;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "\n\n\n\n" << endl;
    }
    else
    {
        cout << "\tCUSTOMER LIST  : " << endl;
        line2();
        cout << left << setw(25) << "CIF"
             << setw(25) << "NAME"
             << setw(25) << "FATHERNAME"
             << setw(25) << "MOBILENO" << endl;
        line2();
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_text(stmt, 2)
                 << setw(25) << sqlite3_column_int64(stmt, 3) << endl;
        }
        line2();
    }
}
int Bank::checkCIF(int CIF)
{
    query = "SELECT * FROM CUSTOMERLIST WHERE CIF = ?;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, CIF);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

void DepositAccount::createAccount(Bank &obj)
{
    char x;
    cout << "\tCIF Number:";
    cin >> CIF;
    if (obj.checkCIF(CIF) == 0)
    {
        cout << "\n\n\n\t||  ERROR: Invalid CIF Number.  ||\n\n\n\n" << endl;
        return;
    }
    account_number = generateAccountNumber();
    cout << "\n\tSavings Account / Current Account :(S/C) ";
    cin >> x;
    if (x == 'S' || x == 's')
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
        cout << "\n\n\n\t|| Error: " << sqlite3_errmsg(db) << "||\n\n\n\n"<< endl;
    }
    else
    {
        cout << "\n\n\n\tData Inserted Successfully.\n\n\tAccount Number Generated: "<<account_number << "\n\n\n\n" << endl;
    }
}

void DepositAccount::depositMoney()
{
    double depo_amt;
    cout << "\n\tAccount Number: ";
    cin >> account_number;
    getchar();

    cout << "\n\tEnter Amount to be Deposited: ";
    cin >> depo_amt;

    double pre_bal = getAmount(account_number);
    if(pre_bal == -1)
    {
         return;
    }

    query = "UPDATE DEPOSITACC SET BALANCE = ? WHERE ACCNO = ?;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_double(stmt, 1, (depo_amt + pre_bal));
    sqlite3_bind_int(stmt, 2, account_number);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        cout << "\n\n\n\tAmount deposited Successfully." << "\n\n\n\n"<< endl;
        getAmount(account_number);
    }
}

void DepositAccount::debitMoney()
{
    double debit_amt;
    cout << "\n\tEnter the account number to Debit Money : ";
    cin >> account_number;
    getchar();

    cout << "\n\tEnter the Amount to be Debited : ";
    cin >> debit_amt;

    double pre_bal = getAmount(account_number);
    if(pre_bal==-1)
    {
    	return;
    }

    if (pre_bal < debit_amt)
    {
        cout << "\n\n\n\t|| ERROR: Debit Request can not be proceeded due to incomplete Balance. ||"<< "\n\n\n\n" << endl;
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
            cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "|| \n\n\n\n"<< endl;
        }
        else
        {
            cout << "\n\n\n\tAmount debited Successfully." << "\n\n\n\n" << endl;
            getAmount(account_number);
        }
    }
}

double DepositAccount::getAmount(int account_no)
{
    query = "SELECT * FROM DEPOSITACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_no);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            double r = sqlite3_column_double(stmt, 3);
            cout << "\n\n\n\tBalance in the account is: " << r << "\n\n\n\n" << endl;
            return r;
        }
        cout << "\n\n\n\t||ERROR: The Account does not exist || " << "\n\n\n\n" << endl;
    }
    return -1;
}
void DepositAccount::getAccountType()
{
    cout << "\tAccount Number : ";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM DEPOSITACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "|| \n\n\n\n"<< endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "\n\n\n\tAccount Type: " << sqlite3_column_text(stmt, 1) << "\n\n\n\n" << endl;
            return;
        }
        cout << "\n\n\n\t||ERROR: Account does not exist ||" << "\n\n\n\n" << endl;
    }
}
void DepositAccount::deleteDepositAccount(int account_no)
{
    char confirm;
    cout << "\t\t-CONFORMATION-\nAre You Sure? (Y/N): ";
    cin >> confirm;
    if (confirm == 'Y' || 'y')
    {
        query = "DELETE FROM DEPOSITACC WHERE ACCNO=?";
        result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, account_no);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result == SQLITE_OK)
        {
            cout << "\n\n\n\t Data Deleted Successfully." << "\n\n\n\n" << endl;
        }
        else
        {
            cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
        }
    }
    else
    {
        cout << "\n\n\n\tDeletion Operation Stopped." << "\n\n\n\n" << endl;
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

string LoanAccount::findDueDate(string d)
{
    string due = "";
    string yr = d.substr(7, 4);
    int n;
    string month[12 ]	 = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    string number_of_days[12 ]	 = {"31", "28", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"};
    int year = stoi(yr);
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        number_of_days[1 ]	 = "29";
    }
    for (int m = 0; m < 12; m++)
    {
        if (d.substr(0, 3) == month[m ]	)
        {
            n = m + 1;
            if (m == 11)
            {
                n = 0;
                yr = to_string(year + 1);
            }
            // if dec to jan => yr needs to change............
            if (stoi(number_of_days[n ]	) < stoi(number_of_days[m ]	) && d.substr(4, 2) == number_of_days[m ]	)
            {
                due = month[n ]	 + ' ' + number_of_days[n ]	 + ' ' + yr;
            }
            else
            {
                due = month[n ]	 + d.substr(3, 4) + yr;
            }
            break;
        }
        else
        {
            continue;
        }
    }
    return due;
}
string LoanAccount::getDateIssued(int account_no)
{
    string d;
    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_no);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n"<< endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            d = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
            return d;
        }
    }
    return "";
}
string LoanAccount::getDueDate(int account_no)
{
    string d;
    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_no);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
        return "";
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            d = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6)));
            return d;
        }
    }
    return 0;
}
void LoanAccount::fetchDueDate(int acc_num)
{
         if (checkAccountNumber(acc_num) == 0)
       {
            cout << "\n\n\n\t||  ERROR: Invalid Account Number.  ||\n\n\n\n" << endl;
             return;
       }
	string d=getDueDate(acc_num);
	cout<<"\n\n\n\tDue Date for payment is: "<<d<<"\n\n\n\n"<<endl;
	return;
}
void LoanAccount::createNewLoan(Bank &obj)
{
    char x;
    cout << "\tCIF Number:";
    cin >> CIF;
    if (obj.checkCIF(CIF) == 0)
    {
        cout << "\n\n\n\t|| ERROR: CIF number does not exist. ||" << "\n\n\n\n" << endl;
        return;
    }
    account_number = generateLoanAccountNumber();
    cout << "\n\tGoldLoan /  PropertyLoan:(G/P) ";
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
    int period;
    cout << "\n\tPeriod:";
    cin >> period;
    cout << "\n\tPrinciple:";
    cin >> principle;
    emi = generateEMI();
    due_date = findDueDate(__DATE__);
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
        cout << "\n\n\n\t|| Error: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        cout << "\n\n\n\tData Inserted Successfully.\n\n\tLoan Account Number: "<<account_number<<"\n\n\tEMI to be paid per month: "<<emi << "\n\n\n\n" << endl;
    }
}

bool LoanAccount::isPeriodOver(int account_no)
{
    int period = getPeriod(account_no);
    cout << period;
    int d1, m1, y1, d2, m2, y2;
    string date1, date2;
    date1 = getDateIssued(account_no);
    date2 = getDueDate(account_no);
    string month[12 ]	 = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int month_Days[12 ]	 = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    y1 = stoi(date1.substr(7, 4));
    y2 = stoi(date2.substr(7, 4));
    for (int m = 0; m < 12; m++)
    {
        if (date1.substr(0, 3) == month[m ]	)
        {
            m1 = m + 1;
        }
    }
    for (int m = 0; m < 12; m++)
    {
        if (date2.substr(0, 3) == month[m ]	)
        {
            m2 = m + 1;
        }
    }

    if (m1 < m2 && y2 - y1 >= period)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int LoanAccount::getPeriod(int account_no)
{
    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_no);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            return sqlite3_column_int(stmt, 5);
        }
        cout << "\n\n\n\t|| ERROR: Could not retrive the Data || " << "\n\n\n\n" << endl;
    }
    return 0;
}

void LoanAccount::payMonthlyEMI()
{
    cout << "\tAccount Number:";
    cin >> account_number;
     if (checkAccountNumber(account_number) == 0)
     {
          cout << "\n\n\n\t||  ERROR: Invalid Account Number.  ||\n\n\n\n" << endl;
           return;
     }
    string due_date = findDueDate(getDueDate(account_number));
    query = "UPDATE LOANACC SET DUEDATE = ? WHERE ACCNO = ?;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, due_date.c_str(), due_date.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, account_number);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        cout << "\n\n\n\tAmount Paid Successfully." << "\n\n\n\n" << endl;
        if (isPeriodOver(account_number))
        {
            deleteLoanAccount(account_number);
        }
    }
}
int LoanAccount::checkAccountNumber(int account_number)
{
    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            return 1;
        }
        return 0;
    }
    return 0;
}
void LoanAccount::getLoanType()
{
    cout << "\tEnter Account Number : ";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "\n\n\n\tLoan Type : " << sqlite3_column_text(stmt, 1) << "\n\n\n\n" << endl;
            return;
        }
        cout << "\n\n\n\t|| ERROR: Account Number does not exist. ||" << "\n\n\n\n" << endl;
    }
}
void LoanAccount::getEMI()
{
    double depo_amt;
    cout << "\n\tAccount Number : ";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "\n\n\n\tEMI : " << sqlite3_column_double(stmt, 4) << "\n\n\n\n" << endl;
            return;
        }
        cout << "\n\n\n\t|| ERROR: Account Number does not exist.||" << "\n\n\n\n" << endl;
    }
}
void LoanAccount::getTotalLoanAmt()
{
    double depo_amt;
    cout << "\n\tAccount Number : ";
    cin >> account_number;
    getchar();

    query = "SELECT * FROM LOANACC WHERE ACCNO = ?;";

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_number);

    if (result != SQLITE_OK)
    {
        cout << "\n\n\n\t|| ERROR: " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "\n\n\n\tTotal Loan Amount : " << (period * 12) * (sqlite3_column_double(stmt, 4)) << "\n\n\n\n" << endl;
            return;
        }
        cout << "\n\n\n\t|| ERROR: Account Number does not exist. ||" << "\n\n\n\n" << endl;
    }
}

void LoanAccount::deleteLoanAccount(int account_no)
{
    query = "DELETE FROM LOANACC WHERE ACCNO=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_no);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result == SQLITE_OK)
    {
        cout << "\n\n\n\tData Deleted Successfully." << "\n\n\n\n" << endl;
    }
    else
    {
        cout << "\n\n\n\tERROR : " << sqlite3_errmsg(db) << "||\n\n\n\n" << endl;
    }
}
