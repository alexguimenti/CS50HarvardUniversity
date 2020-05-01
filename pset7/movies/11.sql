select title FROM movies
join stars
on movies.id = stars.movie_id
join people
on stars.person_id = people.id
join ratings
on ratings.movie_id = movies.id
where name = 'Chadwick Boseman'
order by rating DESC
limit 5