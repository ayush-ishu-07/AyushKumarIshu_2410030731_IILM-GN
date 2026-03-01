# DBMS LAB – EXPERIMENT 3
**Title:** Sorting, Pattern Matching and Conditional Queries

---

## Aim

To perform SQL queries using ORDER BY, LIKE, logical operators, and arithmetic expressions on the EMPLOYEE table.

---

## Table Used

- EMPLOYEE

---

## Queries Performed

---

### Query 1: Display all employees of department 30 in descending order of salary

```sql
SELECT *
FROM EMPLOYEE
WHERE DEPTNO = 30
ORDER BY SAL DESC;
```

**Description:**  
This query displays all employees working in department 30, sorted by salary from highest to lowest.

---

### Query 2: Display job and department number of employees whose names are five letters long, starting with 'A' and ending with 'N'

```sql
SELECT JOB, DEPTNO
FROM EMPLOYEE
WHERE ENAME LIKE 'A___N';
```

**Description:**  
This query uses the LIKE operator to find names with exactly five characters, starting with A and ending with N.

---

### Query 3: Display names of employees whose names start with letter 'S'

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE ENAME LIKE 'S%';
```

**Description:**  
This query retrieves employee names that begin with the letter S.

---

### Query 4: Display names of employees whose names end with letter 'S'

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE ENAME LIKE '%S';
```

**Description:**  
This query retrieves employee names that end with the letter S.

---

### Query 5: Display employees working in department 10, 20, or 40 OR working as clerk, salesman, or analyst

```sql
SELECT *
FROM EMPLOYEE
WHERE DEPTNO IN (10, 20, 40)
OR JOB IN ('CLERK', 'SALESMAN', 'ANALYST');
```

**Description:**  
This query uses the IN and OR operators to filter employees based on department numbers or job roles.

---

### Query 6: Display employee number and name of employees who earn commission

```sql
SELECT EMPNO, ENAME
FROM EMPLOYEE
WHERE COMM IS NOT NULL;
```

**Description:**  
This query displays employees who receive commission.

---

### Query 7: Display employee number and total salary for each employee

```sql
SELECT EMPNO, SAL + IFNULL(COMM, 0) AS TOTAL_SALARY
FROM EMPLOYEE;
```

**Description:**  
This query calculates total salary by adding salary and commission (if available).

---

### Query 8: Display employee number and annual salary for each employee

```sql
SELECT EMPNO, SAL * 12 AS ANNUAL_SALARY
FROM EMPLOYEE;
```

**Description:**  
This query calculates the annual salary of each employee.

---

### Query 9: Display names of clerks earning more than 3000

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE JOB = 'CLERK'
AND SAL > 3000;
```

**Description:**  
This query filters clerks whose salary is greater than 3000.

---

### Query 10: Display names of employees who are clerk, salesman, or analyst and earning more than 3000

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE JOB IN ('CLERK', 'SALESMAN', 'ANALYST')
AND SAL > 3000;
```

**Description:**  
This query displays employees with specific job roles whose salary exceeds 3000.

---

## Result

All queries were executed successfully and the required output was obtained.

---

## Conclusion

This experiment helped in understanding sorting of records, pattern matching using LIKE, and applying conditions using logical operators in SQL.