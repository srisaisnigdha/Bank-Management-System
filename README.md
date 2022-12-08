
# SMS BANK <!-- omit in toc -->

> BANK MANAGEMENT SYSTEM for organised Bank Servies in C++.


## List of Contents
- [Team Members](#team-members)
- [Introduction](#introduction)
- [Features](#features)
- [Details](#details)
- [UML Diagram](#uml-diagram)
- [How To Run](#how-to-run)
- [Sample Input-Output](#sample-input-output)
- [Sample Database](#sample-database)

## Team Members

 Kavuluru Lakshmi Srinidhi, 211117
 
 Katepalli Sri Sai Snigdha, 211114
 
 Kancharla N V L Durga Mahitha, 211113


## Introduction

This is a Bank Management System made for storing and organising the bank services.

## Features

- Each Customer gets a unique CIF Number.
- Deposit Account can be created and managed.
- Loan Account can be created and managed.
- The Accounts of a person in the Bank can be fetched.
- The Customer Details of a person can be fetched.
- The Customer List containing the Customer Details in a Bank can be accessed.
- The Deposits List containing the Deposit Accounts in a Bank can be accessed.
- The Loans List containing the Loan Accounts in a Bank can be accessed.

## Details


- The basic concepts of Object-Oriented Programming are used.

- The Data is stored & manipulated inside DataBase with the help of sqlite library.

  - sqlite : SQLite is an in-process library that implements a self-contained, serverless, zero-configuration, transactional SQL database engine.

## UML Diagram

Five Classes are declared. The Printer Class is inherited to Bank Class, LoanAccount Class and DepositAccount Class.

![1](https://user-images.githubusercontent.com/98080072/206574985-302e9445-ab21-446f-bdd7-c8ef9ca06a1d.png)

![2](https://user-images.githubusercontent.com/98080072/206573919-8085808f-c376-4ecf-bedc-a87f5d89c203.png)


## How To Run

Enter the following command to compile the main.cpp file.


```a
g++ main.cpp -l sqlite3

```
## Sample Input-Output

- Main Menu:
  
  ![6](https://user-images.githubusercontent.com/107610309/206569382-73350af6-47e3-42e5-b8be-f4ae7556b080.png)

- Deposits Menu:
  
  ![5](https://user-images.githubusercontent.com/107610309/206570095-f8fac859-c801-4b86-8b92-cefb8d5be5a2.png)
  
- Loans Menu:
  
  ![4](https://user-images.githubusercontent.com/107610309/206570301-9ee15796-a94a-4333-bc7c-9e3634e2da65.png)



## Sample Database


- Customer Table:
  
  ![Screenshot from 2022-12-09 03-17-13](https://user-images.githubusercontent.com/107610309/206575274-a5de3047-1fe1-4a70-8e7f-207adcfdbefb.png)

- Deposits Table:
  
  ![Screenshot from 2022-12-09 03-17-20](https://user-images.githubusercontent.com/107610309/206575355-d24aba84-741f-413f-b2af-895d440d588f.png)

- Loans Table:
  
  ![Screenshot from 2022-12-09 03-15-25](https://user-images.githubusercontent.com/107610309/206575426-6281e1e7-d3f8-4cc7-804d-27fdaa71e277.png)

