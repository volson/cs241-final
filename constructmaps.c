#include "checkers.h"

int movetodeca(char  *inputmove)
{
  int sumthing = 0;
  for (int i = 0; i < 32; i++)
    {
      sumthing = sumthing + (((inputmove[i]) - 48) * pow((31-i), 5));
    }
  return sumthing;
}

int movetodecr(char  *inputmove)
{
  int sumthing = 0;
  for (int i = 0; i < 32; i++)
    {
      sumthing = sumthing + (((inputmove[i]) - 48) * pow((31-i), 6));
    }
  return sumthing;
}


int movecomparatora(char *inputmove1, char  *inputmove2)
{
  if(movetodeca(inputmove1) >  movetodeca(inputmove2))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int movecomparatorr(char *inputmove1, char  *inputmove2)
{
  if(movetodecr(inputmove1) > movetodecr(inputmove2))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}


void freestoragecontainer(struct movemap **tempstoragecontainer, int capacity)
{
  for (int i = 0; i < capacity; i++)
    {
      free(tempstoragecontainer[i]);
    }
  free(tempstoragecontainer);
}

int numpieces(char *tempmove)
{
  int piececount = 0;
  for (int i = 0; i < 32; i++)
    {
      if (tempmove[i] >= '0' && tempmove[i] <= '5')
	{
	  piececount++;
	}
    }
  return piececount;
}



int * piecearray(char *tempmove, int temppiece)
{
  int *outputmove = malloc(sizeof(int) * temppiece);
  int iterthing = 0;
  for (int i = 0; i < 32; i++)
    {
      if (tempmove[i] != '0')
	{
	  outputmove[i] = iterthing;
	  iterthing++;
	}
    }
  return outputmove;
}


FILE * constructabsolutemap(int linelimit)
{
  FILE * movecatalogue = fopen("movecatalogue.txt", "r");
  FILE * absolutemap = fopen("absolutemap.txt", "w");
  char tempchar = fgetc(movecatalogue);
  int iterthing = 0;
  struct movemap **movetempstoragecontainer = malloc(sizeof(struct movemap) * iterthing);

  while (tempchar != EOF && iterthing < linelimit)
    {
      iterthing++;
      char *movestring = malloc(sizeof(char) * 32);
      for (int j = 0; j < 32; j++)
	{
	  movestring[j] = tempchar;
	  tempchar = fgetc(movecatalogue);
	}
      tempchar = fgetc(movecatalogue);
      movetempstoragecontainer = realloc(movetempstoragecontainer, sizeof(struct movemap) * iterthing);
      double tempscore = 0.0;
      double  k = 1.0;
      while (tempchar != EOF &&  tempchar != 10)
	{
	  double gamescore = 0.0;
	  if (tempchar == 'w')
	    {
	      gamescore = 1.0;
	    }
	  else if (tempchar == 'd')
	    {
	      gamescore = 0.5;
	    }
	  else if (tempchar == 'l')
	    {
	      gamescore = 0.0;
	    }
	  tempchar = fgetc(movecatalogue);
	  tempscore += gamescore;
	  if (tempchar == 10)
	    {
	      tempscore = tempscore / k;
	    }
	  k++;
	}
      tempchar = fgetc(movecatalogue);
      struct movemap *tempmap = malloc(sizeof(struct movemap));
      tempmap->movestring = movestring;
      tempmap->winpercent = tempscore;
      movetempstoragecontainer[iterthing-1] = tempmap;
    }
  struct linkedlist *templist = initializelisttree();
  for (int i = 0; i < iterthing; i++)
    {
      struct listnode *tempnode = initializetreeleafnode(movetempstoragecontainer[i]->movestring, movetempstoragecontainer[i]->winpercent);
      insertsortednodelista(templist, tempnode);
    }
  //printlist(templist);
  outputlistfile(templist, absolutemap);
  removelist(templist);
  freestoragecontainer(movetempstoragecontainer, iterthing);
  fclose(movecatalogue);
  
  return(absolutemap);
}

char *getmovesaroundradius(char *inputmove, int inputpiece, int inputradius)
{
  char boardposition[8][4];
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 4; j++)
	{
	  boardposition[i][j] = inputmove[(i * 8) + j] + 1;
	  printf("%c", inputmove[(i * 8) + j]);
	}
    }
  int pieceindexy = inputpiece / 4;
  int pieceindexx = inputpiece - pieceindexy;
  char tempmove[8][4];
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 4; j++)
	{
	  tempmove[i][j] = '0';
	}
    }

  int altered = 0;
  for (int i = (-1 * inputradius); i < inputradius; i++)
    {
      for (int j = (-1 * inputradius); j < inputradius; j++)
        {
	  int currentvaly = pieceindexy + i;
	  int currentvalx = pieceindexx + j;
	  if (((pieceindexy % 2 == 0 && currentvalx > -2) && (pieceindexy % 2 == 0 && currentvalx < 3 ) && (currentvaly > -1 && currentvaly < 8))||
	      ((pieceindexy % 2 == 1 && currentvalx > -1) && (pieceindexy %2 == 1 && currentvalx < 4) && (currentvaly > -1 && currentvaly < 8)) ||
	      ((inputradius % 2 == 0) && (currentvalx > -1 && currentvalx < 4) && (currentvaly > -1 && currentvaly < 8)))
	    {
	      altered = 1;
	      if (inputradius % 2 == 0)
		{
		  tempmove[pieceindexy + i][pieceindexx + j] = boardposition[pieceindexy + i][pieceindexx + j];
		}
	      else
		{
		  if (pieceindexy % 2 == 0)
		    {
		      tempmove[pieceindexy + i + 1][pieceindexx] = boardposition[pieceindexy + i + 1][pieceindexx];
		    }
		  else
		    {
		      tempmove[pieceindexy + i][pieceindexx] = boardposition[pieceindexy + i][pieceindexx];
		    }
		}	
	    } 
	}
    }
    
   if (altered == 1)
   {
      char *outputmove = malloc(sizeof(char) * 32);
      for (int i = 0; i < 32; i++)
	{
	  int tempy = i / 4;
	  int tempx = i - tempy;
	  outputmove[i] = tempmove[tempy][tempx];
	}
      return outputmove;
   }
   else
     {
       return NULL;
     }
}

char** initializerelativemoves(char *movearray)
{
  char **relstorage = malloc(sizeof(char) * 32 * 0);
  int storecount = 0;
  int boardmove[8][4];
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 4; j++)
	{
	  boardmove[i][j] = movearray[((i * 4) + j)];
	}
    }
  int totalmove = numpieces(movearray);
  //printf("%d", totalmove);
  int *piecelist = piecearray(movearray, totalmove);
  for (int i = 0; i < totalmove; i++)
    {
      for (int j = 0; j < 7; j++)
	{
	  char *relmove = getmovesaroundradius(movearray, piecelist[i], j);
	  if (relmove != NULL)
	    {
	      storecount++;
	      relstorage = realloc(relstorage, sizeof(char) * 32 * storecount);
	      relstorage[storecount-1] = relmove;
	    }
	}
    }
  return relstorage;
}





int main()
{
  //constructabsolutemap(10);
  char testmove[32] = {'2','2','0','2','0','1','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','0','1','1','1','0','1','1','0','0','1'};
  for (int i = 0; i < 32; i++)
    {
      printf("%c", (testmove[i]));
    }
  char **testrel = initializerelativemoves(testmove);
  //printf("%lu", (sizeof(testrel)));
  
}
