select people.name from people
join stars
on people.id = stars.person_id
join movies
on movies.id = stars.movie_id
where movies.id in
(select movies.id from movies
join stars
on movies.id = stars.movie_id
join people
on stars.person_id = people.id
where name in ('Kevin Bacon')
and birth = 1958)
and name <> 'Kevin Bacon'