# DBMS LAB – EXPERIMENT 1

## Aim
To create EMPLOYEE and DEPARTMENT tables and perform basic SQL operations.

## Software Used
- XAMPP
- MySQL
- VS Code

## Step 1: Start MySQL Server
- Open XAMPP Control Panel
- Click Start next to MySQL
- Ensure status shows Running

## Step 2: Open MySQL
```bash
cd C:\xampp\mysql\bin
mysql -u root
---

```md

## Step 3: Create Database
```sql
CREATE DATABASE dbms_lab;
USE dbms_lab;

---

```md
## Step 4: Create DEPARTMENT Table
```sql
CREATE TABLE DEPARTMENT (
    DEPTNO INT PRIMARY KEY,
    DNAME VARCHAR(20) NOT NULL
);

---

```md
## Step 5: Create EMPLOYEE Table
```sql
CREATE TABLE EMPLOYEE (
    EMPNO INT PRIMARY KEY,
    ENAME VARCHAR(20) NOT NULL,
    JOB VARCHAR(20),
    MGR INT,
    HIREDATE DATE,
    SAL INT,
    COMM INT,
    DEPTNO INT,
    FOREIGN KEY (DEPTNO) REFERENCES DEPARTMENT(DEPTNO)
);


---

```md
## Step 6: Insert Data into Tables
```sql
INSERT INTO DEPARTMENT VALUES (10,'RESEARCH');
INSERT INTO DEPARTMENT VALUES (20,'ACCOUNTING');
INSERT INTO DEPARTMENT VALUES (30,'SALES');
INSERT INTO DEPARTMENT VALUES (40,'OPERATIONS');


---

```md
## Step 7: Perform Required Queries
- Create EMPLOYEE_MASTER table
- Delete records of DeptNo 10
- Update salary of DeptNo 20 by 10%
- Modify salary column
- Drop EMPLOYEE_MASTER table

