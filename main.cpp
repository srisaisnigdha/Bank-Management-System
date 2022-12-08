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
    cout << "   ----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t<><><><><><><><><><><><><  SMS BANK  ><><><><><><><><><><><><><>\t\t\t\t\t" << endl;
    cout << "   ----------------------------------------------------------------------------------------------------------------------------------------------------\n"
         << endl;
}

sqlite3 *db;
sqlite3_stmt *stmt;
int result;
string query;

void connection1();
void connection2();
void connection3();

class Printer
{
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
    void customerList();
    int checkCIF(int);
    friend class DepositAccount;
    friend class LoanAccount;
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
    void createAccount(Bank &);
    void depositMoney();
    void debitMoney();
    void showTransactions();
    double getAmount(int);
    void getHolderName();
    void getAccountType();

    void deleteDepositAccount(int account_no);
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
    double generateEMI();         // done
    string findDueDate(string a); // done
    string getDateIssued(int account_no);
    string getDueDate(int account_no); // done
    void createNewLoan(Bank &);        // done
    bool isPeriodOver(int);
    int getPeriod(int);
    void payMonthlyEMI();   // done
    void getLoanType();     // done
    void getEMI();          // done
    void getTotalLoanAmt(); // done
    void deleteLoanAccount(int);
};

int main()
{
    connection1();
    DepositAccount obj_a;
    connection2();
    Bank obj_b;
    connection3();
    LoanAccount obj_c;
    system("clear");
    cout.flush();
    sleep(2);
    header();
    int menu;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "Press [1] to enter into deposits section \n";
    cout << "Press [2] to enter into loans section \n";
    cout << "Press [3] to get accounts of given CIF \n";
    cout << "Press [4] to get given CIF details \n";
    cout << "Press [5] to get deposit list \n";
    cout << "Press [6] to get loans list \n";
    cout << "Press [7] to get customer list \n";
    cout << "Press [8] if you were a new customer to the bank \n";
    cout << "Press [9] to exit from bank \n";
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cin >> menu;
    getchar();

    switch (menu)
    {
    case 1:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        char choice1;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "Press [a] to create account \n";
        cout << "Press [b] to deposit money \n";
        cout << "Press [c] to debit money \n";
        cout << "Press [d] to get account type \n";
        cout << "Press [e] to fetch balance \n";
        cout << "Press [f] to exit from deposits section \n";
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cin >> choice1;
        getchar();

        switch (choice1)
        {
        case 'a':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_a.createAccount(obj_b);
            break;
        }
        case 'b':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_a.depositMoney();
            break;
        }
        case 'c':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_a.debitMoney();
            break;
        }
        case 'd':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_a.getAccountType();
            break;
        }
        case 'e':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            int acc;
            cout << "Enter the account number : ";
            cin >> acc;
            obj_a.getAmount(acc);
            break;
        }
        case 'f':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            cout << "Successfully exited from deposits section." << endl;
            break;
        }
        default:
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            cout << "!!Please press the valid key!!" << endl;
            break;
        }
        }
        break;
    }
    case 2:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        char choice2;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "Press [a] to create new loan \n";
        cout << "Press [b] to generate EMI \n";
        cout << "Press [c] to get due date \n";
        cout << "Press [d] to pay monthly EMI \n";
        cout << "Press [e] to get loan type \n";
        cout << "Press [f] to get EMI \n";
        cout << "Press [g] to get total loan amount \n";
        cout << "Press [h] to exit from loans section \n";
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cin >> choice2;
        getchar();

        switch (choice2)
        {
        case 'a':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_c.createNewLoan(obj_b);
            break;
        }
        case 'b':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_c.generateEMI();
            break;
        }
        case 'c':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            int acc;
            cout << "Enter the account number : ";
            cin >> acc;
            obj_c.getDueDate(acc);
            break;
        }
        case 'd':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_c.payMonthlyEMI();
            break;
        }
        case 'e':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_c.getLoanType();
            break;
        }
        case 'f':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_c.getEMI();
            break;
        }
        case 'g':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            obj_c.getTotalLoanAmt();
            break;
        }
        case 'h':
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            cout << "Successfully exited from loans section." << endl;
            break;
        }
        default:
        {
            system("clear");
            cout.flush();
            sleep(2);
            header();
            cout << "!!Please press the valid key!!" << endl;
            break;
        }
        }
        break;
    }
    case 3:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        obj_b.searchFromCIF();
        break;
    }
    case 4:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        obj_b.searchAboutCIF();
        break;
    }
    case 5:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        obj_b.depositAccounts();
        break;
    }
    case 6:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        obj_b.loanAccounts();
        break;
    }
    case 7:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        obj_b.customerList();
        break;
    }
    case 8:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        obj_b.newCustomer();
        break;
    }
    case 9:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        cout << "Successfully exited from bank." << endl;
        exit(1);
        break;
    }
    default:
    {
        system("clear");
        cout.flush();
        sleep(2);
        header();
        cout << "!!Please press the valid key!!" << endl;
        break;
    }
    }
    sqlite3_close(db);
    return 0;
}

void connection1()
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

void connection2()
{
    if (sqlite3_open("bank.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS CUSTOMERLIST(CIF INT, NAME TEXT, FATHERNAME TEXT, MOBILENO INT, ADDRESS TEXT);", -1, &stmt, NULL);
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

void connection3()
{
    if (sqlite3_open("bank.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS LOANACC(ACCNO INT, TYPE TEXT, CIF INT, DATEISSUED TEXT, EMI REAL, PERIOD INT, DUEDATE TEXT, TRANSACTIONS TEXT);", -1, &stmt, NULL);
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

void DepositAccount::createAccount(Bank &obj)
{
    char x;
    cout << "CIF Number:";
    cin >> CIF;
    if (obj.checkCIF(CIF) == 0)
    {
        cout << "The entered CIF number doesn't exist, please enter a valid CIF number!!" << endl;
        return;
    }
    account_number = generateAccountNumber();
    cout << "\nSavings Account / Current Account :(S/C) ";
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
    cout << "\nType account no. to deposit money: \n";
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
    cout << "Enter the account number to get it's account type : ";
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
            cout << "\n Data Deleted Successfully." << endl;
        }
        else
        {
            cout << "\nFailed: " << sqlite3_errmsg(db) << endl;
        }
    }
    else
    {
        cout << "Deletion Operation Stopped." << endl;
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
    string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    string number_of_days[12] = {"31", "28", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"};
    int year = stoi(yr);
    cout << year;
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        number_of_days[1] = "29";
    }
    for (int m = 0; m < 12; m++)
    {
        if (d.substr(0, 3) == month[m])
        {
            n = m + 1;
            if (m == 11)
            {
                n = 0;
                yr = to_string(year + 1);
            }
            // if dec to jan => yr needs to change............
            if (stoi(number_of_days[n]) < stoi(number_of_days[m]) && d.substr(4, 2) == number_of_days[m])
            {
                due = month[n] + ' ' + number_of_days[n] + ' ' + yr;
            }
            else
            {
                due = month[n] + d.substr(3, 4) + yr;
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
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
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
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
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
}
void LoanAccount::createNewLoan(Bank &obj)
{
    char x;
    cout << "CIF Number:";
    cin >> CIF;
    if (obj.checkCIF(CIF) == 0)
    {
        cout << "The entered CIF number doesn't exist, please enter a valid CIF number!!" << endl;
        return;
    }
    account_number = generateLoanAccountNumber();
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
    int period;
    cout << "Period:";
    cin >> period;
    cout << "Principle:";
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
        cout << "Error: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Data Inserted Successfully." << endl;
    }
}
int LoanAccount::getPeriod(int account_no)
{
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
            return sqlite3_column_int(stmt, 5);
        }
        cout << "Error. " << endl;
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
    string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int month_Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    y1 = stoi(date1.substr(7, 4));
    y2 = stoi(date2.substr(7, 4));
    for (int m = 0; m < 12; m++)
    {
        if (date1.substr(0, 3) == month[m])
        {
            m1 = m + 1;
        }
    }
    for (int m = 0; m < 12; m++)
    {
        if (date2.substr(0, 3) == month[m])
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

void LoanAccount::deleteLoanAccount(int account_no)
{
    query = "DELETE FROM LOANACC WHERE ACCNO=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, account_no);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result == SQLITE_OK)
    {
        cout << "\n Data Deleted Successfully." << endl;
    }
    else
    {
        cout << "\nFailed: " << sqlite3_errmsg(db) << endl;
    }
}
void LoanAccount::payMonthlyEMI()
{
    cout << "Account Number:";
    cin >> account_number;
    string due_date = findDueDate(getDueDate(account_number));
    query = "UPDATE LOANACC SET DUEDATE = ? WHERE ACCNO = ?;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, due_date.c_str(), due_date.length(), SQLITE_TRANSIENT);
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
        if (isPeriodOver(account_number))
        {
            deleteLoanAccount(account_number);
        }
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

    cout << "Enter the holder's father name :";
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
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(25) << "NAME"
             << setw(25) << "FATHER'S NAME"
             << setw(25) << "MOBILE NO"
             << setw(25) << "ADDRESS" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_text(stmt, 2)
                 << setw(25) << sqlite3_column_int64(stmt, 3)
                 << setw(25) << sqlite3_column_text(stmt, 4) << endl;

            return;
        }
        cout << "-------------------------------------------------------------------------------------------------" << endl;
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
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(25) << "Account number" << setw(25) << "Account type " << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1) << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------" << endl;
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
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(25) << "Account number" << setw(25) << "Account type " << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1) << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------" << endl;
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
        cout << "All the deposit accounts are : " << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(25) << "Account number"
             << setw(25) << "Account type"
             << setw(25) << "CIF"
             << setw(25) << "BALANCE " << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_int(stmt, 2)
                 << setw(25) << sqlite3_column_double(stmt, 3) << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------" << endl;
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
        cout << "All the loan accounts are : " << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(25) << "Account number"
             << setw(25) << "Account type"
             << setw(25) << "CIF"
             << setw(25) << "EMI" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_int(stmt, 2)
                 << setw(25) << sqlite3_column_double(stmt, 4) << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------" << endl;
    }
}
void Bank::customerList()
{
    query = "SELECT CIF,NAME,FATHERNAME,MOBILENO FROM CUSTOMERLIST;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "The customer list is : " << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(25) << "CIF"
             << setw(25) << "NAME"
             << setw(25) << "FATHERNAME"
             << setw(25) << "MOBILENO" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << left << setw(25) << sqlite3_column_int(stmt, 0)
                 << setw(25) << sqlite3_column_text(stmt, 1)
                 << setw(25) << sqlite3_column_text(stmt, 2)
                 << setw(25) << sqlite3_column_int64(stmt, 3) << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------" << endl;
    }
}
int Bank::checkCIF(int CIF)
{
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
            return 1;
        }
        return 0;
    }
    return 0;
}
