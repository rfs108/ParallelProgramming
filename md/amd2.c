#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
 //const char *string1="abcdefghijklmnopqrstuvwxyz1234567890";
 //const char *s1 = string1[0];
 //const char string={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0'};
 //char string[]={'a','b','c','d'};
int main()
{
	
	


  int i;
  unsigned char result[MD5_DIGEST_LENGTH];
  char x[10]; 
    char str[3];
  FILE *fp,*f1;
  fp = fopen("hash.txt","w");
  f1 = fopen("cmb.txt","r");
   //while (fgets(str, 2, f1) != NULL)
        //printf("%s\n", str);
    //fclose(f1);
 char line[256];

    while (fgets(line, sizeof(line), f1)) {
        //fprintf(fp,"%s", line); 
    
    

    
	
	 char *t=line;
	 
	 
	
    MD5(t,strlen(t), result);

	for(i = 0; i < MD5_DIGEST_LENGTH; i++)
		{
			printf("%x", result[i]);
			sprintf(x,"%x",result[i]);
			fprintf(fp,"%s",x);
    
		}
		fprintf(fp,"\n");
	}

    //printf("%s\n",x);
  //printf("\n");
fclose(f1);
  return EXIT_SUCCESS;
}
