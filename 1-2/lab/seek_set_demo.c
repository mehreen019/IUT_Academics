#include <stdio.h>
#include <stdlib.h>
int main ()
{
   FILE *fp;
   char data[60];
   fp = fopen ("test.txt","w");
   fputs("Fresh2refresh.com is a programming tutorial website", fp);
   fgets ( data, 60, fp );
   printf("Before fseek - %s", data);

   // To set file pointet to 21th byte/character in the file
   fseek(fp, 21, SEEK_SET);
   fflush(data);
   fgets ( data, 60, fp );
   printf("After SEEK_SET to 21 - %s", data);

   // To find backward 10 bytes from current position
   fseek(fp, -10, SEEK_CUR);
   fflush(data);
   fgets ( data, 60, fp );
   printf("After SEEK_CUR to -10 - %s", data);

   // To find 7th byte before the end of file
   fseek(fp, -7, SEEK_END);
   fflush(data);
   fgets ( data, 60, fp );
   printf("After SEEK_END to -7 - %s", data);

   // To set file pointer to the beginning of the file
   fseek(fp, 0, SEEK_SET); // We can use rewind(fp); also

   fclose(fp);
   return 0;
}
