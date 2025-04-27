/*1.1*/

SET SERVEROUTPUT ON SIZE 1000000
DECLARE
    USERNAME VARCHAR2 (10);
BEGIN
    USERNAME := 'moushi';
    DBMS_OUTPUT.PUT_LINE ( ' Hello ' || USERNAME );
EXCEPTION
    WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE ( SQLERRM );
END ;
/


/*1.2*/


DECLARE
    st_id number;
BEGIN
    st_id := '&Student_ID';
    DBMS_OUTPUT.PUT_LINE ( 'Length of student id is: ' || LENGTH(st_id) );
EXCEPTION
    WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE ( SQLERRM );
END ;
/


/*1.3*/


DECLARE
    n1 integer;
    n2 integer;
    s integer;
BEGIN
    n1 := '&number1';
    n2 := '&number2';
    s := n1+n2;
    DBMS_OUTPUT.PUT_LINE ( 'Product is: ' || s );
EXCEPTION
    WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE ( SQLERRM );
END ;
/


/*1.4*/


DECLARE
    d date:=sysdate;
BEGIN
    DBMS_OUTPUT.PUT_LINE ( 'Todays date is: ' || TO_CHAR(d, 'DD-MON-YY HH12:MI:SS') );
EXCEPTION
    WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE ( SQLERRM );
END ;
/


/*1.5*/


CREATE OR REPLACE 
PROCEDURE CHECK_COMP(N IN integer, RES OUT BOOLEAN)
AS
BEGIN
    FOR i IN 2..N/2 LOOP
        IF(MOD(N,i ) = 0) THEN
            RES:=TRUE;
        ELSE RES:=FALSE;
        EXIT WHEN RES=TRUE;
        END IF;
    END LOOP;
END;
/


DECLARE
    N integer;
    ANS BOOLEAN;
BEGIN
    N:='&number';
    CHECK_COMP(N,ANS);
    IF(ANS = TRUE) THEN DBMS_OUTPUT.PUT_LINE('The number is composite');
    ELSE DBMS_OUTPUT.PUT_LINE('The number is not composite');
    END IF;
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE ( SQLERRM );
END ;
/


/*2.1*/


CREATE OR REPLACE PROCEDURE HIGHEST_MOV(N IN integer)
AS
    r number;
    id number;
    title VARCHAR2(50);
    year number;
    time number;
    lan VARCHAR2(10);
    coun VARCHAR2(10);
    release date;
    rev number;
BEGIN
    FOR i IN 1..N LOOP
        select MOV_TITLE, MOV_YEAR, MOV_LANGUAGE, MOV_COUNTRY
        into title,year,lan,coun
        from  
        (
        select row_number() over (ORDER BY T.REV) rn, t.*
            from (SELECT M.*, R.REV
                FROM MOVIE M, (
                SELECT MOV_ID, AVG(REV_STARS) AS REV
                FROM RATING
                GROUP BY MOV_ID) R
                WHERE R.MOV_ID = M.MOV_ID) t
        )
        where rn=I;

        DBMS_OUTPUT.PUT_LINE(title || ' ' || year || ' ' || lan || ' ' || coun);
    END LOOP;
END;
/

/*SELECT *
FROM MOVIE M, (
        SELECT MOV_ID
        FROM RATING
        GROUP BY MOV_ID
        ORDER BY AVG(REV_STARS) ) R
WHERE R.MOV_ID = M.MOV_ID;*/

BEGIN
HIGHEST_MOV(5);
END ;
/


/*2.2*/


CREATE OR REPLACE FUNCTION MOV_STATUS(t VARCHAR2)
RETURN BOOLEAN
IS
    r number;
    title VARCHAR2(50);
    s BOOLEAN;
BEGIN
    SELECT M.MOV_TITLE, C.ACTORS
    INTO title, r
    FROM (SELECT COUNT(ACT_ID) AS ACTORS, MOV_ID
    FROM CASTS
    GROUP BY MOV_ID) C, MOVIE M
    WHERE M.MOV_ID=C.MOV_ID AND M.MOV_TITLE=T;
    IF(r=1) THEN s:=TRUE;
    ELSE s:=FALSE;
    END IF;
RETURN s;
END ;
/


/*SELECT M.MOV_TITLE, C.ACTORS
FROM (SELECT COUNT(ACT_ID) AS ACTORS, MOV_ID
FROM CASTS
GROUP BY MOV_ID) C, MOVIE M
WHERE M.MOV_ID=C.MOV_ID;*/


DECLARE
    title VARCHAR2(50);
BEGIN
    title:='&movie_name';
    IF(MOV_STATUS(title)=TRUE) THEN DBMS_OUTPUT.PUT_LINE(title || ' SOLO');
    ELSE DBMS_OUTPUT.PUT_LINE(title || ' ENSEMBLE');
    END IF;
END ;
/


/*2.3*/


CREATE OR REPLACE PROCEDURE OSCAR_NOMINEE(N IN integer)
AS
    FN VARCHAR2(50);
    LN VARCHAR2(50);
BEGIN
    FOR i IN 1..6 LOOP
        select DIR_FIRSTNAME, DIR_LASTNAME
        into FN,LN
        from  
        (
        select row_number() over (ORDER BY T.STARS) rn, t.*
            from (SELECT D.DIR_FIRSTNAME, D.DIR_LASTNAME, R.STARS
                FROM DIRECTOR D, DIRECTION DN,
                (SELECT MOV_ID, COUNT(REV_ID) AS REVIEWERS, AVG(REV_STARS) AS STARS
                FROM RATING
                GROUP BY MOV_ID 
                HAVING COUNT(REV_ID)>10 AND AVG(REV_STARS)>=7) R
                WHERE D.DIR_ID=DN.DIR_ID AND DN.MOV_ID=R.MOV_ID) t
        )
        where rn=i;
        DBMS_OUTPUT.PUT_LINE(FN || ' ' || LN);
    END LOOP;
END;
/

BEGIN
OSCAR_NOMINEE(7);
END;
/

/*SELECT D.DIR_FIRSTNAME, D.DIR_LASTNAME
FROM DIRECTOR D, DIRECTION DN,
(SELECT MOV_ID, COUNT(REV_ID) AS REVIEWERS, AVG(REV_STARS)
FROM RATING
GROUP BY MOV_ID
HAVING COUNT(REV_ID)>10 AND AVG(REV_STARS)>=7) R
WHERE D.DIR_ID=DN.DIR_ID AND DN.MOV_ID=R.MOV_ID;*/



/*2.4*/


CREATE OR REPLACE FUNCTION MOV_CATEGORY(t VARCHAR2)
RETURN VARCHAR2
IS
    rat number;
    year NUMBER;
    title VARCHAR2(50);
    s VARCHAR2(50);
BEGIN
    SELECT M.MOV_TITLE,M.MOV_YEAR, R.AVG_RATING
    INTO title, year, rat
    FROM MOVIE M,(
        SELECT MOV_ID, AVG(REV_STARS) AS AVG_RATING
        FROM RATING
        GROUP BY MOV_ID) R
    WHERE M.MOV_ID=R.MOV_ID and M.MOV_TITLE=t;
    IF( year between 1950 AND 1959 AND rat>6.5 ) THEN s:='Fantastic fifties';
    ELSIF(year between 1960 AND 1969 AND rat>6.7) THEN s:='Sweet sixties';
    ELSIF(year between 1970 AND 1979 AND rat>6.9) THEN s:='Super seventies';
    ELSIF(year between 1980 AND 1989 AND rat>7.1) THEN s:='Ecstatic eighties';
    ELSIF(year between 1990 AND 1999 AND rat>7.3) THEN s:='Neat nineties';
    ELSE s:='Garbage';
    END IF;
RETURN s;
END ;
/


/*SELECT M.MOV_TITLE,M.MOV_YEAR, R.AVG_RATING
FROM MOVIE M,(
    SELECT MOV_ID, AVG(REV_STARS) AS AVG_RATING
    FROM RATING
    GROUP BY MOV_ID) R
WHERE M.MOV_ID=R.MOV_ID;*/


DECLARE
    title VARCHAR2(50);
BEGIN
    title:='&movie_name';
    DBMS_OUTPUT.PUT_LINE(MOV_CATEGORY(title));
END ;
/