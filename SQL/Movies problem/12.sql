SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE name = "Helena Bonham Carter" 
OR name = "Johnny Depp"
GROUP BY title
HAVING COUNT(title) >= 2;