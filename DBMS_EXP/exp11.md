# 🗄️ Experiment 11 — SQL Subqueries with Aggregate Functions & DML

**Course:** Database Management System (UCS4001)  
**Topic:** Subqueries using AVG, MAX, MIN, COUNT, Top-N Queries & DML with Subqueries  
**CO Mapped:** CO1, CO2

---

## 📋 Objective

To perform advanced SQL operations using aggregate functions inside subqueries,
apply DML (DELETE) with subquery conditions, retrieve top-N records, and use
GROUP BY with HAVING for conditional filtering — all on the `EMPLOYEE` and
`DEPARTMENT` tables.

---

## 🛠️ Table Structure & Sample Data

### Table: EMPLOYEE

| Column   | Data Type | Size | Constraint  |
|----------|-----------|------|-------------|
| EMPNO    | NUMBER    | 4    | Primary Key |
| ENAME    | VARCHAR2  | 20   | NOT NULL    |
| JOB      | VARCHAR2  | 20   |             |
| MGR      | NUMBER    | 4    |             |
| HIREDATE | DATE      |      |             |
| SAL      | NUMBER    | 10   |             |
| COMM     | NUMBER    | 7    |             |
| DEPTNO   | NUMBER    | 2    | Foreign Key |

### Table: DEPARTMENT

| Column | Data Type | Size | Constraint  |
|--------|-----------|------|-------------|
| DEPTNO | NUMBER    | 2    | Primary Key |
| DNAME  | VARCHAR2  | 15   | NOT NULL    |
| LOC    | VARCHAR2  | 20   |             |

### Sample Data — EMPLOYEE

| EMPNO | ENAME  | JOB       | MGR  | HIREDATE  | SAL  | COMM | DEPTNO |
|-------|--------|-----------|------|-----------|------|------|--------|
| 7369  | SMITH  | CLERK     | 7902 | 17-DEC-80 | 800  |      | 20     |
| 7499  | ALLEN  | SALESMAN  | 7698 | 20-FEB-81 | 1600 | 300  | 30     |
| 7521  | WARD   | SALESMAN  | 7698 | 22-FEB-81 | 1250 | 300  | 30     |
| 7566  | JONES  | MANAGER   | 7839 | 02-APR-81 | 2975 |      | 20     |
| 7654  | MARTIN | SALESMAN  | 7698 | 28-SEP-81 | 1250 | 1400 | 30     |
| 7698  | BLAKE  | MANAGER   | 7839 | 01-MAY-81 | 2850 |      | 30     |
| 7782  | CLARK  | MANAGER   | 7839 | 09-JUN-81 | 2450 |      | 20     |
| 7788  | SCOTT  | ANALYST   | 7566 | 09-DEC-82 | 3000 |      | 40     |
| 7839  | KING   | PRESIDENT |      | 17-NOV-81 | 5000 |      | 20     |
| 7844  | TURNER | SALESMAN  | 7698 | 08-SEP-81 | 1500 | 0    | 30     |
| 7876  | ADAMS  | CLERK     | 7788 | 12-JAN-83 | 1100 |      | 20     |
| 7900  | JAMES  | CLERK     | 7698 | 03-DEC-81 | 950  |      | 30     |
| 7902  | FORD   | ANALYST   | 7566 | 03-DEC-81 | 3000 |      | 20     |
| 7934  | MILLER | CLERK     | 7782 | 23-JAN-82 | 1300 |      | 10     |

### Sample Data — DEPARTMENT

| DEPTNO | DNAME      | LOC      |
|--------|------------|----------|
| 10     | RESEARCH   | NEW YORK |
| 20     | ACCOUNTING | DALLAS   |
| 30     | SALES      | CHICAGO  |
| 40     | OPERATIONS | BOSTON   |

---

## 📝 SQL Queries with Descriptions

---

### Query 1 — Delete employees who joined before 31-DEC-82 and whose dept is in NEW YORK or CHICAGO

**Description:**  
This is a **DML DELETE with a Subquery**. The inner query fetches `DEPTNO`
values for departments located in `'NEW YORK'` or `'CHICAGO'`. The outer
`DELETE` statement removes employees who joined before 31st December 1982
**and** belong to those departments.  
> ⚠️ Run `SELECT` version first to verify rows before deleting.

```sql
-- Preview rows before deleting
SELECT ENAME, HIREDATE, DEPTNO
FROM EMPLOYEE
WHERE HIREDATE < TO_DATE('31-DEC-1982', 'DD-MON-YYYY')
  AND DEPTNO IN (
      SELECT DEPTNO
      FROM DEPARTMENT
      WHERE LOC IN ('NEW YORK', 'CHICAGO')
  );

-- DELETE query
DELETE FROM EMPLOYEE
WHERE HIREDATE < TO_DATE('31-DEC-1982', 'DD-MON-YYYY')
  AND DEPTNO IN (
      SELECT DEPTNO
      FROM DEPARTMENT
      WHERE LOC IN ('NEW YORK', 'CHICAGO')
  );

COMMIT;
```

---

### Query 2 — Display employee name, job, department name, and location for all managers

**Description:**  
This query uses an **Equi Join** between `EMPLOYEE` and `DEPARTMENT` tables.
It filters employees whose `JOB = 'MANAGER'` and retrieves their name, job,
department name, and department location using join on `DEPTNO`.

```sql
SELECT E.ENAME, E.JOB, D.DNAME, D.LOC
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
  AND E.JOB = 'MANAGER';
```

---

### Query 3 — Display name and salary of FORD if his salary equals the highest salary of his grade

**Description:**  
This query uses the `SALGRADE` table to check whether FORD's salary equals the
maximum (`HISAL`) of his grade range. If yes, his name and salary are displayed.
Without `SALGRADE`, we check if FORD's salary equals the highest in the table.

```sql
-- With SALGRADE table
SELECT E.ENAME, E.SAL
FROM EMPLOYEE E, SALGRADE S
WHERE E.ENAME = 'FORD'
  AND E.SAL BETWEEN S.LOSAL AND S.HISAL
  AND E.SAL = S.HISAL;

-- Without SALGRADE (check if FORD earns max salary overall)
SELECT ENAME, SAL
FROM EMPLOYEE
WHERE ENAME = 'FORD'
  AND SAL = (SELECT MAX(SAL) FROM EMPLOYEE);
```

---

### Query 4 — Find out the top 5 earners in the company

**Description:**  
This query retrieves the **Top-N records** by salary. In Oracle SQL, `ROWNUM`
is used to limit results after ordering by salary descending. The inner subquery
first sorts by salary; the outer query picks only top 5 rows using `ROWNUM`.

```sql
-- Oracle SQL (using ROWNUM)
SELECT ENAME, SAL
FROM (
    SELECT ENAME, SAL
    FROM EMPLOYEE
    ORDER BY SAL DESC
)
WHERE ROWNUM <= 5;

-- MySQL / Standard SQL (using LIMIT)
SELECT ENAME, SAL
FROM EMPLOYEE
ORDER BY SAL DESC
LIMIT 5;
```

---

### Query 5 — Display names of employees who earn the highest salary

**Description:**  
This is a **Single Row Subquery** using the `MAX()` function. The inner query
computes the maximum salary across the entire `EMPLOYEE` table. The outer query
returns all employees whose salary matches that maximum (handles ties).

```sql
SELECT ENAME, SAL
FROM EMPLOYEE
WHERE SAL = (SELECT MAX(SAL) FROM EMPLOYEE);
```

---

### Query 6 — Display employees whose salary equals the average of maximum and minimum salary

**Description:**  
This query uses a **Single Row Subquery** that calculates the average of the
maximum and minimum salaries: `(MAX(SAL) + MIN(SAL)) / 2`. The outer query
returns employees whose salary exactly equals this computed value.

```sql
SELECT ENAME, SAL
FROM EMPLOYEE
WHERE SAL = (
    SELECT (MAX(SAL) + MIN(SAL)) / 2
    FROM EMPLOYEE
);

-- To see the computed value
SELECT (MAX(SAL) + MIN(SAL)) / 2 AS AVG_OF_MAX_MIN
FROM EMPLOYEE;
```

---

### Query 7 — Display department names where at least 3 employees are working

**Description:**  
This query uses a **Subquery with GROUP BY and HAVING** to find departments
that have 3 or more employees. The inner query groups employees by `DEPTNO`
and filters those with `COUNT(*) >= 3`. The outer query fetches the matching
department names from the `DEPARTMENT` table.

```sql
-- Using Subquery
SELECT DNAME
FROM DEPARTMENT
WHERE DEPTNO IN (
    SELECT DEPTNO
    FROM EMPLOYEE
    GROUP BY DEPTNO
    HAVING COUNT(*) >= 3
);

-- Using JOIN with GROUP BY
SELECT D.DNAME
FROM DEPARTMENT D, EMPLOYEE E
WHERE D.DEPTNO = E.DEPTNO
GROUP BY D.DNAME
HAVING COUNT(E.EMPNO) >= 3;
```

---

### Query 8 — Display names of managers whose salary is more than the average salary of the company

**Description:**  
This query filters employees who hold `JOB = 'MANAGER'` and earn more than
the company-wide average salary. The inner subquery computes `AVG(SAL)` for
all employees. The outer query applies both the job filter and the salary
comparison.

```sql
SELECT ENAME, SAL, JOB
FROM EMPLOYEE
WHERE JOB = 'MANAGER'
  AND SAL > (SELECT AVG(SAL) FROM EMPLOYEE);
```

---

### Query 9 — Display managers whose salary is more than the average salary of their own employees

**Description:**  
This is a **Correlated Subquery**. For each manager in the outer query, the
inner query computes the average salary of employees who directly report to that
manager (`MGR = E.EMPNO`). Only managers whose own salary exceeds this average
are returned.

```sql
SELECT ENAME, SAL, EMPNO
FROM EMPLOYEE E
WHERE JOB = 'MANAGER'
  AND SAL > (
      SELECT AVG(SAL)
      FROM EMPLOYEE
      WHERE MGR = E.EMPNO
  );
```

---

### Query 10 — Employee name, salary, commission and net pay for employees whose net pay >= any other employee's salary

**Description:**  
Net pay is calculated as `SAL + NVL(COMM, 0)` (salary + commission, treating
NULL commission as 0). The inner subquery finds the maximum salary among all
employees. The outer query returns employees whose net pay is `>= ANY` salary
in the table — showing employees with the highest total compensation.

```sql
-- Net pay >= any employee's salary (net pay > minimum salary)
SELECT ENAME, SAL, NVL(COMM, 0) AS COMM,
       (SAL + NVL(COMM, 0)) AS NET_PAY
FROM EMPLOYEE
WHERE (SAL + NVL(COMM, 0)) >= ANY (
    SELECT SAL FROM EMPLOYEE
);

-- More meaningful: net pay >= maximum salary of any employee
SELECT ENAME, SAL, NVL(COMM, 0) AS COMM,
       (SAL + NVL(COMM, 0)) AS NET_PAY
FROM EMPLOYEE
WHERE (SAL + NVL(COMM, 0)) >= (
    SELECT MAX(SAL) FROM EMPLOYEE
);
```

---

## 📌 Key Concepts Used

| Concept | Description |
|---------|-------------|
| **DELETE with Subquery** | Deletes rows based on conditions derived from a subquery |
| **Top-N Query** | Retrieves top N rows using `ROWNUM` (Oracle) or `LIMIT` (MySQL) |
| **AVG()** | Aggregate function to compute average value of a column |
| **MAX() / MIN()** | Aggregate functions to find highest and lowest values |
| **COUNT()** | Counts number of rows; used with GROUP BY to count per group |
| **HAVING** | Filters grouped results based on aggregate conditions |
| **NVL()** | Oracle function to replace NULL with a default value |
| **Correlated Subquery** | Inner query re-evaluated for each row of outer query |
| **`>= ANY`** | Returns TRUE if value >= at least one value in the subquery result |

---

## ✅ Output Summary

- DML DELETE with subquery correctly targeted employees from specific locations before a date.
- Top-N query using `ROWNUM` returned the 5 highest paid employees.
- Aggregate subqueries (MAX, MIN, AVG) compared individual salaries against company statistics.
- Correlated Subquery identified managers earning more than their own team's average.
- GROUP BY with HAVING filtered departments based on minimum employee count.

---

*Experiment 11 | DBMS Lab | UCS4001*