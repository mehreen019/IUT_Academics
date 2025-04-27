drop table contribution;
drop table student;
drop table publishes;
drop table published_work;
drop table data_driven;
drop table network_driven;
drop table system_driven;
drop table research_group;


//task 1
create table research_group(
    group_id number primary key
);

create table data_driven(
    lab_num number,
    budget number,
    group_head varchar2(20),
    meeting_time varchar(5),
    group_id number not null,
    constraint fk_data foreign key (group_id) references research_group(group_id),
    constraint pk_data primary key (group_id, lab_num)
);

create table network_driven(
    lab_num number,
    budget number,
    group_head varchar2(20),
    meeting_time varchar(5),
    group_id number not null,
    constraint fk_network foreign key (group_id) references research_group(group_id),
    constraint pk_network primary key (group_id, lab_num)
);

create table system_driven(
    lab_num number,
    budget number,
    group_head varchar2(20),
    meeting_time varchar(5),
    group_id number not null,
    constraint fk_system foreign key (group_id) references research_group(group_id),
    constraint pk_system primary key (group_id, lab_num)
);

create table student(
    st_id number primary key,
    name varchar2(20),
    contact varchar(20),
    doj date
);

create table published_work(
    paper_id number primary key,
    title varchar2(20),
    domain varchar2(10),
    summary varchar(50),
    conference_name varchar2(20),
    pub_date date
);

create table contribution(
    st_id number not null,
    group_id number not null,
    constraint pk_contribution primary key (st_id, group_id),
    constraint fk_cr foreign key (group_id) references research_group(group_id),
    constraint fk_cs foreign key (st_id) references student(st_id)
);

create table publishes(
    paper_id number not null,
    group_id number not null,
    
    constraint pk_pub primary key (paper_id, group_id),
    constraint fk_pr foreign key (group_id) references research_group(group_id),
    constraint fk_pw foreign key (paper_id) references published_work(paper_id)
);

//task 2a
SELECT COUNT(st_id)
FROM contribution
WHERE group_id IN(
SELECT group_id FROM research_group
WHERE group_id IN (
    SELECT group_id 
    FROM publishes
    GROUP BY group_id
    HAVING COUNT(paper_id)>2
));

//task 2b
SELECT pw.* FROM published_work pw,
    (   SELECT rgc.ST_NUM, p.paper_id
        FROM publishes p, (
            SELECT COUNT(c.st_id) AS ST_NUM, c.group_id
            FROM research_group rg, contribution c
            WHERE rg.group_id=c.group_id
            GROUP by c.group_id) rgc 
        WHERE p.group_id= rgc.group_id
        ORDER BY rgc.ST_NUM) rgcp
WHERE rgcp.paper_id=pw.paper_id;

//alt sol
SELECT pw.* FROM published_work pw,
    (   SELECT p.paper_id
        FROM publishes p, (
            SELECT c.st_id, c.group_id
            FROM research_group rg, contribution c
            WHERE rg.group_id=c.group_id) rgc 
        WHERE p.group_id= rgc.group_id
        GROUP BY paper_id
        ORDER BY COUNT(p.group_id), COUNT(rgc.st_id)) rgcp
WHERE rgcp.paper_id=pw.paper_id;


//task 3
CREATE VIEW INFO AS
(
    SELECT pw.title, pw.domain, pw.summary,pw.conference_name,pw.pub_date rgcp.GROUP_NUM, rgcp.ST_NUM
    FROM published_work pw,
    (
        SELECT rgc.GROUP_NUM, rgc.ST_NUM, p.paper_id
        FROM publishes p, (
            SELECT COUNT(c.st_id) AS ST_NUM, COUNT(c.group_id) AS GROUP_NUM, c.group_id
            FROM research_group rg, contribution c
            WHERE rg.group_id=c.group_id
            GROUP by c.group_id) rgc 
        WHERE p.group_id= rgc.group_id) rgcp
    WHERE rgcp.paper_id=pw.paper_id
);
