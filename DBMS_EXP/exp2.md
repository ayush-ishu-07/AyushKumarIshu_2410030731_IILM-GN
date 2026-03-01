# DBMS LAB – EXPERIMENT 2
**Title:** Retrieving Data Using SELECT Queries

---

## Aim

To retrieve data from the EMPLOYEE table using different SQL SELECT queries with conditions.

---

## Table Used

- EMPLOYEE

---

## Queries Performed

---

### Query 1: List all distinct jobs in EMPLOYEE table

```sql
SELECT DISTINCT JOB
FROM EMPLOYEE;
```

---

### Query 2: Display all information of employees in department number 30

```sql
SELECT *
FROM EMPLOYEE
WHERE DEPTNO = 30;
```

---

### Query 3: Display department numbers greater than 20

```sql
SELECT DISTINCT DEPTNO
FROM EMPLOYEE
WHERE DEPTNO > 20;
```

---

### Query 4: Display all managers and clerks in department 30

```sql
SELECT *
FROM EMPLOYEE
WHERE DEPTNO = 30
AND (JOB = 'MANAGER' OR JOB = 'CLERK');
```

---

### Query 5: Display employee number, name and department number of all clerks

```sql
SELECT EMPNO, ENAME, DEPTNO
FROM EMPLOYEE
WHERE JOB = 'CLERK';
```

---

### Query 6: Display all managers not working in department 30

```sql
SELECT *
FROM EMPLOYEE
WHERE JOB = 'MANAGER'
AND DEPTNO <> 30;
```

---

### Query 7: Display employees in department 10 who are neither managers nor clerks

```sql
SELECT *
FROM EMPLOYEE
WHERE DEPTNO = 10
AND JOB NOT IN ('MANAGER', 'CLERK');
```

---

### Query 8: Display employees earning salary between 1200 and 1400

```sql
SELECT ENAME, JOB, SAL
FROM EMPLOYEE
WHERE SAL BETWEEN 1200 AND 1400;
```

---

### Query 9: Display name and department number of clerks, analysts, or salesmen

```sql
SELECT ENAME, DEPTNO
FROM EMPLOYEE
WHERE JOB IN ('CLERK', 'ANALYST', 'SALESMAN');
```

---

### Query 10: Display name and department number of employees whose names start with 'M'

```sql
SELECT ENAME, DEPTNO
FROM EMPLOYEE
WHERE ENAME LIKE 'M%';
```

---

## Result

All the above queries were executed successfully and the required output was obtained.

---

## Conclusion

This experiment helped in understanding data retrieval from tables using SQL SELECT queries with conditions.