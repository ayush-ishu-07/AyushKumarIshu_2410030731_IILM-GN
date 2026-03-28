# SQLBolt Exercises

## EXERCISE 1

### 1. Find the title of each film
```sql
SELECT title FROM movies;
```

### 2. Find the director of each film
```sql
SELECT director FROM movies;
```

### 3. Find the title and director of each film
```sql
SELECT title, director FROM movies;
```

### 4. Find the title and year of each film
```sql
SELECT title, year FROM movies;
```

### 5. Find all the information about each film
```sql
SELECT * FROM movies;
```

---

## EXERCISE 2

### 1. Find the movie with a row id of 6
```sql
SELECT * FROM movies WHERE id = 6;
```

### 2. Find the movies released between 2000 and 2010
```sql
SELECT * FROM movies WHERE year BETWEEN 2000 AND 2010;
```

### 3. Find the movies not released between 2000 and 2010
```sql
SELECT * FROM movies WHERE year NOT BETWEEN 2000 AND 2010;
```

### 4. Find the first 5 Pixar movies and their release year
```sql
SELECT title, year FROM movies ORDER BY year ASC LIMIT 5;
```

---

## EXERCISE 3

### 1. Find all the Toy Story movies
```sql
SELECT * FROM movies WHERE title LIKE 'Toy%';
```

### 2. Find all the movies directed by John Lasseter
```sql
SELECT * FROM movies WHERE director = 'John Lasseter';
```

### 3. Find all the movies not directed by John Lasseter
```sql
SELECT * FROM movies WHERE director != 'John Lasseter';
```

### 4. Find all the WALL-* movies
```sql
SELECT * FROM movies WHERE title LIKE 'WALL-%';
```

---

## EXERCISE 4

### 1. List all directors of Pixar movies (alphabetically, without duplicates)
```sql
SELECT DISTINCT director FROM movies ORDER BY director;
```

### 2. List the last four Pixar movies released (most recent to least)
```sql
SELECT * FROM movies ORDER BY year DESC LIMIT 4;
```

### 3. List the first five Pixar movies sorted alphabetically
```sql
SELECT * FROM movies ORDER BY title ASC LIMIT 5;
```

### 4. List the next five Pixar movies sorted alphabetically
```sql
SELECT * FROM movies ORDER BY title ASC LIMIT 5 OFFSET 5;
```

---

## Notes
- SELECT → fetch data
- WHERE → filter
- LIKE → pattern matching
- ORDER BY → sorting
- LIMIT → restrict rows
- OFFSET → skip rows