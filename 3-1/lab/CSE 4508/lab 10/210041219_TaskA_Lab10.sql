/*Task 1*/

DECLARE
    employee_name VARCHAR(20);
    salary NUMBER;
BEGIN
    SELECT salary, name INTO salary, employee_name FROM employees WHERE employee_id = 101;

    DBMS_OUTPUT.PUT_LINE('Name: ' || employee_name );
    DBMS_OUTPUT.PUT_LINE('Salary: ' || salary );
END ;
/

/*Task 2*/

CREATE OR REPLACE FUNCTION employee_count(dept_id INTEGER) 
RETURN INTEGER IS emp_count INTEGER;
BEGIN
    SELECT COUNT(*)
    INTO emp_count
    FROM employees
    WHERE employees.department_id = dept_id;
    RETURN emp_count;
END;
/

BEGIN
DBMS_OUTPUT.PUT_LINE(
    'Count of employees in dept 2: ' ||
    employee_count(2)
);
END;
/

/*Task 3*/

DROP TRIGGER update_hire_date_trg;

CREATE TRIGGER update_hire_date_trg
AFTER INSERT ON EMPLOYEES
FOR EACH ROW
BEGIN
    UPDATE DEPARTMENTS
    SET DEPARTMENTS.LAST_HIRE_DATE = :NEW.HIRE_DATE
    WHERE DEPARTMENTS.DEPARTMENT_ID = :NEW.DEPARTMENT_ID
    AND :NEW.HIRE_DATE > DEPARTMENTS.LAST_HIRE_DATE;
END;
/

/*check trigger*/
-- Check current last_hire_date for HR department
SELECT department_id, name, last_hire_date
FROM departments
WHERE department_id = 1;

-- Insert a new employee with a more recent hire date
INSERT INTO employees (employee_id, name, salary, department_id, hire_date)
VALUES (115, 'New HR Employee', 60000, 1, DATE '2023-12-01');

-- Verify that the trigger updated the last_hire_date
SELECT department_id, name, last_hire_date
FROM departments
WHERE department_id = 1;

-- Test with another employee with an older hire date
INSERT INTO employees (employee_id, name, salary, department_id, hire_date)
VALUES (116, 'Another HR Employee', 62000, 1, DATE '2023-06-01');

-- Verify that last_hire_date didn't change (since it's an older date)
SELECT department_id, name, last_hire_date
FROM departments
WHERE department_id = 1;

COMMIT;

/*Task 4*/

DECLARE 
    emp_name employees.name%TYPE;
    CURSOR c IS
    SELECT name FROM EMPLOYEES
    WHERE DEPARTMENT_ID = 2;
BEGIN
    OPEN c;
    LOOP
        FETCH  c INTO emp_name;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('NAME: ' || emp_name);
    END LOOP;
    CLOSE c;
END;
/