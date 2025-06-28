--Task 1
DECLARE 
    CURSOR c1 IS
    SELECT STRENGTH, AGILITY, INTELLIGENCE FROM SUPERHEROES;

    STRENGTH SUPERHEROES.STRENGTH%TYPE;
    AGILITY SUPERHEROES.AGILITY%TYPE;
    INTELLIGENCE SUPERHEROES.INTELLIGENCE%TYPE;
    SCORE INTEGER;
BEGIN
    OPEN c1;
    LOOP
        FETCH c1 INTO STRENGTH, AGILITY, INTELLIGENCE;
        EXIT WHEN c1%NOTFOUND;

        STRENGTH:= STRENGTH * 0.5;
        AGILITY:= AGILITY * 0.3;
        INTELLIGENCE:= INTELLIGENCE * 0.2;

        SCORE:= STRENGTH + AGILITY + INTELLIGENCE;

        DBMS_OUTPUT.PUT_LINE('Score: ' || SCORE);
    END LOOP;

    CLOSE c1;

END;
/

--or

SELECT superhero_id, name, 
       (strength * 0.5) + (agility * 0.3) + (intelligence * 0.2) AS score
FROM superheroes;


--Task 2
SELECT p.power_name 
FROM superhero_powers sp
JOIN powers p ON sp.power_id = p.power_id
JOIN superheroes s ON sp.superhero_id = s.superhero_id
WHERE INSTR(p.power_name, ' ') > 0
GROUP BY p.power_name
HAVING COUNT(DISTINCT s.city) >= 2;

--Task 3
WITH team_intelligence AS (
    SELECT 
        t.team_id,
        t.name AS team_name,
        AVG(s.intelligence) AS avg_team_intelligence
    FROM 
        teams t
    JOIN 
        affiliations a ON t.team_id = a.team_id
    JOIN 
        superheroes s ON a.superhero_id = s.superhero_id
    GROUP BY 
        t.team_id, t.name
),
overall_avg_intelligence AS (
    SELECT AVG(avg_team_intelligence) AS overall_avg
    FROM team_intelligence
),
teams_with_energy_heroes AS (
    SELECT DISTINCT 
        t.team_id
    FROM 
        teams t
    JOIN 
        affiliations a ON t.team_id = a.team_id
    JOIN 
        superheroes s ON a.superhero_id = s.superhero_id
    JOIN 
        superhero_powers sp ON s.superhero_id = sp.superhero_id
    JOIN 
        powers p ON sp.power_id = p.power_id
    WHERE 
        p.power_type = 'Energy'
)
SELECT 
    ti.team_id,
    ti.team_name,
    ti.avg_team_intelligence,
    oai.overall_avg AS overall_avg_intelligence
FROM 
    team_intelligence ti
JOIN 
    overall_avg_intelligence oai ON ti.avg_team_intelligence > oai.overall_avg
JOIN 
    teams_with_energy_heroes twe ON ti.team_id = twe.team_id
ORDER BY 
    ti.avg_team_intelligence DESC;

--Task 4
CREATE OR REPLACE FUNCTION BATTLE_SCORE(t1 INTEGER, t2 INTEGER)
RETURN INTEGER
IS
    T1_SCORE INTEGER;
    T2_SCORE INTEGER;
    WINNER INTEGER;
BEGIN

    SELECT AVG((strength * 0.5) + (agility * 0.3) + (intelligence * 0.2)) INTO T1_SCORE
    FROM superheroes S JOIN affiliations A
    ON S.superhero_id = A.superhero_id
    WHERE A.team_id = t1;

    SELECT AVG((strength * 0.5) + (agility * 0.3) + (intelligence * 0.2)) INTO T2_SCORE
    FROM superheroes S JOIN affiliations A
    ON S.superhero_id = A.superhero_id
    WHERE A.team_id = t2;

    IF T1_SCORE > T2_SCORE THEN
        WINNER:= t1;
    ELSE
        WINNER:= t2;
    END IF;

    RETURN WINNER;
END;
/

--Task 5
CREATE SEQUENCE superhero_stat_seq
START WITH 1
INCREMENT BY 1
NOCACHE;

CREATE TABLE IF NOT EXISTS superhero_stat_logs (
    log_id INT PRIMARY KEY,
    superhero_id INT,
    superhero_name VARCHAR(50),
    stat_changed VARCHAR(20),
    old_value INT,
    new_value INT,
    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE OR REPLACE TRIGGER superhero_stat_trigger
AFTER INSERT OR UPDATE ON superheroes
FOR EACH ROW
DECLARE
    superhero_id INT;
    superhero_name VARCHAR(50);
    stat_changed VARCHAR(20);
    old_value INT;
    new_value INT;
BEGIN 
    IF :NEW.strength != :OLD.strength THEN
        INSERT INTO superhero_stat_logs VALUES (superhero_stat_seq.NEXTVAL, :NEW.superhero_id, :NEW.superhero_name, 'Strength', :OLD.strength, :NEW.strength, CURRENT_TIMESTAMP);
    END IF;

    IF :NEW.agility != :OLD.agility THEN
        INSERT INTO superhero_stat_logs VALUES (superhero_stat_seq.NEXTVAL, :NEW.superhero_id, :NEW.superhero_name, 'Agility', :OLD.agility, :NEW.agility, CURRENT_TIMESTAMP);
    END IF;

    IF :NEW.intelligence != :OLD.intelligence THEN
        INSERT INTO superhero_stat_logs VALUES (superhero_stat_seq.NEXTVAL, :NEW.superhero_id, :NEW.superhero_name, 'Intelligence', :OLD.intelligence, :NEW.intelligence, CURRENT_TIMESTAMP);
    END IF;
END;
/

--Task 6
CREATE OR REPLACE TRIGGER superhero_NEW_TRIGGER
BEFORE INSERT ON superheroes
FOR EACH ROW
DECLARE
    superhero_count INT;
BEGIN
    SELECT COUNT(A.superhero_id) 
    INTO superhero_count
    FROM  AFFILIATIONS A
    WHERE A.TEAM_ID = :NEW.TEAM_ID;

    IF superhero_count > 3 THEN
        INSERT INTO superheros VALUES (:NEW.superhero_id, :NEW.name, :NEW.alias, :NEW.city, :NEW.strength - 5, :NEW.agility - 5, :NEW.intelligence - 5);
    END IF; --this is wrong, use update instead
END;
/

--Task 7
CREATE OR REPLACE PROCEDURE increase_city_hero_agility(city_name VARCHAR)
IS
    CURSOR hero_cursor IS 
        SELECT superhero_id 
        FROM superheroes 
        WHERE city = city_name;
    hero_record superheroes.SUPERHERO_ID%TYPE;
    updated_count INT := 0;
BEGIN
    OPEN hero_cursor;
    
    LOOP
        FETCH hero_cursor INTO hero_record;
        EXIT WHEN hero_cursor%NOTFOUND;
        
        -- Update agility by 10%
        UPDATE superheroes
        SET agility = agility * 1.1
        WHERE superhero_id = hero_record;
        
        updated_count := updated_count + 1;
    END LOOP;
    
    CLOSE hero_cursor;

END;
/

--Task 8
SELECT 
    CASE WHEN s.city IS NULL THEN 'All Cities' ELSE s.city END AS city,
    CASE WHEN p.power_type IS NULL THEN 'All Types' ELSE p.power_type END AS power_type,
    CASE WHEN t.name IS NULL THEN 'All Teams' ELSE t.name END AS team_name,
    COUNT(sp.power_id) AS power_count
FROM 
    superheroes s
JOIN 
    superhero_powers sp ON s.superhero_id = sp.superhero_id
JOIN 
    powers p ON sp.power_id = p.power_id
JOIN 
    affiliations a ON s.superhero_id = a.superhero_id
JOIN 
    teams t ON a.team_id = t.team_id
GROUP BY 
    CUBE(s.city, p.power_type, t.name)
ORDER BY 
    city, 
    power_type, 
    team_name;


--Task 9
SELECT 
    CASE WHEN s.city IS NULL THEN 'Grand Total' ELSE s.city END AS city,
    CASE WHEN t.name IS NULL THEN 'City Subtotal' ELSE t.name END AS team_name,
    ROUND(AVG(s.strength), 2) AS avg_strength,
    ROUND(AVG(s.agility), 2) AS avg_agility,
    ROUND(AVG(s.intelligence), 2) AS avg_intelligence,
    COUNT(DISTINCT s.superhero_id) AS hero_count
FROM 
    superheroes s
JOIN 
    affiliations a ON s.superhero_id = a.superhero_id
JOIN 
    teams t ON a.team_id = t.team_id
WHERE 
    s.strength > 50 AND 
    s.agility > 50 AND 
    s.intelligence > 50
GROUP BY 
    ROLLUP(s.city, t.name)
ORDER BY 
    city,
    team_name;

--Task 10
CREATE GLOBAL TEMPORARY TABLE temp_synergy_results (
        hero1_id NUMBER,
        hero1_name VARCHAR2(50),
        hero1_power_type VARCHAR2(20),
        hero2_id NUMBER,
        hero2_name VARCHAR2(50),
        hero2_power_type VARCHAR2(20),
        synergy_score NUMBER(10,2)
) ON COMMIT PRESERVE ROWS;

CREATE OR REPLACE PROCEDURE team_synergy_analysis(team_name_param IN VARCHAR2) IS
    v_team_id NUMBER;
BEGIN
    -- Get team ID
    SELECT team_id INTO v_team_id
    FROM teams
    WHERE name = team_name_param;
    
    -- Create temporary table for results (using global temporary table approach for Oracle)
    EXECUTE IMMEDIATE 'TRUNCATE TABLE temp_synergy_results';
    
    -- Find complementary pairs and calculate synergy score
    INSERT INTO temp_synergy_results (
        hero1_id, hero1_name, hero1_power_type,
        hero2_id, hero2_name, hero2_power_type,
        synergy_score
    )
    SELECT 
        h1.superhero_id AS hero1_id,
        h1.name AS hero1_name,
        'Physical' AS hero1_power_type,
        h2.superhero_id AS hero2_id,
        h2.name AS hero2_name,
        'Mental' AS hero2_power_type,
        (MAX(CASE WHEN p1.power_type = 'Physical' THEN sp1.power_level ELSE 0 END) * 
         MAX(CASE WHEN p2.power_type = 'Mental' THEN sp2.power_level ELSE 0 END)) AS synergy_score
    FROM 
        superheroes h1
    JOIN 
        affiliations a1 ON h1.superhero_id = a1.superhero_id AND a1.team_id = v_team_id
    JOIN 
        superhero_powers sp1 ON h1.superhero_id = sp1.superhero_id
    JOIN 
        powers p1 ON sp1.power_id = p1.power_id AND p1.power_type = 'Physical'
    JOIN 
        superheroes h2 ON h1.superhero_id < h2.superhero_id
    JOIN 
        affiliations a2 ON h2.superhero_id = a2.superhero_id AND a2.team_id = v_team_id
    JOIN 
        superhero_powers sp2 ON h2.superhero_id = sp2.superhero_id
    JOIN 
        powers p2 ON sp2.power_id = p2.power_id AND p2.power_type = 'Mental'
    GROUP BY 
        h1.superhero_id, h1.name, h2.superhero_id, h2.name
    ORDER BY 
        synergy_score DESC;
    
    -- Output results (Oracle uses DBMS_OUTPUT instead of RAISE NOTICE)
    DBMS_OUTPUT.PUT_LINE('Synergy Analysis for ' || team_name_param || ':');
    
    -- Count the results
    DECLARE
        v_count NUMBER;
    BEGIN
        SELECT COUNT(*) INTO v_count FROM temp_synergy_results;
        DBMS_OUTPUT.PUT_LINE('Found ' || v_count || ' complementary pairs');
    END;
    
END team_synergy_analysis;
/