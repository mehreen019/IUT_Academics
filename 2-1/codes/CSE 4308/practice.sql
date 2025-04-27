create table emp(
    int p primary key,
   constraint fk foreign key(p) references emp(p));

select customer_id, customer_name, address
from customers c, orders o,, products p, transactions t 
where c.customer_id=t.customer_id and t.order_id=o.order_id and o.order_id=p.product_id
and (p.product_name='Rice' or p.product_id='Flour');

select customer_id, customer_name
from customers c, trans

select *
from rating
where (mov_id=902 or mov_id=911) and rev_id=9004;

CREATE OR REPLACE FUNCTION BSS(EMP_ID IN NUMBER)
RETURN EMP.BASIC_SALARY%TYPE
AS
BS EMP.BASIC_SALARY%TYPE;
TS EMP.BASIC_SALARY%TYPE;
BEGIN
    SELECT BASIC_SALARY
    INTO BS FROM EMP
    WHERE EMP.ID=EMP_ID;

    TS:=BS + BS*0.4 + 50;
RETURN TS;
END;
/

create table section(
    room numeric(3,0) check (room between 100 and 200),
    year numeric(4,0) check (year>2002),
    sem varchar2(10) check (sem in ('fall', 'winter')),
    building varchar2(10) check (building like 'S%'),
    classroom varchar2(10),
    constraint d unique (year, sem)
);
drop table section;