# 🗄️ Experiment 10 — SQL Subqueries with ANY, ALL & Correlated Queries

**Course:** Database Management System (UCS4001)  
**Topic:** Advanced Subqueries — ANY, ALL, Correlated, Multi-table Subqueries  
**CO Mapped:** CO1, CO2

---

## 📋 Objective

To perform advanced SQL subquery operations using `ANY`, `ALL`, correlated
subqueries, and multi-table subqueries on the `EMPLOYEE` and `DEPARTMENT`
tables. These queries help in comparing values across rows and tables dynamically.

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

### Query 1 — Employees from dept 10 with salary greater than ANY employee in other departments

**Description:**  
The `> ANY` operator returns `TRUE` if the salary is greater than **at least one**
value in the subquery result. The inner query fetches all salaries of employees
**not** in department 10. The outer query returns dept 10 employees whose salary
exceeds even the minimum salary among others.  
`> ANY(list)` is equivalent to `> MIN(list)`.

```sql
SELECT ENAME, SAL, DEPTNO
FROM EMPLOYEE
WHERE DEPTNO = 10
  AND SAL > ANY (
      SELECT SAL
      FROM EMPLOYEE
      WHERE DEPTNO != 10
  );
```

---

### Query 2 — Employees from dept 10 with salary greater than ALL employees in other departments

**Description:**  
The `> ALL` operator returns `TRUE` only if the salary is greater than **every**
value in the subquery result. The inner query fetches all salaries of employees
not in department 10. Only dept 10 employees earning more than all of them
are returned. `> ALL(list)` is equivalent to `> MAX(list)`.

```sql
SELECT ENAME, SAL, DEPTNO
FROM EMPLOYEE
WHERE DEPTNO = 10
  AND SAL > ALL (
      SELECT SAL
      FROM EMPLOYEE
      WHERE DEPTNO != 10
  );
```

---

### Query 3 — Details of employees in SALES department with grade 3

**Description:**  
This query joins the `EMPLOYEE` table with the `DEPARTMENT` table using a
subquery to filter employees from the `'SALES'` department. Grade 3 corresponds
to the salary range 1401–2000 (from standard Oracle SALGRADE table).

```sql
-- Using DEPARTMENT subquery
SELECT E.*
FROM EMPLOYEE E
WHERE E.DEPTNO = (
    SELECT DEPTNO
    FROM DEPARTMENT
    WHERE DNAME = 'SALES'
);

-- With grade 3 salary range (SAL between 1401 and 2000)
SELECT E.ENAME, E.JOB, E.SAL
FROM EMPLOYEE E
WHERE E.DEPTNO = (
    SELECT DEPTNO FROM DEPARTMENT WHERE DNAME = 'SALES'
)
  AND E.SAL BETWEEN 1401 AND 2000;
```

---

### Query 4 — Display those who are NOT managers and those who ARE managers

**Description:**  
Two parts combined using `UNION`:
- First part: employees whose `EMPNO` does **not** appear in the `MGR` column
  (not managing anyone).
- Second part: employees who **are** someone's manager using `IN`.

```sql
-- Employees who are NOT managers (not managing anyone)
SELECT ENAME, JOB
FROM EMPLOYEE
WHERE EMPNO NOT IN (
    SELECT MGR FROM EMPLOYEE WHERE MGR IS NOT NULL
)

UNION

-- Employees who ARE managers (managing at least one person)
SELECT ENAME, JOB
FROM EMPLOYEE
WHERE EMPNO IN (
    SELECT MGR FROM EMPLOYEE WHERE MGR IS NOT NULL
);
```

---

### Query 5 — Display employees whose manager's name is JONES

**Description:**  
This query uses a **Self-referencing Subquery**. The inner query finds the
`EMPNO` of the employee named `'JONES'`. The outer query then returns all
employees whose `MGR` field matches JONES's employee number — meaning
JONES is their direct manager.

```sql
SELECT ENAME, JOB, MGR
FROM EMPLOYEE
WHERE MGR = (
    SELECT EMPNO
    FROM EMPLOYEE
    WHERE ENAME = 'JONES'
);
```

---

### Query 6 — Display employee names working in the SALES department

**Description:**  
The inner subquery retrieves the `DEPTNO` corresponding to `'SALES'` from
the `DEPARTMENT` table. The outer query returns all employee names belonging
to that department number.

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE DEPTNO = (
    SELECT DEPTNO
    FROM DEPARTMENT
    WHERE DNAME = 'SALES'
);
```

---

### Query 7 — Employee name, dept name, salary and commission for salary 2000–5000 in CHICAGO

**Description:**  
This query joins `EMPLOYEE` and `DEPARTMENT` tables. It filters employees
within the salary range 2000 to 5000 whose department is located in `'CHICAGO'`.
Both direct join and subquery approaches are shown.

```sql
-- Direct join approach
SELECT E.ENAME, D.DNAME, E.SAL, E.COMM
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
  AND E.SAL BETWEEN 2000 AND 5000
  AND D.LOC = 'CHICAGO';

-- Using Subquery
SELECT E.ENAME, D.DNAME, E.SAL, E.COMM
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
  AND E.SAL BETWEEN 2000 AND 5000
  AND E.DEPTNO IN (
      SELECT DEPTNO
      FROM DEPARTMENT
      WHERE LOC = 'CHICAGO'
  );
```

---

### Query 8 — Display employees whose salary is greater than their manager's salary

**Description:**  
This is a **Correlated Subquery** using a Self Join approach. For each employee
in the outer query, the inner query retrieves their manager's salary by matching
`E.MGR = M.EMPNO`. Only employees earning more than their own manager are returned.

```sql
-- Self Join approach
SELECT E.ENAME AS EMPLOYEE, E.SAL AS EMP_SALARY,
       M.ENAME AS MANAGER, M.SAL AS MGR_SALARY
FROM EMPLOYEE E, EMPLOYEE M
WHERE E.MGR = M.EMPNO
  AND E.SAL > M.SAL;

-- Correlated Subquery
SELECT ENAME, SAL
FROM EMPLOYEE E
WHERE SAL > (
    SELECT SAL
    FROM EMPLOYEE
    WHERE EMPNO = E.MGR
);
```

---

### Query 9 — Display employees working in the same department as their manager

**Description:**  
This **Correlated Subquery** checks whether an employee and their manager
share the same `DEPTNO`. For each employee, the inner query fetches their
manager's department number and compares it with the employee's own department.

```sql
-- Correlated Subquery
SELECT E.ENAME AS EMPLOYEE, E.DEPTNO
FROM EMPLOYEE E
WHERE E.DEPTNO = (
    SELECT M.DEPTNO
    FROM EMPLOYEE M
    WHERE M.EMPNO = E.MGR
);

-- Self Join (alternative)
SELECT E.ENAME AS EMPLOYEE, E.DEPTNO
FROM EMPLOYEE E, EMPLOYEE M
WHERE E.MGR = M.EMPNO
  AND E.DEPTNO = M.DEPTNO;
```

---

### Query 10 — Grade and employee name for dept 10 or 30, grade not 4, joined before 31-DEC-82

**Description:**  
This query filters employees from department 10 or 30 who joined before
31st December 1982. Grade 4 corresponds to salary between 2001–3000
(standard Oracle SALGRADE), so grade NOT 4 means salary is NOT in that range.

```sql
-- With SALGRADE table
SELECT S.GRADE, E.ENAME
FROM EMPLOYEE E, SALGRADE S
WHERE E.SAL BETWEEN S.LOSAL AND S.HISAL
  AND E.DEPTNO IN (10, 30)
  AND S.GRADE != 4
  AND E.HIREDATE < TO_DATE('31-DEC-82', 'DD-MON-YY')
ORDER BY S.GRADE, E.ENAME;

-- Without SALGRADE table (Grade 4 = SAL 2001-3000)
SELECT E.ENAME, E.SAL, E.DEPTNO, E.HIREDATE
FROM EMPLOYEE E
WHERE E.DEPTNO IN (10, 30)
  AND E.SAL NOT BETWEEN 2001 AND 3000
  AND E.HIREDATE < TO_DATE('31-DEC-1982', 'DD-MON-YYYY')
ORDER BY E.ENAME;
```

---

## 📌 Key Concepts Used

| Concept | Description |
|---------|-------------|
| **`> ANY`** | TRUE if value > at least one subquery result (equivalent to `> MIN`) |
| **`> ALL`** | TRUE if value > every subquery result (equivalent to `> MAX`) |
| **`NOT IN`** | Excludes rows whose value matches any value in the subquery |
| **Correlated Subquery** | Inner query depends on outer query's current row; re-evaluated each time |
| **Self Join** | Table joined with itself using aliases to compare rows within same table |
| **`BETWEEN`** | Filters values within a specified inclusive range |
| **`UNION`** | Combines results of two SELECT statements, removing duplicates |
| **`TO_DATE()`** | Oracle function to convert a string to DATE data type |

---

## ✅ Output Summary

- `ANY` operator returned dept 10 employees earning more than at least one other dept employee.
- `ALL` operator returned dept 10 employees earning more than every other dept employee.
- Correlated Subqueries correctly identified employees earning more than their managers.
- Self-referencing Subqueries resolved manager-employee hierarchical comparisons.
- Combined conditions with `IN`, `BETWEEN`, and date filters gave accurate filtered outputs.

---

*Experiment 10 | DBMS Lab | UCS4001*