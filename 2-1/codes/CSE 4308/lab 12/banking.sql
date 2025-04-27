DROP TABLE ACCOUNT CASCADE CONSTRAINTS;
DROP TABLE BALANCE CASCADE CONSTRAINTS;
DROP TABLE TRANSACTION CASCADE CONSTRAINTS;
DROP TABLE ACC_PROPERTY CASCADE CONSTRAINTS;

CREATE TABLE ACC_PROPERTY
(
    acc_id integer primary key,
    name varchar2(20),
    profit_rate number,
    grace int
);

CREATE TABLE ACCOUNT
(
    acc_id integer primary key,
    NAME VARCHAR2(20),
    acc_code integer,
    op_date timestamp,
    lastdateinterest timestamp,
    CONSTRAINT fk_acc FOREIGN KEY(acc_code) REFERENCES ACC_PROPERTY(acc_id)
);

CREATE TABLE BALANCE
(
    acc_no integer primary key,
    principal_amount number,
    profit_amount number,
    CONSTRAINT fk_balance FOREIGN KEY(acc_no) REFERENCES ACCOUNT(acc_id)
);

CREATE TABLE TRANSACTION
(
    tid integer primary key,
    acc_no integer,
    amount number,
    transaction_date timestamp,
    CONSTRAINT fk_trans FOREIGN KEY(acc_no) REFERENCES ACCOUNT(acc_id)
);


INSERT INTO ACC_PROPERTY VALUES(2001, 'monthly', 2.4, 1);
INSERT INTO ACCOUNT VALUES(202, 'Jack', 2001, TO_DATE('1998-01-23 05:34:45', 'YYYY-MM-DD HH:MI:SS'), TO_DATE('2003-01-23 05:34:45', 'YYYY-MM-DD HH:MI:SS'));
INSERT INTO BALANCE VALUES(202, 2345, 232);
INSERT INTO TRANSACTION VALUES(677332, 202, 23455, TO_DATE('2013-06-12 08:09:45', 'YYYY-MM-DD HH:MI:SS'));
