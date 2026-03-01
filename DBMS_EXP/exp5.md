# DBMS LAB – EXPERIMENT 5
**Title:** Aggregate Functions and String Functions in SQL

---

## Aim

To use aggregate functions and string functions to retrieve summarized and formatted data from the EMPLOYEE table.

---

## Table Used

- EMPLOYEE

---

## Queries Performed

---

### Query 1: Display the total number of employees working in the company

```sql
SELECT COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEE;
```

**Description:**  
Counts the total number of employees in the company.

---

### Query 2: Display the total salary being paid to all employees

```sql
SELECT SUM(SAL) AS TOTAL_SALARY
FROM EMPLOYEE;
```

**Description:**  
Calculates the sum of salaries of all employees.

---

### Query 3: Display the maximum salary from EMPLOYEE table

```sql
SELECT MAX(SAL) AS MAX_SALARY
FROM EMPLOYEE;
```

**Description:**  
Finds the highest salary among all employees.

---

### Query 4: Display the minimum salary from EMPLOYEE table

```sql
SELECT MIN(SAL) AS MIN_SALARY
FROM EMPLOYEE;
```

**Description:**  
Finds the lowest salary among all employees.

---

### Query 5: Display the average salary of employees

```sql
SELECT AVG(SAL) AS AVERAGE_SALARY
FROM EMPLOYEE;
```

**Description:**  
Calculates the average salary of all employees.

---

### Query 6: Display the maximum salary being paid to clerks

```sql
SELECT MAX(SAL) AS MAX_CLERK_SALARY
FROM EMPLOYEE
WHERE JOB = 'CLERK';
```

**Description:**  
Finds the maximum salary among clerks.

---

### Query 7: Display the maximum salary being paid in department number 20

```sql
SELECT MAX(SAL) AS MAX_SAL_DEPT20
FROM EMPLOYEE
WHERE DEPTNO = 20;
```

**Description:**  
Displays the highest salary in department 20.

---

### Query 8: Display the minimum salary paid to any salesman

```sql
SELECT MIN(SAL) AS MIN_SALESMAN_SALARY
FROM EMPLOYEE
WHERE JOB = 'SALESMAN';
```

**Description:**  
Finds the minimum salary among salesmen.

---

### Query 9: Display the average salary drawn by managers

```sql
SELECT AVG(SAL) AS AVG_MANAGER_SALARY
FROM EMPLOYEE
WHERE JOB = 'MANAGER';
```

**Description:**  
Calculates the average salary of managers.

---

### Query 10: Display the total salary drawn by analysts working in department number 40

```sql
SELECT SUM(SAL) AS TOTAL_ANALYST_SALARY
FROM EMPLOYEE
WHERE JOB = 'ANALYST'
AND DEPTNO = 40;
```

**Description:**  
Calculates the total salary of analysts in department 40.

---

### Query 11: Display the names of employees in uppercase

```sql
SELECT UPPER(ENAME) AS EMPLOYEE_NAME
FROM EMPLOYEE;
```

**Description:**  
Converts employee names to uppercase.

---

### Query 12: Display the names of employees in lowercase

```sql
SELECT LOWER(ENAME) AS EMPLOYEE_NAME
FROM EMPLOYEE;
```

**Description:**  
Converts employee names to lowercase.

---

### Query 13: Display the names of employees in proper case

```sql
SELECT CONCAT(
       UPPER(SUBSTRING(ENAME,1,1)),
       LOWER(SUBSTRING(ENAME,2))
) AS EMPLOYEE_NAME
FROM EMPLOYEE;
```

**Description:**  
Displays employee names in proper case format.

---

### Query 14: Display the length of your name using appropriate function

```sql
SELECT LENGTH('AYUSH') AS NAME_LENGTH;
```

**Description:**  
Finds the length of the given name using LENGTH function.

---

### Query 15: Display the length of all employee names

```sql
SELECT ENAME, LENGTH(ENAME) AS NAME_LENGTH
FROM EMPLOYEE;
```

**Description:**  
Displays the length of each employee name.

---

## Result

All 15 queries were executed successfully and the required output was obtained.

---

## Conclusion

This experiment helped in understanding aggregate functions and string functions for analyzing and formatting data in SQL.