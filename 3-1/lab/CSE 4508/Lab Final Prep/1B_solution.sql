-- 1. Identify directors who have directed at least 3 movies with an average rating above 8.5.
SELECT d.first_name, d.last_name
FROM directors d
JOIN movie_director md ON d.director_id = md.director_id
JOIN movies m ON md.movie_id = m.movie_id
GROUP BY d.director_id, d.first_name, d.last_name
HAVING COUNT(m.movie_id) >= 3 AND AVG(m.rating) > 8.5;

-- 2. Write SQL query to list the movies that contain two "the" (The .... the ...) in their title
SELECT title
FROM movies
WHERE UPPER(title) LIKE '%THE%THE%';

-- 3. Find all directors who have directed at least one movie with a box office revenue greater than the average box office revenue of all movies.
SELECT DISTINCT d.first_name, d.last_name
FROM directors d
JOIN movie_director md ON d.director_id = md.director_id
JOIN movies m ON md.movie_id = m.movie_id
WHERE m.box_office_millions > (SELECT AVG(box_office_millions) FROM movies);

-- 4. Retrieve all directors and the number of awards won by their movies, including directors whose movies have won no awards.
SELECT d.first_name, d.last_name, COUNT(ma.award_id) AS number_of_awards
FROM directors d
JOIN movie_director md ON d.director_id = md.director_id
LEFT JOIN movie_awards ma ON md.movie_id = ma.movie_id
GROUP BY d.director_id, d.first_name, d.last_name;

-- 5. Using implicit cursor, adjust the budget of movies with a rating below 6.0 by reducing it by 10%, but only if the movie's profit is negative.
DECLARE
  v_affected_count NUMBER := 0;
BEGIN
  FOR movie_rec IN (
    SELECT movie_id 
    FROM movies 
    WHERE rating < 6.0 AND (box_office_millions - budget_millions) < 0
  )
  LOOP
    UPDATE movies
    SET budget_millions = budget_millions * 0.9
    WHERE movie_id = movie_rec.movie_id;
    
    v_affected_count := v_affected_count + 1;
  END LOOP;
  
  DBMS_OUTPUT.PUT_LINE('Total number of movies affected: ' || v_affected_count);
END;
/

-- 6. Create a function that calculates a director's success score based on average rating (30%), ROI (40%), and awards ratio per movie (30%).
CREATE OR REPLACE FUNCTION calculate_director_success(p_director_id IN INT)
RETURN DECIMAL
IS
  v_avg_rating DECIMAL(5,2);
  v_roi_percent DECIMAL(10,2);
  v_awards_ratio DECIMAL(10,2);
  v_success_score DECIMAL(10,2);
  v_movie_count INT;
BEGIN
  -- Get average rating (30%)
  SELECT AVG(m.rating) INTO v_avg_rating
  FROM movies m
  JOIN movie_director md ON m.movie_id = md.movie_id
  WHERE md.director_id = p_director_id;
  
  -- Calculate ROI (40%)
  SELECT AVG((m.box_office_millions - m.budget_millions) / NULLIF(m.budget_millions, 0) * 100) INTO v_roi_percent
  FROM movies m
  JOIN movie_director md ON m.movie_id = md.movie_id
  WHERE md.director_id = p_director_id;
  
  -- Get count of movies by this director
  SELECT COUNT(*) INTO v_movie_count
  FROM movie_director
  WHERE director_id = p_director_id;
  
  -- Calculate awards ratio per movie (30%)
  SELECT COUNT(ma.award_id) / v_movie_count INTO v_awards_ratio
  FROM movie_director md
  LEFT JOIN movie_awards ma ON md.movie_id = ma.movie_id
  WHERE md.director_id = p_director_id;
  
  -- Calculate final success score
  v_success_score := (v_avg_rating * 0.3) + (v_roi_percent * 0.4) + (v_awards_ratio * 0.3);
  
  RETURN v_success_score;
END;
/

-- 7. Create a procedure named 'transfer_actor_role' that takes an 'actor_id_A', 'actor_id_B', and 'movie_id' as input and transfers them from one actor to another in the specified movie in movie cast.
CREATE OR REPLACE PROCEDURE transfer_actor_role(
  p_actor_id_A IN INT,
  p_actor_id_B IN INT,
  p_movie_id IN INT
)
IS
  v_role VARCHAR2(100);
BEGIN
  -- Get the role of actor A in the specified movie
  SELECT role INTO v_role
  FROM movie_cast
  WHERE movie_id = p_movie_id AND actor_id = p_actor_id_A;
  
  -- Delete the existing record for actor A
  DELETE FROM movie_cast
  WHERE movie_id = p_movie_id AND actor_id = p_actor_id_A;
  
  -- Insert a new record for actor B with the same role
  INSERT INTO movie_cast (movie_id, actor_id, role)
  VALUES (p_movie_id, p_actor_id_B, v_role);
  
  COMMIT;
  
  DBMS_OUTPUT.PUT_LINE('Role "' || v_role || '" transferred from actor ID ' || 
                      p_actor_id_A || ' to actor ID ' || p_actor_id_B || 
                      ' in movie ID ' || p_movie_id);
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Actor ' || p_actor_id_A || ' does not have a role in movie ' || p_movie_id);
  WHEN OTHERS THEN
    ROLLBACK;
    DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;
/

-- 8. Create trigger that automatically calculates and prints a movie's "Return on Investment" (ROI) percentage whenever a movie's budget or box office values are updated.
CREATE OR REPLACE TRIGGER movie_roi_trigger
AFTER UPDATE OF budget_millions, box_office_millions ON movies
FOR EACH ROW
BEGIN
  -- Calculate ROI as a percentage
  DECLARE
    v_roi DECIMAL(10,2);
  BEGIN
    IF :NEW.budget_millions > 0 THEN
      v_roi := ((:NEW.box_office_millions - :NEW.budget_millions) / :NEW.budget_millions) * 100;
      DBMS_OUTPUT.PUT_LINE('Movie ID ' || :NEW.movie_id || ' ROI updated: ' || v_roi || '%');
    ELSE
      DBMS_OUTPUT.PUT_LINE('Movie ID ' || :NEW.movie_id || ' has zero budget. Cannot calculate ROI.');
    END IF;
  END;
END;
/

-- 9. Write a PL/SQL block using a cursor to identify movies that are "underrated gems" - films with high ratings (above 7.5) but relatively low box office returns (less than 150 million).
DECLARE
  CURSOR underrated_gems_cursor IS
    SELECT title, rating, box_office_millions
    FROM movies
    WHERE rating > 7.5 AND box_office_millions < 150;
  
  v_gem_count NUMBER := 0;
BEGIN
  DBMS_OUTPUT.PUT_LINE('Underrated Gems:');
  DBMS_OUTPUT.PUT_LINE('----------------');
  
  FOR gem IN underrated_gems_cursor LOOP
    DBMS_OUTPUT.PUT_LINE(gem.title || ' - Rating: ' || gem.rating || 
                         ', Box Office: $' || gem.box_office_millions || ' million');
    v_gem_count := v_gem_count + 1;
  END LOOP;
  
  DBMS_OUTPUT.PUT_LINE('----------------');
  DBMS_OUTPUT.PUT_LINE('Total underrated gems found: ' || v_gem_count);
END;
/

-- 10. Use CUBE to analyze the movie industry performance across different genres, release decades, and budget ranges. Include total box office, average ratings, and ROI calculations.
SELECT 
  CASE 
    WHEN genre IS NULL THEN 'ALL GENRES' 
    ELSE genre 
  END AS genre,
  CASE 
    WHEN decade IS NULL THEN 'ALL DECADES' 
    ELSE decade 
  END AS decade,
  CASE 
    WHEN budget_range IS NULL THEN 'ALL BUDGETS' 
    ELSE budget_range 
  END AS budget_range,
  COUNT(*) AS movie_count,
  ROUND(SUM(box_office_millions), 2) AS total_box_office,
  ROUND(AVG(rating), 2) AS avg_rating,
  ROUND(AVG((box_office_millions - budget_millions) / NULLIF(budget_millions, 0) * 100), 2) AS avg_roi_percent
FROM (
  SELECT 
    genre,
    FLOOR(release_year / 10) * 10 || 's' AS decade,
    CASE 
      WHEN budget_millions < 50 THEN 'Low Budget (<$50M)'
      WHEN budget_millions BETWEEN 50 AND 100 THEN 'Medium Budget ($50M-$100M)'
      ELSE 'High Budget (>$100M)'
    END AS budget_range,
    box_office_millions,
    budget_millions,
    rating
  FROM movies
)
GROUP BY CUBE(genre, decade, budget_range)
ORDER BY genre, decade, budget_range;