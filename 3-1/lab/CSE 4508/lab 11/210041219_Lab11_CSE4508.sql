DROP TABLE SalesRecords;

CREATE TABLE SalesRecords (
    OrderID NUMBER PRIMARY KEY,
    CustomerName  VARCHAR2(50) NOT NULL,
  	ProductsPurchased VARCHAR2(50),
  	SalesInfo VARCHAR2(50),
	OrderDate DATE
);

INSERT INTO SalesRecords VALUES ('O1001', 'John Doe', 'P01-Logitech MX Master, P02-Samsung Galaxy S25', 'S01-Alice (Seattle)', '2025-01-15');

SELECT * FROM SalesRecords;

/*Task 1*/

--Atomicity isn't maintained in current table

DROP TABLE SalesRecords1NF;

CREATE TABLE SalesRecords1NF (
	OrderID NUMBER PRIMARY KEY,
    CustomerName  VARCHAR2(50) NOT NULL,
  	PurchasedProductId NUMBER,
	PurchasedProductName VARCHAR2(50),
  	SalesPersonId NUMBER,
  	SalesPersonName VARCHAR2(50),
	SalesPersonLocation VARCHAR2(50),
	OrderDate DATE
);

INSERT INTO SalesRecords1NF VALUES ('O1001', 'John Doe', '1', 'Logitech MX Master', '1' , 'Alice', 'Seattle', '2025-01-15');

SELECT * FROM SalesRecords1NF;

/*Task 2*/

--There exists 3 partial dependencies in the current table. product name is dependent on product id, and sales person name and location is dependent on sales person id. Thus we need to separate them to ensure no composite key dependency exists.

DROP TABLE SalesRecords2NF;
DROP TABLE Products;
DROP TABLE SalesPersons;

CREATE TABLE Products (
	ProductId NUMBER PRIMARY KEY,
	ProductName VARCHAR2(50)
);

CREATE TABLE SalesPersons (
	SalesPersonId NUMBER PRIMARY KEY,
  	SalesPersonName VARCHAR2(50),
	SalesPersonLocation VARCHAR2(50)
);

CREATE TABLE SalesRecords2NF (
	OrderID NUMBER PRIMARY KEY,
    CustomerName  VARCHAR2(50) NOT NULL,
  	ProductId NUMBER,
  	SalesPersonId NUMBER,
  	OrderDate DATE,
  	FOREIGN KEY (ProductId) REFERENCES Products(ProductId),
	FOREIGN KEY (SalesPersonId) REFERENCES SalesPersons(SalesPersonId)
);

INSERT INTO Products VALUES ('1', 'Logitech MX Master');

INSERT INTO SalesPersons VALUES ('1' , 'Alice', 'Seattle');

INSERT INTO SalesRecords2NF VALUES ('O1001', 'John Doe', '1', '1', '2025-01-15');

SELECT * FROM SalesRecords2NF;
SELECT * FROM Products;
SELECT * FROM SalesPersons;

--If we want to retrieve the original table

SELECT S.OrderID, 
    S.CustomerName, 
    S.OrderDate, 
    S.ProductId, 
    P.ProductName, 
    SS.SalesPersonId, 
    SS.SalesPersonName, 
    SS.SalesPersonLocation FROM 
(SalesRecords2NF S  JOIN Products P ON S.ProductId = P.ProductId)
SP JOIN SalesPersons SS ON SP.SalesPersonId = SS.SalesPersonId;


/*Task 3*/

--There exists a transitive dependency between elements of SalesPersonsTable, as Id and Location are transitively dependent. To eliminate this, we can create a separate table for names and locations of sales persons

DROP TABLE SalesPersonNames;
DROP TABLE SalesPersonLocations;

CREATE TABLE SalesPersonNames (
	SalesPersonId NUMBER PRIMARY KEY,
  	SalesPersonName VARCHAR2(50),
	FOREIGN KEY (SalesPersonName) REFERENCES SalesPersonLocations(SalesPersonName)
);

CREATE TABLE SalesPersonLocations (
  	SalesPersonName VARCHAR2(50) PRIMARY KEY,
	SalesPersonLocation VARCHAR2(50)
);

INSERT INTO SalesPersonLocations VALUES ('Alice', 'Seattle');
INSERT INTO SalesPersonNames VALUES ('1' , 'Alice');

SELECT * FROM SalesPersonNames;
SELECT * FROM SalesPersonLocations;

--If we want to gain the original table from this:

SELECT S.OrderID, 
    S.CustomerName, 
    S.OrderDate, 
    S.ProductId, 
    P.ProductName, 
    S.SalesPersonId, 
    SN.SalesPersonName, 
    SL.SalesPersonLocation FROM 
((SalesRecords2NF S  JOIN Products P ON S.ProductId = P.ProductId)
SP JOIN SalesPersonNames SN ON SP.SalesPersonId = SN.SalesPersonId)
SPN JOIN SalesPersonLocations SL ON SPN.SalesPersonName = SL.SalesPersonName;