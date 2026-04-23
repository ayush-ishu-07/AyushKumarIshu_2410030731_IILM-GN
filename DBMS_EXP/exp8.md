# 🗄️ Experiment 8 — SQL Joins & Multi-Table Queries

**Course:** Database Management System (UCS4001)  
**Topic:** Joins — Inner Join, Self Join, Outer Join, Equi Join  
**CO Mapped:** CO1, CO2

---

## 📋 Objective

To perform various SQL JOIN operations on the `EMPLOYEE` and `DEPARTMENT`
tables and retrieve combined data from multiple tables using different types of joins.

---

## 🛠️ Table Structure & Sample Data

### Table: EMPLOYEE

| Column   | Data Type  | Size | Constraint  |
|----------|------------|------|-------------|
| EMPNO    | NUMBER     | 4    | Primary Key |
| ENAME    | VARCHAR2   | 20   | NOT NULL    |
| JOB      | VARCHAR2   | 20   |             |
| MGR      | NUMBER     | 4    |             |
| HIREDATE | DATE       |      |             |
| SAL      | NUMBER     | 10   |             |
| COMM     | NUMBER     | 7    |             |
| DEPTNO   | NUMBER     | 2    | Foreign Key |

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

### Query 1 — Display all employees with their department name

**Description:**  
This query uses an **INNER JOIN** (Equi Join) between the `EMPLOYEE` and
`DEPARTMENT` tables on the common column `DEPTNO` to display the name of
every employee along with their respective department name.

```sql
SELECT E.ENAME, D.DNAME
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO;
```

---

### Query 2 — Display employees whose manager name is JONES, along with their manager name

**Description:**  
This query uses a **Self Join** on the `EMPLOYEE` table. The table is aliased
as two separate instances — one for the employee (`E`) and one for the manager
(`M`) — so we can compare the manager's name.

```sql
SELECT E.ENAME AS EMPLOYEE_NAME, M.ENAME AS MANAGER_NAME
FROM EMPLOYEE E, EMPLOYEE M
WHERE E.MGR = M.EMPNO
  AND M.ENAME = 'JONES';
```

---

### Query 3 — Display employee name, job, department name, manager name, department-wise

**Description:**  
This query combines a **Self Join** (to get manager name) and an **Equi Join**
with the `DEPARTMENT` table (to get dept name), and displays results
department-wise using `ORDER BY`.

```sql
SELECT E.ENAME AS EMP_NAME, E.JOB, D.DNAME AS DEPT_NAME,
       M.ENAME AS MANAGER_NAME, E.DEPTNO
FROM EMPLOYEE E, EMPLOYEE M, DEPARTMENT D
WHERE E.MGR = M.EMPNO
  AND E.DEPTNO = D.DEPTNO
ORDER BY E.DEPTNO;
```

---

### Query 4 — List all employees (except CLERKs), sorted by highest salary

**Description:**  
This query joins `EMPLOYEE` and `DEPARTMENT` tables, filters out employees
with the job `'CLERK'`, and sorts the result by salary in descending order
so the highest salary appears first.

```sql
SELECT E.ENAME, E.JOB, E.SAL, D.DNAME
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
  AND E.JOB != 'CLERK'
ORDER BY E.SAL DESC;
```

---

### Query 5 — Display employee, job, and manager name; also show employees without a manager

**Description:**  
This query uses a **Left Outer Join** (Self Join) to display all employees
along with their manager's name. Employees with no manager (like the
PRESIDENT) are also included, with `NULL` in the manager column.

```sql
-- Standard SQL (LEFT OUTER JOIN)
SELECT E.ENAME AS EMP_NAME, E.JOB, M.ENAME AS MANAGER_NAME
FROM EMPLOYEE E
LEFT OUTER JOIN EMPLOYEE M ON E.MGR = M.EMPNO;

-- Oracle syntax
SELECT E.ENAME AS EMP_NAME, E.JOB, M.ENAME AS MANAGER_NAME
FROM EMPLOYEE E, EMPLOYEE M
WHERE E.MGR = M.EMPNO(+);
```

---

### Query 6 — Employees who earn 36000/year OR are not clerks

**Description:**  
Joins `EMPLOYEE` and `DEPARTMENT`, calculates annual salary (`SAL * 12`),
and filters employees who earn ≥ 36000/year OR whose job is not `'CLERK'`.

```sql
SELECT E.ENAME, E.JOB, (E.SAL * 12) AS ANNUAL_SAL,
       E.DEPTNO, D.DNAME
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
  AND ((E.SAL * 12) >= 36000 OR E.JOB != 'CLERK');
```

---

### Query 7 — Employees who earn 30000/year AND are not clerks

**Description:**  
Similar to Query 6 but uses `AND` — both conditions must be true. The
employee must earn at least 30000/year **and** must not be a clerk.

```sql
SELECT E.ENAME, E.JOB, (E.SAL * 12) AS ANNUAL_SAL,
       E.DEPTNO, D.DNAME
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
  AND (E.SAL * 12) >= 30000
  AND E.JOB != 'CLERK';
```

---

### Query 8 — List all employees and managers; show 'NO MANAGER' where applicable

**Description:**  
Uses a **Self Join** with `NVL()` to replace `NULL` manager names with
the string `'NO MANAGER'`.

```sql
SELECT E.EMPNO AS EMP_NO, E.ENAME AS EMP_NAME,
       M.EMPNO AS MGR_NO,
       NVL(M.ENAME, 'NO MANAGER') AS MANAGER_NAME
FROM EMPLOYEE E
LEFT OUTER JOIN EMPLOYEE M ON E.MGR = M.EMPNO;
```

---

### Query 9 — Department name, number, and total salary for each department

**Description:**  
Joins `EMPLOYEE` and `DEPARTMENT`, groups by department, and calculates
the sum of salaries using the `SUM()` aggregate function.

```sql
SELECT D.DNAME, D.DEPTNO, SUM(E.SAL) AS TOTAL_SALARY
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO
GROUP BY D.DNAME, D.DEPTNO;
```

---

### Query 10 — Display employee number, name, and department location

**Description:**  
Performs an **Equi Join** between `EMPLOYEE` and `DEPARTMENT` to retrieve
the department location for each employee.

```sql
-- If DEPARTMENT table has LOC column
SELECT E.EMPNO, E.ENAME, D.LOC
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO;

-- Without LOC column
SELECT E.EMPNO, E.ENAME, D.DNAME AS DEPARTMENT
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO;
```

---

### Query 11 — Display employee name and department name for each employee

**Description:**  
A simple **Equi Join** that retrieves the name of every employee and
the name of the department they belong to, by matching `DEPTNO` in both tables.

```sql
SELECT E.ENAME AS EMPLOYEE_NAME, D.DNAME AS DEPARTMENT_NAME
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.DEPTNO = D.DEPTNO;
```

---

## 📌 Key Concepts Used

| Concept             | Description                                                    |
|---------------------|----------------------------------------------------------------|
| **Equi Join**       | Joins tables on equality of a common column (e.g., `DEPTNO`)  |
| **Self Join**       | Table joined with itself using aliases (manager hierarchy)     |
| **Left Outer Join** | All rows from left table + matched rows from right; NULLs shown|
| **NVL()**           | Oracle function to replace NULL with a specified value         |
| **GROUP BY**        | Groups rows for aggregate functions like `SUM()`               |

---

## ✅ Output Summary

- All JOIN queries were executed successfully on Oracle SQL / MySQL.
- Self Join was used to retrieve hierarchical data (manager → employee).
- Left Outer Join correctly displayed employees with no manager.
- Aggregate functions combined with GROUP BY gave department-wise salary totals.

---

*Experiment 8 | DBMS Lab | UCS4001*