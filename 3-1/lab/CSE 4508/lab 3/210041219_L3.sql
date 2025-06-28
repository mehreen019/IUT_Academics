--Task 1
--I ran the .sql file to create the table and the rows
drop table customers;
drop table Addresses;
drop table subscriptions;

CREATE TABLE Customers (
    Customer_ID NUMBER PRIMARY KEY,
    Customer_Name VARCHAR2(100),
    Date_of_Birth DATE,
    Address_ID NUMBER,
    Subscription_ID NUMBER
);
 
CREATE TABLE Addresses (
    Address_ID NUMBER PRIMARY KEY,
    Division VARCHAR2(50),
    District VARCHAR2(50)
);
 
CREATE TABLE Subscriptions (
    Subscription_ID NUMBER PRIMARY KEY,
    Subscriber_Type VARCHAR2(10),
    Subscriber_Level VARCHAR2(10),
    Lifetime_Usage NUMBER
);
 
INSERT INTO Addresses 
VALUES (1, 'Dhaka', 'Dhaka');
 
INSERT INTO Addresses 
VALUES (2, 'Khulna', 'Jessore');
 
INSERT INTO Addresses 
VALUES (3, 'Chittagong', 'Comilla');
 
INSERT INTO Addresses 
VALUES (4, 'Dhaka', 'Gazipur');
 
INSERT INTO Addresses 
VALUES (5, 'Sylhet', 'Sylhet');
 
INSERT INTO Subscriptions 
VALUES (1, 'Prepaid', 'Silver', 5000);
 
INSERT INTO Subscriptions 
VALUES (2, 'Postpaid', 'Gold', 20000);
 
INSERT INTO Subscriptions 
VALUES (3, 'Prepaid', 'Bronze', 3000);
 
INSERT INTO Subscriptions 
VALUES (4, 'Postpaid', 'Platinum', 40000);
 
INSERT INTO Subscriptions 
VALUES (5, 'Prepaid', 'Silver', 7000);
 
INSERT INTO Customers 
VALUES (1, '  john Doe', TO_DATE('1990-05-10', 'YYYY-MM-DD'), 1, 1);
 
INSERT INTO Customers 
VALUES (2, 'Jane smith  ', TO_DATE('1985-12-25', 'YYYY-MM-DD'), 2, 2);
 
INSERT INTO Customers 
VALUES (3, 'ahmed khan', TO_DATE('1975-07-15', 'YYYY-MM-DD'), 3, 3);
 
INSERT INTO Customers 
VALUES (4, 'lisa Rahman', TO_DATE('1992-03-09', 'YYYY-MM-DD'), 4, 4);
 
INSERT INTO Customers 
VALUES (5, 'Samiul Islam', TO_DATE('1988-11-19', 'YYYY-MM-DD'), 5, 5);
 

--Task 2
SELECT C.customer_name, c.customer_id, s.lifetime_usage
FROM customers C JOIN subscriptions s 
ON C.subscription_id = s.subscription_id 
WHERE ROWNUM<=5
ORDER BY S.lifetime_usage DESC;

--Task 3
SELECT CS.customer_name, CS.Date_of_Birth, A.Division, a.District
FROM (
    SELECT C.customer_name, c.Date_of_Birth, c.Address_ID, s.lifetime_usage
    FROM customers C JOIN subscriptions s 
    ON C.subscription_id = s.subscription_id 
) cs
 JOIN Addresses A 
ON cs.Address_ID = A.Address_ID
WHERE cs.lifetime_usage > (
    SELECT avg(lifetime_usage)
    FROM subscriptions
    WHERE Subscriber_Type='Prepaid' AND Subscriber_Level='Silver'
);

--Task 4
SELECT CS.customer_name, CS.Date_of_Birth, A.Division, a.District
FROM (
    SELECT C.customer_name, c.Date_of_Birth, c.Address_ID, s.lifetime_usage
    FROM customers C JOIN subscriptions s 
    ON C.subscription_id = s.subscription_id 
) cs
 JOIN Addresses A 
ON cs.Address_ID = A.Address_ID
WHERE cs.lifetime_usage > (
    SELECT avg(lifetime_usage)
    FROM subscriptions
    WHERE Subscriber_Type='Prepaid' AND Subscriber_Level='Silver'
) AND a.Division='Dhaka';

--Task 5
SELECT concat('Mr./Ms.' , customer_name) AS full_name
FROM customers;

--Task 6
SELECT initcap(customer_name) AS capitalized_name
FROM customers;

--Task 7
SELECT customer_name, instr(customer_name, 'an') AS Position_of_substr
FROM customers
WHERE instr(customer_name, 'an') > 0;

--Task 8
SELECT lower(customer_name) AS lowercase_name
FROM customers;

--Task 9
SELECT upper(customer_name) AS lowercase_name
FROM customers;

--Task 10
SELECT customer_name, length(customer_name) AS name_length
FROM customers;

--Task 11
SELECT lpad(customer_name, 15, '*') as padded_customer_name
from customers;

--Task 12
SELECT ltrim(customer_name) as trimmed_customer_name
from customers;

--Task 13
SELECT substr(customer_name, 1, 5) as customer_name
from customers;

--Task 14
SELECT a.Division, count(*) AS number_of_customer 
FROM customers cs JOIN Addresses A 
ON cs.Address_ID = A.Address_ID
GROUP BY a.Division;