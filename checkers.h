#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct movemap{
  char *movestring;
  double winpercent;
};

struct listnode{
  char *movestring;
  double winpercent;
  struct listnode *next;
  struct listnode *previous;
};

struct linkedlist{
  struct listnode bow;
  struct listnode stern;
};


struct listnode* initializetreeleafnode(char *inputstring, double inputfreq);

struct linkedlist* initializelisttree();

struct linkedlist* clearlist(struct linkedlist *inputlist);

void removelist(struct linkedlist *inputlist);

int listsize (struct linkedlist *inputlist);

void insertsortednodelistr(struct linkedlist *inputlist, struct listnode *inputnode);

void insertsortednodelista(struct linkedlist *inputlist, struct listnode *inputnode);

int movecomparatora(char *inputmove1, char  *inputmove2);

int movecomparatorr(char *inputmove1, char  *inputmove2);

void printlist(struct linkedlist *inputlist);

void outputlistfile(struct linkedlist *inputlist, FILE *inputfile);
  





#endif
