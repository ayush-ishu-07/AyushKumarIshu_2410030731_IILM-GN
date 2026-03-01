# DBMS LAB – EXPERIMENT 6
**Title:** Date Functions and Conditional Queries in MySQL

---

## Aim

To perform SQL queries using date functions, CASE statement, and conditional logic on the EMPLOYEE table.

---

## Tables Used

- EMPLOYEE  
- DEPARTMENT  

---

## Queries Performed

---

### Query 1: Display empno, ename and department name

```sql
SELECT EMPNO,
       ENAME,
       CASE DEPTNO
            WHEN 10 THEN 'RESEARCH'
            WHEN 20 THEN 'ACCOUNTING'
            WHEN 30 THEN 'SALES'
            WHEN 40 THEN 'OPERATIONS'
       END AS DNAME
FROM EMPLOYEE;
```

**Description:**  
Uses CASE statement to display department names instead of numbers.

---

### Query 2: Display age in days

```sql
SELECT DATEDIFF(CURDATE(), '2003-01-01') AS AGE_IN_DAYS;
```

**Description:**  
Calculates age in days from given date of birth.

---

### Query 3: Display age in months

```sql
SELECT TIMESTAMPDIFF(MONTH, '2003-01-01', CURDATE()) AS AGE_IN_MONTHS;
```

**Description:**  
Calculates age in months.

---

### Query 4: Display current date in readable format

```sql
SELECT DATE_FORMAT(CURDATE(), '%D %M %Y') AS FORMATTED_DATE;
```

**Description:**  
Formats the current date in readable form.

---

### Query 5: Display joining sentence for employee SCOTT

```sql
SELECT CONCAT(
       ENAME,
       ' has joined the company on ',
       DATE_FORMAT(HIREDATE, '%W %D %M %Y')
) AS JOINING_INFO
FROM EMPLOYEE
WHERE ENAME = 'SCOTT';
```

**Description:**  
Displays joining date in sentence format.

---

### Query 6: Find nearest Saturday after current date

```sql
SELECT DATE_ADD(CURDATE(),
INTERVAL (7 - DAYOFWEEK(CURDATE())) DAY) AS NEXT_SATURDAY;
```

**Description:**  
Finds the next Saturday.

---

### Query 7: Display current time

```sql
SELECT CURTIME() AS CURRENT_TIME;
```

---

### Query 8: Display date three months before current date

```sql
SELECT DATE_SUB(CURDATE(), INTERVAL 3 MONTH) AS DATE_BEFORE_3_MONTHS;
```

---

### Query 9: Display employees who joined in December

```sql
SELECT *
FROM EMPLOYEE
WHERE MONTH(HIREDATE) = 12;
```

---

### Query 10: Display employees whose first two digits of year equal last two digits of salary

```sql
SELECT *
FROM EMPLOYEE
WHERE RIGHT(SAL,2) = DATE_FORMAT(HIREDATE,'%y');
```

---

### Query 11: Display employees whose 10% salary equals year of joining

```sql
SELECT *
FROM EMPLOYEE
WHERE SAL * 0.10 = YEAR(HIREDATE);
```

---

### Query 12: Display employees who joined before 15th of month

```sql
SELECT *
FROM EMPLOYEE
WHERE DAY(HIREDATE) < 15;
```

---

### Query 13: Display employees whose joining day equals department number

```sql
SELECT *
FROM EMPLOYEE
WHERE DAY(HIREDATE) = DEPTNO;
```

---

### Query 14: Display current date

```sql
SELECT CURDATE();
```

---

### Query 15: Display current timestamp

```sql
SELECT NOW();
```

---

## Result

All queries executed successfully in MySQL environment.

---

## Conclusion

This experiment improved understanding of date functions, CASE statements, and conditional queries in MySQL.