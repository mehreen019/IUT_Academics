#pragma once

#define MAX_CITY_LEN    10
#define MAX_COUNTRY_LEN 10
#define MAX_NAME_LEN    20

typedef struct _address
{
    int     HouseNumber;
    int     RoadNumber;
    char    City[MAX_CITY_LEN + 1];
    char    Country[MAX_COUNTRY_LEN + 1];
    int     ZipCode;
} Address;


typedef struct _studentInfo
{
    char    Name[MAX_NAME_LEN + 1];
    int     ID;
    float   CGPA;
    Address PresentAddress;
    Address PermanentAddress;
} StudentInfo;
