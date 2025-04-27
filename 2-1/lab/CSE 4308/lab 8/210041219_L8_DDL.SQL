drop table is_placed_at;
drop table works_at;
drop table rental;
drop table branch;
drop table division;
drop table district;
drop table department;
drop table employee;
drop table items;
drop table customer;

create table division(
    div_name varchar2(10) primary key,
    population number,
    location varchar2(50)
);

create table district(
    dist_name varchar2(10) primary key,
    population number,
    location varchar2(50),
    div varchar2(50) NOT NULL,
    constraint fk_dist_div foreign key (div) references division(div_name) on delete cascade
);

create table branch(
    branch_id int primary key,
    location varchar2(50),
    dist varchar2(50),
    constraint fk_branch_dist foreign key (dist) references district(dist_name) on delete cascade
);

create table department(
    dept_id int primary key,
    dept_hq varchar2(50)
);

create table is_placed_at(
    dept int,
    branch int,
    constraint fk_ipa_branch foreign key (branch) references branch(branch_id) on delete cascade,
    constraint fk_ipa_dept foreign key (dept) references department(dept_id) on delete cascade
);

create table employee(
    emp_id int primary key,
    name varchar2(10),
    DOB date,
    contact_no number
);

create table works_at(
    emp int,
    dept int,
    branch_loc int,
    dept_type varchar2(10),
    constraint fk_ipa_branch foreign key (branch_loc) references branch(branch_id) on delete cascade,
    constraint fk_ipa_dept foreign key (dept) references department(dept_id) on delete cascade,
    constraint fk_ipa_emp foreign key (emp) references employee(emp_id) on delete cascade,
);

create table customer(
    customer_id int primary key,
    name varchar2(10),
    address varchar2(50),
    contact_no number,
    constraint fk_cust foreign key (address) references district(dist_name)
);

create table items(
    item_id int primary key,
    name varchar2(10),
    desc varchar2(50),
    unit_price int,
    bought_by int,
    constraint fk_item_cust foreign key (bought_by) references customer(customer_id) on delete cascade,
);

create table rental(
    emp int,
    item int,
    time_period varchar2(5),
    constraint fk_rental_emp foreign key (emp) references employee(emp_id) on delete cascade,
    constraint fk_rental_item foreign key (item) references items(item_id) on delete cascade
);

