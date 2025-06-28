set serveroutput on;
set linesize 200;

--task 1
select bus_id, sum(t.kilometers_traveled), sum(t.fuel_consumption), sum(t.passengers_count)
from trip t join time_dim td 
on trip_date = TO_DATE( TO_CHAR(td.year) || '-' || TO_CHAR(td.month) || '-' || TO_CHAR(td.day) , 'YYYY-MM-DD' )
group by t.bus_id, t.trip_date;


--task 2
select b.bus_model, ttd.year, ttd.month, sum(ttd.total_kilometers), sum(ttd.total_passengers), sum(ttd.total_fuel)
from (
    select t.bus_id, t.kilometers_traveled as total_kilometers, t.fuel_consumption as total_fuel, t.passengers_count as total_passengers, td.year, td.month
    from trip t join time_dim td 
    on t.trip_date = TO_DATE( TO_CHAR(td.year) || '-' || TO_CHAR(td.month) || '-' || TO_CHAR(td.day) , 'YYYY-MM-DD' )
    ) ttd join bus b 
on b.bus_id = ttd.bus_id
group by rollup(b.bus_model, ttd.year, ttd.month);

--task 3
select b.bus_model, ttd.depot_id, extract(year from ttd.trip_date) as trip_year, sum(ttd.total_kilometers), sum(ttd.total_passengers), sum(ttd.total_fuel)
from (
    select t.bus_id, t.kilometers_traveled as total_kilometers, t.fuel_consumption as total_fuel, t.passengers_count as total_passengers, t.trip_date, d.depot_id
    from trip t join depot d
    on t.depot_id = d.depot_id
    ) ttd join bus b 
on b.bus_id = ttd.bus_id
group by cube(b.bus_model, extract(year from ttd.trip_date), ttd.depot_id);

--task 4
select b.bus_model, ttd.year, ttd.month, sum(ttd.total_kilometers), sum(ttd.total_passengers), sum(ttd.total_fuel), grouping(b.bus_model) as grouped_model, grouping(ttd.year) as grouped_year, grouping(ttd.month) as grouped_month
from (
    select t.bus_id, t.kilometers_traveled as total_kilometers, t.fuel_consumption as total_fuel, t.passengers_count as total_passengers, td.year, td.month
    from trip t join time_dim td 
    on t.trip_date = TO_DATE( TO_CHAR(td.year) || '-' || TO_CHAR(td.month) || '-' || TO_CHAR(td.day) , 'YYYY-MM-DD' )
    ) ttd join bus b 
on b.bus_id = ttd.bus_id
group by rollup(b.bus_model, ttd.year, ttd.month);

--task 5
select b.bus_model, ttd.depot_id, extract(year from ttd.trip_date) as trip_year, sum(ttd.total_kilometers), sum(ttd.total_passengers), sum(ttd.total_fuel)
from (
    select t.bus_id, t.kilometers_traveled as total_kilometers, t.fuel_consumption as total_fuel, t.passengers_count as total_passengers, t.trip_date, d.depot_id
    from trip t join depot d
    on t.depot_id = d.depot_id
    ) ttd join bus b 
on b.bus_id = ttd.bus_id
group by b.bus_model, extract(year from ttd.trip_date), ttd.depot_id;