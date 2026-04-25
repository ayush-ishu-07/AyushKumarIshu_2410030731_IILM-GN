# 🗄️ Experiment 12 — SQL Complex Subqueries, DML & SALGRADE Operations

**Course:** Database Management System (UCS4001)  
**Topic:** Complex Subqueries — Manager Comparisons, DML with Subqueries, SALGRADE Table  
**CO Mapped:** CO1, CO2

---

## 📋 Objective

To perform complex SQL operations involving manager-employee salary comparisons,
DML (DELETE) with subqueries on referential conditions, SALGRADE-based grade
queries, and advanced filtering using correlated and nested subqueries — all on
the `EMPLOYEE`, `DEPARTMENT`, and `SALGRADE` tables.

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

### Table: SALGRADE

| Column | Data Type | Description                   |
|--------|-----------|-------------------------------|
| GRADE  | NUMBER    | Grade level (1 to 5)          |
| LOSAL  | NUMBER    | Minimum salary for this grade |
| HISAL  | NUMBER    | Maximum salary for this grade |

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

### Sample Data — SALGRADE

| GRADE | LOSAL | HISAL |
|-------|-------|-------|
| 1     | 700   | 1200  |
| 2     | 1201  | 1400  |
| 3     | 1401  | 2000  |
| 4     | 2001  | 3000  |
| 5     | 3001  | 9999  |

---

## 📝 SQL Queries with Descriptions

---

### Query 1 — Employees whose salary is less than their manager but more than any other manager's salary

**Description:**  
This query uses two **Correlated/Nested Subqueries**:
- First condition: employee earns less than their own manager (Self Join).
- Second condition: uses `> ANY` to ensure the employee earns more than at
  least one manager in the company.

```sql
SELECT E.ENAME, E.SAL, E.JOB
FROM EMPLOYEE E, EMPLOYEE M
WHERE E.MGR = M.EMPNO
  AND E.SAL < M.SAL
  AND E.SAL > ANY (
      SELECT SAL
      FROM EMPLOYEE
      WHERE JOB = 'MANAGER'
  );
```

---

### Query 2 — Find the number of employees whose salary is greater than their manager's salary

**Description:**  
This query uses a **Correlated Subquery inside COUNT()**. The inner query checks
whether each employee earns more than their own manager. The outer query wraps
the result in `COUNT(*)` to return the total number of such employees.

```sql
-- Using Correlated Subquery
SELECT COUNT(*) AS EMP_EARNING_MORE_THAN_MGR
FROM EMPLOYEE E
WHERE SAL > (
    SELECT SAL
    FROM EMPLOYEE
    WHERE EMPNO = E.MGR
);

-- Using Self Join approach
SELECT COUNT(*) AS EMP_EARNING_MORE_THAN_MGR
FROM EMPLOYEE E, EMPLOYEE M
WHERE E.MGR = M.EMPNO
  AND E.SAL > M.SAL;
```

---

### Query 3 — Display managers who are NOT working under the PRESIDENT but under any other manager

**Description:**  
This query identifies managers (`JOB = 'MANAGER'`) whose own manager (`MGR`)
is **not** the PRESIDENT. The inner subquery fetches the `EMPNO` of the
PRESIDENT. The outer query returns managers whose `MGR` does not match.

```sql
SELECT ENAME, JOB, MGR
FROM EMPLOYEE
WHERE JOB = 'MANAGER'
  AND MGR != (
      SELECT EMPNO
      FROM EMPLOYEE
      WHERE JOB = 'PRESIDENT'
  );

-- Alternative using NOT IN
SELECT ENAME, JOB, MGR
FROM EMPLOYEE
WHERE JOB = 'MANAGER'
  AND MGR NOT IN (
      SELECT EMPNO
      FROM EMPLOYEE
      WHERE JOB = 'PRESIDENT'
  );
```

---

### Query 4 — Delete departments where no employee is working

**Description:**  
This is a **DML DELETE with a NOT IN Subquery**. The inner query retrieves all
`DEPTNO` values that exist in the `EMPLOYEE` table (departments with employees).
The DELETE removes departments from `DEPARTMENT` whose `DEPTNO` is not in that list.  
> ⚠️ Preview with SELECT before running DELETE.

```sql
-- Preview rows to be deleted
SELECT *
FROM DEPARTMENT
WHERE DEPTNO NOT IN (
    SELECT DISTINCT DEPTNO FROM EMPLOYEE
);

-- DELETE query
DELETE FROM DEPARTMENT
WHERE DEPTNO NOT IN (
    SELECT DISTINCT DEPTNO FROM EMPLOYEE
);

COMMIT;
```

---

### Query 5 — Delete records from EMPLOYEE whose DEPTNO is not available in DEPARTMENT table

**Description:**  
This **DML DELETE with NOT IN Subquery** removes employees whose `DEPTNO` does
not exist in the `DEPARTMENT` table. This cleans up orphan records that violate
referential integrity.  
> ⚠️ Preview with SELECT before running DELETE.

```sql
-- Preview rows to be deleted
SELECT ENAME, DEPTNO
FROM EMPLOYEE
WHERE DEPTNO NOT IN (
    SELECT DEPTNO FROM DEPARTMENT
);

-- DELETE query
DELETE FROM EMPLOYEE
WHERE DEPTNO NOT IN (
    SELECT DEPTNO FROM DEPARTMENT
);

COMMIT;
```

---

### Query 6 — Display employees whose salary is outside any grade range in the SALGRADE table

**Description:**  
The `SALGRADE` table defines valid salary ranges. This query finds employees
whose salary does **not** fall within any defined grade range. The inner subquery
selects employees who DO fall within a grade; the outer query returns those who don't.

```sql
-- Using NOT IN with subquery
SELECT ENAME, SAL
FROM EMPLOYEE
WHERE EMPNO NOT IN (
    SELECT E.EMPNO
    FROM EMPLOYEE E, SALGRADE S
    WHERE E.SAL BETWEEN S.LOSAL AND S.HISAL
);

-- Alternative: salary out of all grade boundaries
SELECT ENAME, SAL
FROM EMPLOYEE
WHERE SAL < (SELECT MIN(LOSAL) FROM SALGRADE)
   OR SAL > (SELECT MAX(HISAL) FROM SALGRADE);
```

---

### Query 7 — Employee name, salary, commission and net pay for those whose net pay is greater than any other employee's salary

**Description:**  
Net pay is calculated as `SAL + NVL(COMM, 0)`. The `> ALL` subquery ensures
the net pay is greater than **every** employee's base salary in the company —
meaning their total compensation exceeds even the highest base earner.

```sql
SELECT ENAME,
       SAL,
       NVL(COMM, 0) AS COMM,
       (SAL + NVL(COMM, 0)) AS NET_PAY
FROM EMPLOYEE
WHERE (SAL + NVL(COMM, 0)) > ALL (
    SELECT SAL FROM EMPLOYEE
);

-- Alternative: net pay > maximum salary
SELECT ENAME,
       SAL,
       NVL(COMM, 0) AS COMM,
       (SAL + NVL(COMM, 0)) AS NET_PAY
FROM EMPLOYEE
WHERE (SAL + NVL(COMM, 0)) > (
    SELECT MAX(SAL) FROM EMPLOYEE
);
```

---

### Query 8 — Display employees working in SALES or RESEARCH department

**Description:**  
This query uses a **Multi-Row Subquery with IN**. The inner query fetches
`DEPTNO` values for departments named `'SALES'` or `'RESEARCH'`. The outer
query returns all employees whose `DEPTNO` matches any of those values.

```sql
-- Using Subquery with IN
SELECT ENAME, JOB, DEPTNO
FROM EMPLOYEE
WHERE DEPTNO IN (
    SELECT DEPTNO
    FROM DEPARTMENT
    WHERE DNAME IN ('SALES', 'RESEARCH')
);

-- Using Direct Join
SELECT E.ENAME, E.JOB, D.DNAME
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
  AND D.DNAME IN ('SALES', 'RESEARCH');
```

---

### Query 9 — Display the grade of JONES

**Description:**  
This query joins the `EMPLOYEE` table with the `SALGRADE` table using a range
condition (`BETWEEN LOSAL AND HISAL`). It filters the result for the employee
`'JONES'` to display their salary grade based on their current salary.

```sql
SELECT E.ENAME, E.SAL, S.GRADE
FROM EMPLOYEE E, SALGRADE S
WHERE E.SAL BETWEEN S.LOSAL AND S.HISAL
  AND E.ENAME = 'JONES';
```

---

### Query 10 — Display department names whose character count equals the number of employees in any other department

**Description:**  
This advanced query combines **string functions** and **aggregate subqueries**.
The inner query counts employees per department using `GROUP BY`. The outer
query checks if the `LENGTH(DNAME)` matches any of those employee counts
using `= ANY`.

```sql
SELECT DNAME, LENGTH(DNAME) AS NAME_LENGTH
FROM DEPARTMENT
WHERE LENGTH(DNAME) = ANY (
    SELECT COUNT(*)
    FROM EMPLOYEE
    GROUP BY DEPTNO
);
```

---

## 📌 Key Concepts Used

| Concept | Description |
|---------|-------------|
| **`> ANY`** | TRUE if value > at least one value in subquery result |
| **`> ALL`** | TRUE if value > every value in subquery result |
| **`NOT IN`** | Excludes rows whose value appears in the subquery result set |
| **DELETE with Subquery** | Removes rows based on dynamically computed condition |
| **SALGRADE Join** | Range join using `BETWEEN LOSAL AND HISAL` to assign grades |
| **LENGTH()** | Returns the number of characters in a string |
| **NVL()** | Replaces NULL with a specified default value |
| **Correlated Subquery** | Inner query references outer query's current row |
| **COUNT() with GROUP BY** | Counts rows per group for aggregation-based comparisons |

---

## ✅ Output Summary

- Complex salary comparisons using `ANY`, `ALL`, and Self Join handled manager-employee cases.
- `COUNT(*)` with correlated subquery counted employees earning more than their manager.
- DML DELETE with `NOT IN` safely removed orphan records from both tables.
- `SALGRADE` range join identified out-of-grade salaries and assigned grades to employees.
- `LENGTH()` with `= ANY` performed a unique string-length to employee-count comparison.

---

*Experiment 12 | DBMS Lab | UCS4001*