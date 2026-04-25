# 🗄️ Experiment 9 — SQL Subqueries

**Course:** Database Management System (UCS4001)  
**Topic:** Subqueries — Single Row, Multi Row, Correlated Subqueries  
**CO Mapped:** CO1, CO2

---

## 📋 Objective

To perform various SQL **Subquery** operations on the `EMPLOYEE` and
`DEPARTMENT` tables. A subquery is a query nested inside another query
(SELECT, INSERT, UPDATE, or DELETE). It helps in retrieving data based
on computed or dynamic conditions.

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

| DEPTNO | DNAME      |
|--------|------------|
| 10     | RESEARCH   |
| 20     | ACCOUNTING |
| 30     | SALES      |
| 40     | OPERATIONS |

---

## 📝 SQL Queries with Descriptions

---

### Query 1 — Display the name of employee who earns the highest salary

**Description:**  
This query uses a **Single Row Subquery** with the `MAX()` aggregate function.  
The inner query first finds the maximum salary from the `EMPLOYEE` table.
The outer query then retrieves the name of the employee whose salary equals
that maximum value.

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE SAL = (SELECT MAX(SAL) FROM EMPLOYEE);
```

---

### Query 2 — Display employee number and name of the clerk earning the highest salary among all clerks

**Description:**  
This query filters the inner subquery by `JOB = 'CLERK'` to get the maximum
salary among clerks only. The outer query then returns the `EMPNO` and `ENAME`
of the clerk matching that salary.  
This is a **Single Row Subquery** with a job-specific filter.

```sql
SELECT EMPNO, ENAME
FROM EMPLOYEE
WHERE JOB = 'CLERK'
  AND SAL = (SELECT MAX(SAL) FROM EMPLOYEE WHERE JOB = 'CLERK');
```

---

### Query 3 — Display names of salesman who earn more than the highest salary of any clerk

**Description:**  
The inner query finds the maximum salary among all clerks. The outer query
then returns salesman whose salary is **greater than** that maximum.  
This demonstrates comparing one job group's salary against another using
a **Single Row Subquery**.

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE JOB = 'SALESMAN'
  AND SAL > (SELECT MAX(SAL) FROM EMPLOYEE WHERE JOB = 'CLERK');
```

---

### Query 4 — Display names of clerks who earn more than JAMES but less than SCOTT

**Description:**  
This query uses **two Single Row Subqueries** combined with `AND`:
- The first subquery fetches JAMES's salary as the lower bound.
- The second subquery fetches SCOTT's salary as the upper bound.  
Only clerks falling between these two salaries are returned.

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE JOB = 'CLERK'
  AND SAL > (SELECT SAL FROM EMPLOYEE WHERE ENAME = 'JAMES')
  AND SAL < (SELECT SAL FROM EMPLOYEE WHERE ENAME = 'SCOTT');
```

---

### Query 5 — Display names of employees who earn more than JAMES OR more than SCOTT

**Description:**  
This query uses `OR` between two subqueries:
- The first condition checks if salary > JAMES's salary.
- The second condition checks if salary > SCOTT's salary.  
Any employee satisfying **at least one** condition is returned.  
This is equivalent to using `> ANY (subquery)` in some databases.

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE SAL > (SELECT SAL FROM EMPLOYEE WHERE ENAME = 'JAMES')
   OR SAL > (SELECT SAL FROM EMPLOYEE WHERE ENAME = 'SCOTT');
```

---

### Query 6 — Display names of employees who earn the highest salary in their respective departments

**Description:**  
This query uses a **Correlated Subquery**. For each employee in the outer query,
the inner query calculates the maximum salary within the same department
(`E1.DEPTNO = E2.DEPTNO`). Only employees whose salary matches the department's
maximum are returned.

```sql
SELECT ENAME, SAL, DEPTNO
FROM EMPLOYEE E1
WHERE SAL = (
    SELECT MAX(SAL)
    FROM EMPLOYEE E2
    WHERE E1.DEPTNO = E2.DEPTNO
);
```

---

### Query 7 — Display names of employees who earn the highest salary in their respective job groups

**Description:**  
Similar to Query 6, this is a **Correlated Subquery** but grouped by `JOB`
instead of `DEPTNO`. For each employee, the inner query finds the maximum
salary within the same job role. Employees matching this maximum are returned.

```sql
SELECT ENAME, JOB, SAL
FROM EMPLOYEE E1
WHERE SAL = (
    SELECT MAX(SAL)
    FROM EMPLOYEE E2
    WHERE E1.JOB = E2.JOB
);
```

---

### Query 8 — Display employee names who are working in the ACCOUNTING department

**Description:**  
This query uses a **Single Row Subquery** on the `DEPARTMENT` table to first
get the `DEPTNO` of the `'ACCOUNTING'` department. The outer query then
filters employees belonging to that department.

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE DEPTNO = (
    SELECT DEPTNO
    FROM DEPARTMENT
    WHERE DNAME = 'ACCOUNTING'
);
```

---

### Query 9 — Display employee names who are working in CHICAGO

**Description:**  
This query assumes the `DEPARTMENT` table has a `LOC` (location) column.
The inner subquery retrieves the `DEPTNO` for the location `'CHICAGO'`.
The outer query returns employee names from that department.

```sql
-- If DEPARTMENT table has LOC column
SELECT ENAME
FROM EMPLOYEE
WHERE DEPTNO = (
    SELECT DEPTNO
    FROM DEPARTMENT
    WHERE LOC = 'CHICAGO'
);

-- Using IN for multiple departments in Chicago
SELECT ENAME
FROM EMPLOYEE
WHERE DEPTNO IN (
    SELECT DEPTNO
    FROM DEPARTMENT
    WHERE LOC = 'CHICAGO'
);
```

---

### Query 10 — Display job groups having total salary greater than the maximum salary of managers

**Description:**  
This query uses `GROUP BY` with `HAVING` and a **Subquery in the HAVING clause**.
The inner query calculates the maximum salary of all managers. The outer query
groups employees by job and returns only those job groups whose total salary
exceeds that maximum.

```sql
SELECT JOB, SUM(SAL) AS TOTAL_SALARY
FROM EMPLOYEE
GROUP BY JOB
HAVING SUM(SAL) > (
    SELECT MAX(SAL)
    FROM EMPLOYEE
    WHERE JOB = 'MANAGER'
);
```

---

## 📌 Key Concepts Used

| Concept | Description |
|---------|-------------|
| **Single Row Subquery** | Returns exactly one row; used with `=`, `>`, `<`, `>=`, `<=` operators |
| **Multi Row Subquery** | Returns multiple rows; used with `IN`, `ANY`, `ALL` operators |
| **Correlated Subquery** | Inner query references a column from the outer query; re-executed for each row |
| **Subquery in HAVING** | Used to filter grouped results based on aggregate comparisons |
| **MAX()** | Aggregate function to find the maximum value in a column |
| **IN operator** | Checks if a value exists in the result set of a subquery |

---

## ✅ Output Summary

- Single Row Subqueries were used to find employees with max/specific salaries.
- Correlated Subqueries efficiently returned department-wise and job-wise highest earners.
- Multi-row Subqueries with `IN` operator handled cases with multiple matching departments.
- Subqueries inside `HAVING` clause were used to filter aggregated job groups.

---

*Experiment 9 | DBMS Lab | UCS4001*