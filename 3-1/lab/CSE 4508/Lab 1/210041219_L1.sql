--task 1
CREATE TABLE PASSWORDS(
    Username varchar2(100) NOT NULL,
    Password_Length number,
    Constraint pk_passwords primary key (Username)
);

CREATE OR REPLACE FUNCTION FIND_HIGHEST_LENGTH
RETURN INTEGER IS
    p_length INTEGER;
    result INTEGER:=1;
    PERM INTEGER:= 52;
BEGIN
    SELECT max(Password_Length) INTO p_length FROM PASSWORDS;
    WHILE p_length > 0 LOOP
        result:= result*PERM;
        PERM:= PERM - 1;
        p_length:= p_length - 1;
    END LOOP;
    RETURN result;
END;
/

DECLARE
    result INTEGER;
BEGIN
    result:= FIND_HIGHEST_LENGTH;
    DBMS_OUTPUT.PUT_LINE(result);
END;
/

--task 2
CREATE OR REPLACE PROCEDURE SPACED_STRING (input IN varchar2, outputt OUT varchar2, palindrome OUT varchar2) 
IS
    string_length INTEGER := LENGTH(input);
    new_string varchar2(30000) := '';
    i number;
    cnt INTEGER:=0;
BEGIN

    --creating new string
    FOR i IN 1..string_length LOOP
        new_string:= new_string || substr(input, i,1);
        if(i< string_length) then
            new_string:= new_string || ' ';
        end if;
    end loop;
    outputt:=new_string;

    --check palindrome
    new_string:='';
    FOR i IN reverse 1..string_length LOOP
        new_string:= new_string || substr(input, i,1);
    end loop;

    FOR i IN 1..string_length LOOP
        if substr(input, i,1) = substr(new_string, i,1) then
            cnt:= cnt+1;
        end if;
    end loop;

    if cnt=string_length then
        palindrome:='yes';
    else 
        palindrome:='no';
    end if;

END;
/

DECLARE
    palindrome varchar2(10);
    outputt varchar2(3000);
BEGIN
    SPACED_STRING('apple', outputt, palindrome);
    DBMS_OUTPUT.PUT_LINE( 'reversed string: ' || outputt || CHR(10) || 'is the string a palindrome?'|| CHR(10)  ||palindrome);
END;
/


--task 3
--3.1
CREATE TABLE library_borrowing(
    b_id number not null,
    name varchar2(100) not null,
    book_title varchar2(200) not null,
    borrow_date date not null,
    due_date date not null,
    returned_date date,
    Constraint pk_library primary key (b_id)
);

--3.2
INSERT INTO library_borrowing VALUES( 1, 'John Doe', 'The Great Gatsby', TO_DATE('2024-08-01', 'yyyy-mm-dd'), TO_DATE('2024-08-15','yyyy-mm-dd'), TO_DATE('2024-08-20','yyyy-mm-dd') );
INSERT INTO library_borrowing VALUES(2,'Jane Smith', '1984', TO_DATE('2024-08-10', 'yyyy-mm-dd'), TO_DATE('2024-08-24', 'yyyy-mm-dd'), null);
INSERT INTO library_borrowing VALUES( 3, 'Alice Johnson', 'To Kill a Mockingbird', TO_DATE('2024-09-01', 'yyyy-mm-dd'), TO_DATE('2024-09-15','yyyy-mm-dd'), TO_DATE('2024-09-16','yyyy-mm-dd') );
INSERT INTO library_borrowing VALUES(4, 'Bob Brown', 'Moby Dick', TO_DATE('2024-08-20', 'yyyy-mm-dd'), TO_DATE('2024-09-03 ','yyyy-mm-dd'), TO_DATE('2024-09-02 ','yyyy-mm-dd') );
INSERT INTO library_borrowing VALUES(5, 'Charlie Adams', 'The Catcher in the Rye', TO_DATE('2024-09-05', 'yyyy-mm-dd'), TO_DATE('2024-09-19','yyyy-mm-dd'), NULL );

--3.3
CREATE OR REPLACE FUNCTION Calculate_late_fee(book_id INTEGER)
RETURN number AS
    late_fee number;
    due date;
    returned date;
BEGIN
    SELECT due_date, returned_date INTO due, returned FROM library_borrowing
    WHERE b_id=book_id;

    if (returned is NULL) then
        late_fee:= trunc(sysdate) - due;
    else 
        late_fee:= trunc(returned) - due;
    end if;

    if(late_fee<0) then
        late_fee:=0;
    end if;

    return late_fee;
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE(' late fee: ' || Calculate_late_fee(3) || '$');
END;
/

--3.4
CREATE OR REPLACE PROCEDURE List_Overdue_Books IS
CURSOR book_cursor IS
    SELECT name, book_title, trunc(sysdate) - due_date FROM library_borrowing
    WHERE returned_date IS NULL and sysdate > due_date;

    member_name library_borrowing.name%TYPE;
    book_titlee library_borrowing.book_title%TYPE;
    Overdue_days number;
BEGIN   
    OPEN book_cursor;
    LOOP
        Fetch book_cursor INTO member_name, book_titlee, Overdue_days;
        EXIT WHEN book_cursor%NOTFOUND;

        DBMS_OUTPUT.PUT_LINE('Member: ' || member_name || ' Borrowed: ' || book_titlee || ' Overdue for: ' || Overdue_days || ' days');
    END LOOP;
    CLOSE book_cursor;
END;
/

BEGIN
    List_Overdue_Books;
END;
/
