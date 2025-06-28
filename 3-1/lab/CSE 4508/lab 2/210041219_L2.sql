set serveroutput on;

--Task 1
DROP TABLE employees;

CREATE TABLE employees(
    ID number not null,
    name varchar2(100) NOT NULL,
    salary number not null,
    designation varchar2(100),
    Constraint pk_employees primary key (ID)
);

INSERT INTO employees VALUES(1, 'nowshin', 20000, 'manager');
INSERT INTO employees VALUES(2, 'fariya', 40000, 'ceo');
INSERT INTO employees VALUES(3, 'moon', 10000, 'general employee');
INSERT INTO employees VALUES(4, 'sreya', 30000, 'assistant manager');

DECLARE 
    affected_rows number:=0;
BEGIN

UPDATE employees
SET salary = CASE
    WHEN salary < 30000 AND designation ='manager' THEN salary + salary*0.1
    WHEN salary > 20000 AND designation ='assistant manager' THEN salary - salary*0.1
    ELSE salary
    END
    WHERE (salary < 30000 AND designation ='manager') OR (salary > 20000 AND designation ='assistant manager');

affected_rows:= affected_rows + SQL%ROWCOUNT;

DBMS_OUTPUT.PUT_LINE('Number of affected rows are: ' || affected_rows);
END;
/

--Task 2
DROP TABLE transactions;

CREATE TABLE transactions(
    user_id number not null,
    amount number,
    t_date date,
    Constraint pk_transactions primary key (user_id)
);

INSERT INTO transactions VALUES( 1, 2005000, TO_DATE('2024-10-10', 'yyyy-mm-dd') );
INSERT INTO transactions VALUES( 2, 1000000, TO_DATE('2024-10-10', 'yyyy-mm-dd') );
INSERT INTO transactions VALUES( 3, 500000, TO_DATE('2024-10-10', 'yyyy-mm-dd') );

CREATE TABLE loan_type(
    scheme number not null,
    installments number,
    scharge number,
    min_trans number,
    Constraint pk_loantype primary key (scheme)
);

INSERT INTO loan_type VALUES(1, 30, 5, 2000000);
INSERT INTO loan_type VALUES(2, 20, 10, 1000000);
INSERT INTO loan_type VALUES(3, 15, 15, 500000);

CREATE OR REPLACE FUNCTION assign_loan_scheme(u_id number)
RETURN number AS

CURSOR loan_cursor IS
    SELECT scheme, min_trans FROM loan_type;

    total_trans number;

    output_scheme loan_type.scheme%TYPE;
    output_trans loan_type.min_trans%TYPE;

BEGIN
    SELECT SUM(amount) INTO total_trans FROM transactions
    WHERE user_id=u_id;

    OPEN loan_cursor;
    LOOP
        Fetch loan_cursor INTO output_scheme, output_trans;
        EXIT WHEN loan_cursor%NOTFOUND;

        IF output_trans <= total_trans THEN
            EXIT; 
        END IF;

    END LOOP;
    CLOSE loan_cursor;

    RETURN output_scheme;
END;
/

BEGIN 
DBMS_OUTPUT.PUT_LINE('Loan scheme for the person with user id 2 is: ' || assign_loan_scheme(2));
END;
/

--Task 3

DROP TABLE customer;
DROP TABLE pricingplan;
DROP TABLE phonecall;
DROP TABLE bill;

CREATE TABLE customer(
    SSN number not null,
    Name varchar2(100),
    surname varchar2(100),
    phonenum number,
    plan_code number,
    Constraint pk_customer primary key (SSN)
);

CREATE TABLE pricingplan(
    plan_code number not null,
    confee number,
    pricePerSecond number,
    Constraint pk_pricingplan primary key (plan_code)
);

CREATE TABLE phonecall(
    SSN number not null,
    call_date date,
    timee varchar2(10),
    callednum number,
    secondss number,
    Constraint pk_phonecall primary key (SSN)
);

CREATE TABLE bill(
    SSN number not null,
    monthh number,
    yearr number,
    amount number,
    Constraint pk_bill primary key (SSN)
);


--Task 3.1
CREATE TRIGGER init_bill
AFTER INSERT ON customer
FOR EACH ROW
BEGIN
    INSERT INTO bill VALUES(:NEW.SSN, EXTRACT(MONTH FROM sysdate), EXTRACT(YEAR FROM sysdate), 0 );
END;
/ 

--Task 3.2
CREATE TRIGGER update_bill
AFTER INSERT ON phonecall
FOR EACH ROW
DECLARE
    plann customer.plan_code%TYPE;
    secondPrice pricingplan.pricePerSecond%TYPE;
    connectionfee pricingplan.confee%TYPE;
BEGIN
    SELECT plan_code INTO plann FROM customer
    WHERE SSN= :NEW.SSN;

    SELECT pricePerSecond, confee INTO secondPrice, connectionfee FROM pricingplan
    WHERE plan_code=plann;

    UPDATE bill
    SET amount = amount + (secondPrice* :NEW.secondss) + connectionfee
    WHERE SSN = :NEW.SSN;
END;
/

--Task 4
--Task 4.1
CREATE TABLE IUT(
    ID varchar2(15),
    Date_of_Admission date,
    Department char,
    Program char,
    Section char,
    Constraint pk_IUT primary key(ID)
);

CREATE SEQUENCE student_seq
START WITH 1
INCREMENT BY 1
NOCACHE;

CREATE OR REPLACE FUNCTION GEN_ID(doa date, dept varchar2, prog varchar2, sec varchar2)
RETURN varchar2 AS
    new_id varchar2(15):='' ;
    nextt number;
BEGIN
    new_id := TO_CHAR(doa, 'YY') || '00' || dept || prog || sec;

    nextt:=student_seq.NEXTVAL;

    IF(nextt< 10) THEN
        new_id:= new_id || TO_CHAR(nextt, '09');
    ELSE new_id:= new_id || TO_CHAR(nextt, '99');

    END IF;

    RETURN new_id;
END;
/

CREATE OR REPLACE TRIGGER new_student
BEFORE INSERT on IUT
FOR EACH ROW
BEGIN
    :NEW.ID := GEN_ID( :NEW.Date_of_Admission, :NEW.Department, :NEW.Program, :NEW.Section );
END;
/

--Taskk 4.2
CREATE OR REPLACE PROCEDURE update_balances AS
    CURSOR account_cursor IS
        SELECT a.ID, a.Balance, a.LastDateofInterest, ap.interestRate, ap.GP
        FROM Accounts a
        JOIN AccountProperties ap
        ON a.ID = ap.ID;

    current_date DATE := SYSDATE;
    days_diff NUMBER;
    interest_amount NUMBER := 0;
BEGIN
    OPEN account_cursor;
    LOOP
        FETCH account_cursor INTO account_cursor%ROWTYPE;
        EXIT WHEN account_cursor%NOTFOUND;

        days_diff := current_date - account_cursor.LastDateofInterest;

        IF account_cursor.GP = 1 THEN
            interest_amount := account_cursor.Balance * (account_cursor.interestRate / 100) * days_diff;
        ELSIF account_cursor.GP = 2 THEN
            IF days_diff >= 30 THEN
                interest_amount := account_cursor.Balance * (account_cursor.interestRate / 100) * (days_diff / 30);
            END IF;
        ELSIF account_cursor.GP = 3 THEN
            IF days_diff >= 365 THEN
                interest_amount := account_cursor.Balance * (account_cursor.interestRate / 100) * (days_diff / 365);
            END IF;
        END IF;

        IF interest_amount > 0 THEN
            UPDATE Accounts
            SET Balance = Balance + interest_amount,
                LastDateofInterest = current_date
            WHERE ID = account_cursor.ID;

            interest_amount := 0;
        END IF;

    END LOOP;
    
    CLOSE account_cursor;
    COMMIT;
END;
/
