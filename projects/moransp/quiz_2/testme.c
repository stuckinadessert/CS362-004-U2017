/************************
 * AUTHOR: MORANSP	*
 * CLASS: CS362		*
 * ASSIGNMENT: QUIZ 2 	*
 * DESC: Random Testing *
 * *********************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    int c = (rand()%94) + 32;
    return c;
}

char *inputString()
{
    // TODO: rewrite this function
    	int i;
   	char *s = malloc(6*sizeof(char));
	memset(s, '\0', 6);
	for (i=0;i<5;i++){
		while(1){
		s[i]=rand()%16+101;
		if (s[i] == 'e' || s[i] == 'r' || s[i] == 's' || s[i] == 't' )break;


		}
	}
    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
	//printf("%c\n", 37);
	//exit(0);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
