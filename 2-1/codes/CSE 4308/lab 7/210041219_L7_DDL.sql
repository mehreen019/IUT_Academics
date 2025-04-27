drop table shift;
drop table emp_admin;
drop table emp_librarian;
drop table emp_maintenance;
drop table book_issued;
drop table branch_holds_books;
drop table employee;
drop table branch;
drop table publisher;
drop table books;


drop table account;

create table employee(
    NID int primary key
);
create table emp_admin(
    NID int primary key,
    base_salary int,
    DOB date,
    blood_group varchar(5),
    name varchar2(20),
    housing_salary GENERATED ALWAYS AS (base_salary*0.4),
    constraint fk_admin foreign key (NID) references employee(NID) on delete cascade
);
create table emp_librarian(
    NID int primary key,
    base_salary int,
    DOB date,
    blood_group varchar(5),
    name varchar2(20),
    housing_salary GENERATED ALWAYS AS (base_salary*0.4),
    constraint fk_librarian foreign key (NID) references employee(NID) on delete cascade
);
create table emp_maintenance(
    NID int primary key,
    base_salary int,
    DOB date,
    blood_group varchar(5),
    name varchar2(20),
    housing_salary GENERATED ALWAYS AS (base_salary*0.4),
    constraint fk_maintanance foreign key (NID) references employee(NID) on delete cascade
);
create table shift(
    employee_id int,
    branch_id int,
    duration number,
    starting_time varchar2(5),
    day_of_the_week date,
    constraint pk_shift primary key (employee_id, branch_id),
    constraint fk_employee foreign key (employee_id) references employee(NID) on delete cascade,
    constraint fk_branch foreign key (branch_id) references branch(branch_id) on delete cascade
);
create table branch(
    branch_id int primary key,
    location varchar2(50),
    year_of_establishment date
);
create table books(
    ISBN int primary key,
    name varchar2(20),
    author varchar2(20),
    genre varchar2(10),
    price int
);
create table publisher(
    name varchar2(20),
    city varchar2(20),
    year_of_establishment date,
    ISBN int,
    constraint pk_publisher primary key (name, city),
    constraint fk_book foreign key (ISBN) references books(ISBN) on delete cascade
);
create table branch_holds_books(
    branch_id int,
    ISBN int,
    num_of_copies int,
    constraint pk_hold primary key (branch_id, ISBN),
    constraint fk_hold_branch foreign key (branch_id) references branch(branch_id) on delete cascade,
    constraint fk_hold_book foreign key (ISBN) references books(ISBN) on delete cascade
);
create table account(
    user_name varchar2(20) primary key,
    name varchar(20),
	DOB date,
	hometown varchar2(20),
	occupation varchar2(20)
);
create table book_issued(
    username varchar2(20),
    branch_id int,
    ISBN int,
    num_of_days int,
    issue_date date,
    constraint pk_issue primary key (branch_id, ISBN, username),
    constraint fk_issue_branch foreign key (branch_id) references branch(branch_id) on delete cascade,
    constraint fk_issue_book foreign key (ISBN) references books(ISBN) on delete cascade,
    constraint fk_issue_user foreign key (username) references account(user_name) on delete cascade
);