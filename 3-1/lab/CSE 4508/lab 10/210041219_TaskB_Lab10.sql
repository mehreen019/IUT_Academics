/*Task 1*/
SELECT products.category, regions.region_id, SUM(total_amount) AS revenue
FROM sales
JOIN regions ON sales.region_id = regions.region_id
JOIN products ON sales.product_id = products.product_id
GROUP BY ROLLUP( regions.region_id, products.category);

/*Task 2*/
SELECT category, region_id, SUM(total_amount) AS revenue
FROM sales JOIN products ON sales.product_id = products.product_id
GROUP BY CUBE(category, region_id);