# DBMS LAB – EXPERIMENT 4
**Title:** Date Functions, String Operations and Salary Calculations

---

## Aim

To perform SQL queries using date functions, string functions, conditional filtering, and salary calculations on the EMPLOYEE table.

---

## Table Used

- EMPLOYEE

---

## Queries Performed

---

### Query 1: Display employees who joined before 30th June 1980 or after 31st December 1981

```sql
SELECT *
FROM EMPLOYEE
WHERE HIREDATE < '1980-06-30'
OR HIREDATE > '1981-12-31';
```

**Description:**  
This query filters employees based on their joining date using comparison operators.

---

### Query 2: Display names of employees whose second letter is 'A'

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE ENAME LIKE '_A%';
```

**Description:**  
This query uses the LIKE operator to match names whose second character is A.

---

### Query 3: Display names of employees whose name length is exactly five characters

```sql
SELECT ENAME
FROM EMPLOYEE
WHERE LENGTH(ENAME) = 5;
```

**Description:**  
This query finds employee names having exactly five characters.

---

### Query 4: Display employees who are not working as salesman, clerk, or analyst

```sql
SELECT *
FROM EMPLOYEE
WHERE JOB NOT IN ('SALESMAN', 'CLERK', 'ANALYST');
```

**Description:**  
This query filters employees excluding specific job roles using NOT IN.

---

### Query 5: Display employee name and annual salary, highest salary first

```sql
SELECT ENAME, SAL * 12 AS ANNUAL_SALARY
FROM EMPLOYEE
ORDER BY ANNUAL_SALARY DESC;
```

**Description:**  
This query calculates annual salary and sorts the result in descending order.

---

### Query 6: Display name, salary, HRA, DA, PF and total salary for each employee

```sql
SELECT ENAME,
       SAL,
       SAL * 0.15 AS HRA,
       SAL * 0.10 AS DA,
       SAL * 0.05 AS PF,
       (SAL + (SAL * 0.15) + (SAL * 0.10) - (SAL * 0.05)) AS TOTAL_SALARY
FROM EMPLOYEE;
```

**Description:**  
This query calculates different salary components and total salary for each employee.

---

### Query 7: Update salary of employees by 10% who are not eligible for commission

```sql
UPDATE EMPLOYEE
SET SAL = SAL + (SAL * 0.10)
WHERE COMM IS NULL;
```

**Description:**  
This query increases salary by 10% for employees who do not receive commission.

---

### Query 8: Display employees whose salary is more than 3000 after giving 20% increment

```sql
SELECT ENAME, SAL * 1.20 AS UPDATED_SALARY
FROM EMPLOYEE
WHERE (SAL * 1.20) > 3000;
```

**Description:**  
This query checks employee salary after a 20% increment and filters those exceeding 3000.

---

### Query 9: Display employees whose salary contains at least 3 digits

```sql
SELECT *
FROM EMPLOYEE
WHERE LENGTH(SAL) >= 3;
```

**Description:**  
This query filters employees based on the number of digits in their salary.

---

### Query 10: Display employees who joined before the 15th day of any month

```sql
SELECT *
FROM EMPLOYEE
WHERE DAY(HIREDATE) < 15;
```

**Description:**  
This query finds employees who joined the company before the 15th day of the month.

---

## Result

All queries were executed successfully and the required output was obtained.

---

## Conclusion

This experiment helped in understanding date-based queries, string operations, conditional filtering, and salary calculations using SQL.