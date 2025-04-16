SELECT COUNT(*) AS num_movies_with_rating_10
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;
