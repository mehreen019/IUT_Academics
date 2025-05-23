CREATE TABLE PRODUCT_INFO
(
	P_ID VARCHAR(50),
	MODEL VARCHAR(50) NOT NULL, 
	MANUFACTURER VARCHAR(50) NOT NULL,
	PRICE NUMBER NOT NULL,
	CONSTRAINT PK PRIMARY KEY(P_ID)
);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('10203', 'X515EA', 'ASUS', 51900);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('20301', 'Latitude 14 3420', DELL, 82500);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('20311', 'Inspiron 15 3525', 'DELL', 58900);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('20114', 'P2451FA', 'ASUS', 58500);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('20122', 'X415EA', 'ASUS', 57000);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('30301', 'Vostro 14 3400', 'DELL', 83000);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('00788', '15s-eq3619AU', 'HP', 73200);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('30583', 'P1412CEA', 'ASUS', 63000);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('30543', '15s-fq5486TU', 'HP', 58500);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('10766', 'IdeaPad Slim 3i', 'Lenovo', 56900);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('00821', 'K14', 'Lenovo', 66500);
INSERT INTO PRODUCT_INFO (P_ID, MODEL, MANUFACTURER, PRICE) VALUES ('30345', 'SModern 15 B11M', 'MSI', 74000);
SELECT * FROM PRODUCT_INFO;
SELECT MODEL,MANUFACTURER FROM PRODUCT_INFO;
SELECT MODEL,MANUFACTURER FROM PRODUCT_INFO WHERE PRICE<=70000;
SELECT MODEL,MANUFACTURER FROM PRODUCT_INFO WHERE PRICE>=55000 AND PRICE<=75000;
SELECT MODEL,P_ID FROM PRODUCT_INFO WHERE MANUFACTURER = 'ASUS';
SELECT MODEL,PRICE FROM PRODUCT_INFO WHERE MANUFACTURER = 'DELL';
SELECT MODEL,P_ID FROM PRODUCT_INFO WHERE MANUFACTURER = 'HP' OR PRICE>55000;
SELECT MODEL,P_ID FROM PRODUCT_INFO WHERE MANUFACTURER = 'ASUS';
SELECT MANUFACTURER FROM PRODUCT_INFO;
DROP TABLE PRODUCT_INFO;





