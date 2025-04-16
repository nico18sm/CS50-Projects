SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE people.name IN ('Jennifer Lawrence', 'Bradley Cooper')
GROUP BY movies.title
HAVING COUNT(DISTINCT people.name) = 2;
