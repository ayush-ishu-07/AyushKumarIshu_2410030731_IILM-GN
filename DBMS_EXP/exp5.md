# DBMS LAB – EXPERIMENT 5
**Title:** Aggregate Functions and String Functions in SQL

---

## Aim

To use aggregate functions and string functions in SQL to retrieve summarized and formatted information from the EMPLOYEE table.

---

## Table Used

- EMPLOYEE

---

## Queries Performed

---

### Query 1: Display total number of employees working in the company

```sql
SELECT COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEE;
```

**Description:**  
This query counts the total number of records present in the EMPLOYEE table.

---

### Query 2: Display total salary paid to all employees

```sql
SELECT SUM(SAL) AS TOTAL_SALARY
FROM EMPLOYEE;
```

**Description:**  
This query calculates the sum of salaries of all employees.

---

### Query 3: Display maximum salary from EMPLOYEE table

```sql
SELECT MAX(SAL) AS MAX_SALARY
FROM EMPLOYEE;
```

**Description:**  
This query finds the highest salary among all employees.

---

### Query 4: Display minimum salary from EMPLOYEE table

```sql
SELECT MIN(SAL) AS MIN_SALARY
FROM EMPLOYEE;
```

**Description:**  
This query finds the lowest salary among all employees.

---

### Query 5: Display average salary of employees

```sql
SELECT AVG(SAL) AS AVERAGE_SALARY
FROM EMPLOYEE;
```

**Description:**  
This query calculates the average salary of all employees.

---

### Query 6: Display maximum salary paid to clerks

```sql
SELECT MAX(SAL) AS MAX_CLERK_SALARY
FROM EMPLOYEE
WHERE JOB = 'CLERK';
```

**Description:**  
This query finds the maximum salary among employees working as clerks.

---

### Query 7: Display maximum salary paid in department number 20

```sql
SELECT MAX(SAL) AS MAX_SAL_DEPT20
FROM EMPLOYEE
WHERE DEPTNO = 20;
```

**Description:**  
This query displays the highest salary in department 20.

---

### Query 8: Display minimum salary paid to salesmen

```sql
SELECT MIN(SAL) AS MIN_SALESMAN_SALARY
FROM EMPLOYEE
WHERE JOB = 'SALESMAN';
```

**Description:**  
This query finds the minimum salary among salesmen.

---

### Query 9: Display average salary drawn by managers

```sql
SELECT AVG(SAL) AS AVG_MANAGER_SALARY
FROM EMPLOYEE
WHERE JOB = 'MANAGER';
```

**Description:**  
This query calculates the average salary of managers.

---

### Query 10: Display total salary drawn by analysts working in department 40

```sql
SELECT SUM(SAL) AS TOTAL_ANALYST_SALARY
FROM EMPLOYEE
WHERE JOB = 'ANALYST'
AND DEPTNO = 40;
```

**Description:**  
This query calculates the total salary of analysts working in department 40.

---

### Query 11: Display employee names in uppercase

```sql
SELECT UPPER(ENAME) AS EMPLOYEE_NAME
FROM EMPLOYEE;
```

**Description:**  
This query converts all employee names to uppercase letters.

---

### Query 12: Display employee names in lowercase

```sql
SELECT LOWER(ENAME) AS EMPLOYEE_NAME
FROM EMPLOYEE;
```

**Description:**  
This query converts all employee names to lowercase letters.

---

### Query 13: Display employee names in proper case

```sql
SELECT CONCAT(
       UPPER(SUBSTRING(ENAME,1,1)),
       LOWER(SUBSTRING(ENAME,2))
) AS EMPLOYEE_NAME
FROM EMPLOYEE;
```

**Description:**  
This query formats employee names in proper case (first letter capital, remaining letters small).

---

### Query 14: Display length of each employee name

```sql
SELECT ENAME, LENGTH(ENAME) AS NAME_LENGTH
FROM EMPLOYEE;
```

**Description:**  
This query displays the length of each employee name using the LENGTH function.

---

## Result

All aggregate and string function queries were executed successfully and produced the required output.

---

## Conclusion

This experiment helped in understanding aggregate functions like COUNT, SUM, AVG, MAX, MIN and string functions for formatting and analyzing data in SQL.
