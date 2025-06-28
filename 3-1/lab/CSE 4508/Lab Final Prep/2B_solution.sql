--task 1
SELECT a.attack_name, COUNT(pa.pokemon_id) as num_pokemon
FROM attacks a
JOIN pokemon_attacks pa ON a.attack_id = pa.attack_id
WHERE INSTR(a.attack_name, ' ') > 0
GROUP BY a.attack_name
HAVING COUNT(DISTINCT pa.pokemon_id) >= 2;

--task 2
SELECT DISTINCT t.first_name, t.last_name
FROM trainer t
JOIN owner o ON t.trainer_id = o.trainer_id
JOIN pokemon_attacks pa ON o.pokemon_id = pa.pokemon_id
JOIN attacks a ON pa.attack_id = a.attack_id
WHERE a.attack_type = 'Fire' AND a.attack_power > 50;

--task 3
SELECT p.name AS pokemon_name, 
       COALESCE(a.attack_name, 'NULL') AS attack_name, 
       COALESCE(a.attack_power, 'NULL') AS attack_power
FROM pokemon p
LEFT JOIN pokemon_attacks pa ON p.pokemon_id = pa.pokemon_id
LEFT JOIN attacks a ON pa.attack_id = a.attack_id;

--task 4
SELECT t.first_name, t.last_name, p.name AS pokemon_name, p.type
FROM trainer t
JOIN owner o ON t.trainer_id = o.trainer_id
JOIN pokemon p ON o.pokemon_id = p.pokemon_id
WHERE (p.hp + p.attack + p.defense + p.speed) = (
    SELECT MAX(p2.hp + p2.attack + p2.defense + p2.speed)
    FROM owner o2
    JOIN pokemon p2 ON o2.pokemon_id = p2.pokemon_id
    WHERE o2.trainer_id = t.trainer_id
);

--task 5
CREATE OR REPLACE FUNCTION avg_attack_power(pokemon_name VARCHAR2) 
RETURN NUMBER IS
    avg_power NUMBER;
BEGIN
    SELECT AVG(a.attack_power)
    INTO avg_power
    FROM pokemon p
    JOIN pokemon_attacks pa ON p.pokemon_id = pa.pokemon_id
    JOIN attacks a ON pa.attack_id = a.attack_id
    WHERE p.name = pokemon_name;

    RETURN NVL(avg_power, 0);
END;
/

--task 6
CREATE OR REPLACE TRIGGER update_stats_on_evolution
BEFORE UPDATE OF name ON pokemon
FOR EACH ROW
WHEN (NEW.name != OLD.name)  -- Evolution detected
BEGIN
    :NEW.hp := :NEW.hp * 1.2;
    :NEW.attack := :NEW.attack * 1.2;
    :NEW.defense := :NEW.defense * 1.2;
    :NEW.speed := :NEW.speed * 1.2;
END;
/

--task 7
DECLARE
    ash_score NUMBER;
    gary_score NUMBER;
BEGIN
    SELECT MAX(p.hp + p.attack + p.defense + p.speed) INTO ash_score
    FROM trainer t
    JOIN owner o ON t.trainer_id = o.trainer_id
    JOIN pokemon p ON o.pokemon_id = p.pokemon_id
    WHERE t.first_name = 'Ash';

    SELECT MAX(p.hp + p.attack + p.defense + p.speed) INTO gary_score
    FROM trainer t
    JOIN owner o ON t.trainer_id = o.trainer_id
    JOIN pokemon p ON o.pokemon_id = p.pokemon_id
    WHERE t.first_name = 'Gary';

    IF ash_score > gary_score THEN
        DBMS_OUTPUT.PUT_LINE('Ash wins!');
    ELSIF gary_score > ash_score THEN
        DBMS_OUTPUT.PUT_LINE('Gary wins!');
    ELSE
        DBMS_OUTPUT.PUT_LINE('It''s a tie!');
    END IF;
END;
/

--task 8
DECLARE
    CURSOR pokemon_cursor IS 
        SELECT p.name FROM pokemon p
        JOIN owner o ON p.pokemon_id = o.pokemon_id
        WHERE o.trainer_id = :trainer_id;
    v_pokemon_name VARCHAR2(50);
BEGIN
    OPEN pokemon_cursor;
    LOOP
        FETCH pokemon_cursor INTO v_pokemon_name;
        EXIT WHEN pokemon_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_pokemon_name);
    END LOOP;
    CLOSE pokemon_cursor;
END;
/

--task 9
SELECT t.city, p.type, COUNT(p.pokemon_id) AS num_pokemon
FROM trainer t
JOIN owner o ON t.trainer_id = o.trainer_id
JOIN pokemon p ON o.pokemon_id = p.pokemon_id
GROUP BY CUBE (t.city, p.type);

--task 10
CREATE OR REPLACE PROCEDURE delete_pokemon_with_low_stats(threshold NUMBER) IS
BEGIN
    DELETE FROM pokemon
    WHERE (hp + attack + defense + speed) < threshold;
    COMMIT;
END;
/
