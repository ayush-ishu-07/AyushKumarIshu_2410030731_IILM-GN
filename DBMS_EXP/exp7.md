# 🗄️ Experiment 7 — Advanced SQL Queries (Date Functions, Salary Analysis & Group Queries)

**Course:** Database Management System (UCS4001)  
**Lab:** DBMS Practical  
**Experiment No.:** 07  
**CO Mapped:** CO1, CO2

---

## 🎯 Aim

To write and execute advanced SQL queries using date functions, string formatting, aggregate functions, and `GROUP BY` / `DECODE` clauses on the **EMPLOYEE** and **DEPARTMENT** tables — performing salary analysis, date-based calculations, and department-wise grouped reporting.

---

## 📋 Description

In this experiment, we explore powerful SQL features such as:

- **Date Arithmetic** — calculating remaining days in a year, finding the last Sunday of a month, and other date-based computations.
- **Aggregate Functions** — `MAX()`, `MIN()`, `SUM()`, `COUNT()` for salary analysis.
- **Conditional Formatting** — displaying salary in dollar format using `TO_CHAR()`.
- **DECODE / CASE** — creating pivot-style matrix queries showing salary per department per job.
- **GROUP BY & HAVING** — grouping records by department and job to get meaningful summaries.

These techniques are essential for real-world database reporting and business intelligence scenarios.

---

## 🛢️ Pre-requisite: Table Structure & Data

```sql
-- EMPLOYEE Table
CREATE TABLE EMPLOYEE (
    EMPNO    NUMBER(4)    PRIMARY KEY,
    ENAME    VARCHAR2(20) NOT NULL,
    JOB      VARCHAR2(20),
    MGR      NUMBER(4),
    HIREDATE DATE,
    SAL      NUMBER(10),
    COMM     NUMBER(7),
    DEPTNO   NUMBER(2)    REFERENCES DEPARTMENT(DEPTNO)
);

-- DEPARTMENT Table
CREATE TABLE DEPARTMENT (
    DEPTNO NUMBER(2)    PRIMARY KEY,
    DNAME  VARCHAR2(15) NOT NULL
);
```

---

## 💻 SQL Queries

### Q1 — Compute the Number of Days Remaining in This Year

```sql
SELECT
    SYSDATE                                           AS TODAY,
    TO_DATE('31-DEC-' || TO_CHAR(SYSDATE, 'YYYY'), 'DD-MON-YYYY') - TRUNC(SYSDATE)
                                                      AS DAYS_REMAINING
FROM DUAL;
```

> **Explanation:** `SYSDATE` gives the current date. We find 31st December of the current year and subtract today's date to get days remaining.

---

### Q2 — Find Highest and Lowest Salaries and Their Difference

```sql
SELECT
    MAX(SAL)          AS HIGHEST_SAL,
    MIN(SAL)          AS LOWEST_SAL,
    MAX(SAL) - MIN(SAL) AS DIFFERENCE
FROM EMPLOYEE;
```

> **Explanation:** `MAX()` and `MIN()` aggregate functions are used. Their difference shows the salary spread across all employees.

---

### Q3 — List Employees Whose Commission is Greater Than 25% of Their Salary

```sql
SELECT
    EMPNO,
    ENAME,
    SAL,
    COMM,
    COMM * 100 / SAL AS COMM_PERCENTAGE
FROM EMPLOYEE
WHERE COMM > 0.25 * SAL;
```

> **Explanation:** We filter employees where `COMM` exceeds 25% of `SAL`. The `COMM_PERCENTAGE` column shows the actual commission percentage.

---

### Q4 — Display Salary in Dollar Format

```sql
SELECT
    ENAME,
    SAL,
    TO_CHAR(SAL, '$999,999.99') AS SALARY_IN_DOLLAR
FROM EMPLOYEE;
```

> **Explanation:** `TO_CHAR()` with a format mask `$999,999.99` converts the numeric salary into a dollar-formatted string.

---

### Q5 — Matrix Query: Job-wise Salary per Department with Total

```sql
SELECT
    JOB,
    SUM(DECODE(DEPTNO, 10, SAL, 0)) AS "DEPT 10",
    SUM(DECODE(DEPTNO, 20, SAL, 0)) AS "DEPT 20",
    SUM(DECODE(DEPTNO, 30, SAL, 0)) AS "DEPT 30",
    SUM(DECODE(DEPTNO, 40, SAL, 0)) AS "DEPT 40",
    SUM(SAL)                         AS "TOTAL"
FROM EMPLOYEE
GROUP BY JOB
ORDER BY JOB;
```

> **Explanation:** This is a pivot/matrix query. `DECODE()` acts like a conditional — if `DEPTNO` matches, it returns `SAL`, else `0`. Wrapping in `SUM()` aggregates per department. The final `SUM(SAL)` gives the row total for all departments.

---

### Q6 — Total Employees and Count Hired in 1980, 1981, 1982, 1983

```sql
SELECT
    COUNT(*)                                                   AS "TOTAL",
    SUM(DECODE(TO_CHAR(HIREDATE, 'YYYY'), '1980', 1, 0))    AS "1980",
    SUM(DECODE(TO_CHAR(HIREDATE, 'YYYY'), '1981', 1, 0))    AS "1981",
    SUM(DECODE(TO_CHAR(HIREDATE, 'YYYY'), '1982', 1, 0))    AS "1982",
    SUM(DECODE(TO_CHAR(HIREDATE, 'YYYY'), '1983', 1, 0))    AS "1983"
FROM EMPLOYEE;
```

> **Explanation:** `TO_CHAR(HIREDATE, 'YYYY')` extracts the year. `DECODE` returns `1` if the year matches, `0` otherwise. `SUM()` counts matches per year. `COUNT(*)` gives total employees.

---

### Q7 — Get the Last Sunday of Any Given Month

```sql
-- Last Sunday of the current month
SELECT
    NEXT_DAY(LAST_DAY(SYSDATE) - 7, 'SUNDAY') AS LAST_SUNDAY
FROM DUAL;
```

> **Explanation:** `LAST_DAY(SYSDATE)` returns the last date of the current month. Subtracting 7 moves back one week. `NEXT_DAY(..., 'SUNDAY')` then finds the very next Sunday — which is the last Sunday of the month.

---

### Q8 — Display Department Numbers and Total Employees per Department

```sql
SELECT
    DEPTNO,
    COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEE
GROUP BY DEPTNO
ORDER BY DEPTNO;
```

> **Explanation:** `GROUP BY DEPTNO` groups rows by department. `COUNT(*)` counts employees in each group.

---

### Q9 — Display Various Jobs and Total Employees in Each Job Group

```sql
SELECT
    JOB,
    COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEE
GROUP BY JOB
ORDER BY TOTAL_EMPLOYEES DESC;
```

> **Explanation:** Same concept as Q8 but grouped by `JOB`. `ORDER BY TOTAL_EMPLOYEES DESC` lists the most common job first.

---

### Q10 — Display Department Numbers and Total Salary per Department

```sql
SELECT
    DEPTNO,
    SUM(SAL) AS TOTAL_SALARY
FROM EMPLOYEE
GROUP BY DEPTNO
ORDER BY DEPTNO;
```

> **Explanation:** `SUM(SAL)` computes total payroll per department. This is useful for budgeting and financial reporting.

---

## 📊 Sample Output

| DEPTNO | TOTAL_EMPLOYEES | TOTAL_SALARY |
|--------|----------------|--------------|
| 10     | 3              | 8750         |
| 20     | 5              | 10875        |
| 30     | 6              | 9400         |
| 40     | 1              | 3000         |

---

## 🔑 Key Concepts Used

| Concept | Description |
|--------|-------------|
| `SYSDATE` | Returns current date and time |
| `TO_CHAR()` | Converts date/number to formatted string |
| `TO_DATE()` | Converts string to DATE type |
| `LAST_DAY()` | Returns last day of the month |
| `NEXT_DAY()` | Returns the next specified weekday |
| `DECODE()` | Oracle's conditional expression (like IF-ELSE) |
| `GROUP BY` | Groups rows sharing a value for aggregation |
| `MAX()` / `MIN()` | Returns highest / lowest value in a group |
| `SUM()` / `COUNT()` | Sum and count of values in a group |

---

## ✅ Conclusion

In this experiment, we successfully:

1. Performed **date arithmetic** to calculate days remaining in the year and found the last Sunday of a month.
2. Conducted **salary analysis** using aggregate functions like `MAX()`, `MIN()`, and `SUM()`.
3. Filtered employees based on **commission percentage**.
4. Used **`TO_CHAR()`** to format salary in dollar notation.
5. Built a **pivot/matrix query** using `DECODE()` to display job-wise salaries across departments.
6. Used **`GROUP BY`** to generate department-wise and job-wise employee count and salary summaries.

These advanced SQL techniques are widely used in real-world database reporting and analytics.

---

> 📁 *DBMS Lab | UCS4001 | Experiment 07*
