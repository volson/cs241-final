#include "checkers.h"

struct listnode* initializetreeleafnode(char *inputstring, double inputfreq)
{
  struct listnode *outnode = malloc(sizeof(struct listnode));
  outnode->movestring = inputstring;
  outnode->winpercent = inputfreq;
  outnode->next = NULL;
  outnode->previous = NULL;
  return outnode;
}

struct linkedlist* initializelisttree()
{
  struct linkedlist *outlist = malloc(sizeof(struct linkedlist));
  outlist->bow.winpercent = -2;
  outlist->bow.next = &(outlist->stern);
  outlist->stern.winpercent = -3;
  outlist->stern.previous = &(outlist->bow);
  return outlist;
}

struct linkedlist* clearlist(struct linkedlist *inputlist)
{
  struct listnode *tempnode = inputlist->bow.next;
  struct listnode *removenode;
  while (tempnode->winpercent != -3)
    {
      removenode = tempnode;
      tempnode = tempnode->next;
      if (removenode->movestring != NULL)
	{
	  free(removenode->movestring);
	}
      free(removenode);
    }
  return inputlist;
}


void removelist(struct linkedlist *inputlist)
{
  clearlist(inputlist);
  free(inputlist);
}

int listsize (struct linkedlist *inputlist)
{
  int counter = 0;
  struct listnode *tempnode = inputlist->bow.next;
  while (tempnode->winpercent != -3)
    {
      tempnode = tempnode->next;
      counter++;
    }
  return counter;
}

void insertsortednodelista(struct linkedlist *inputlist, struct listnode *inputnode)
{
  struct listnode  *iternode = inputlist->bow.next;
  while(iternode->winpercent != -3)
    {
      if ((movecomparatora(iternode->movestring, inputnode->movestring)) == 1)
	{
	  iternode = iternode->next;
	}
      else
	{
	  break;
	}
    }
  inputnode->next = iternode;
  inputnode->previous = iternode->previous;
  iternode->previous->next = inputnode;
  iternode->previous = inputnode;
}

void insertsortednodelistr(struct linkedlist *inputlist, struct listnode *inputnode)
{
  struct listnode  *iternode = inputlist->bow.next;
  while(iternode->winpercent != -3)
    {
      if ((movecomparatorr(iternode->movestring, inputnode->movestring)) == 1)
	{
	  iternode = iternode->next;
	}
      else
	{
	  break;
	}
    }
  inputnode->next = iternode;
  inputnode->previous = iternode->previous;
  iternode->previous->next = inputnode;
  iternode->previous = inputnode;
}


void printlist(struct linkedlist *inputlist)
{
  struct listnode *tempnode = inputlist->bow.next;
  char *tempstring;
  while (tempnode->winpercent != -3)
    {
      tempstring = tempnode->movestring;
      printf("%s", tempstring);
      printf("%c", ' ');
      printf("%f", tempnode->winpercent);
      printf("%c", '\n');
      tempnode = tempnode->next;
    }
}

void outputlistfile(struct linkedlist *inputlist, FILE *inputfile)
{
  struct listnode *tempnode = inputlist->bow.next;
  char *tempstring;
  while (tempnode->winpercent != -3)
    {
      tempstring = tempnode->movestring;
      for (int i = 0; i < 32; i++)
	{
	  fputc(tempstring[i] + 48, inputfile);
	}
      fputc(' ', inputfile);
      fprintf(inputfile, "%f", tempnode->winpercent);
      fputc('\n', inputfile);
      tempnode = tempnode->next;
    }
}
