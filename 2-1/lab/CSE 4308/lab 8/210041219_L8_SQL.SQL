//A
SELECT div_name, COUNT(dist_name) 
FROM district
GROUP BY div_name;

//B
SELECT address
FROM customer
GROUP BY address
HAVING COUNT(customer_id)>200;

//C
SELECT COUNT(item_id)
FROM items i join customer c on c.customer_id=i.bought_by
GROUP BY c.customer_id
WHERE c.name='Alfred';