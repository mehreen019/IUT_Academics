#include <stdio.h>

typedef struct timeSpan
{
    int Start;
    int End;
} TimeSpan;

int TwentyFourHourToFlatTime(int hour, int min);
int RectifyTimeSpan(TimeSpan *const span);
int IsTimeSpanOverlapping(const TimeSpan *const span1, const TimeSpan *const span2);
void PrintTimeSpan(const TimeSpan *const span);
void ScanTimeSpanFrom24HrTime(TimeSpan *const span);

int main(void)
{
    size_t loopCount;
    scanf("%zu", &loopCount);
    unsigned int count = 0;
    TimeSpan studySpan, meetingSpan;

    for(size_t i = 0; i < loopCount; i++)
    {
        ScanTimeSpanFrom24HrTime(&studySpan);
        ScanTimeSpanFrom24HrTime(&meetingSpan);
        if(!IsTimeSpanOverlapping(&studySpan, &meetingSpan)) count++;
    }

    printf("%d\n", count);
    return 0;
}


int TwentyFourHourToFlatTime(int hour, int min)
{
    return hour * 60 + min;
}

int RectifyTimeSpan(TimeSpan *const span)
{
    if(span->End < span->Start)
    {
        span->End += (24 * 60);
    }
}

int IsTimeSpanOverlapping(const TimeSpan *const span1, const TimeSpan *const span2)
{
    if( (span2->Start > span1->Start && span2->Start < span1->End) 
        || 
        (span2->End > span1->Start && span2->End < span1->End) 
        ||
        (span2->Start + 24 * 60 > span1->Start && span2->Start + 24 * 60 < span1->End) 
        || 
        (span2->End + 24 * 60 > span1->Start && span2->End + 24 * 60 < span1->End)) return 1;
    else return 0;
}

void PrintTimeSpan(const TimeSpan *const span)
{
    printf("%d, %d\n", span->Start, span->End);
}

void ScanTimeSpanFrom24HrTime(TimeSpan *const span)
{
    int hourStart, minStart, hourEnd, minEnd;
    scanf("%d :%d%d :%d", &hourStart, &minStart, &hourEnd, &minEnd);
    span->Start = TwentyFourHourToFlatTime(hourStart, minStart);
    span->End = TwentyFourHourToFlatTime(hourEnd, minEnd);
    RectifyTimeSpan(span);
}