SELECT name FROM people
WHERE people.id IN(
SELECT stars.person_id FROM stars
WHERE stars.movie_id IN(
SELECT movies.id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE name = "Kevin Bacon" and birth = 1958))
AND NOT name = "Kevin Bacon"
ORDER BY name;
