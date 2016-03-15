#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gdd_list.h"


typedef struct _Paragraph {
    unsigned int pnum;
    unsigned int nSentences;
    char **sentences;
} Paragraph_t;

typedef struct Criteria_ {
    char *word;   /** look for this word that occurs N times **/
    int   noccur;    
}  Criteria_t;


Paragraph_t * makeParagraph(unsigned int pnum)
{
    Paragraph_t *P = malloc(sizeof(Paragraph_t));
    P->pnum = pnum;
    P->nSentences = 0;
    P->sentences = (char**)malloc(sizeof(char*));   /** inefficient, but just allocate for one and use realloc **/
    P->sentences[0] = NULL;                         /** always set the last element to NULL to indicate end of array  **/
    return P;
}


void addSentence(Paragraph_t *P, const char* const S)
{
    if (!P || !S) return;


    P->sentences = (char**)realloc(P->sentences, sizeof(char*) * (P->nSentences+1)); /** grow the array by 1 (inefficient)  **/

    *(P->sentences+(P->nSentences)) = strdup(S);
    P->nSentences++;
    *(P->sentences+(P->nSentences)) = NULL;  /** last array element is NULL to indicate end of array    **/
}

/** --------------------------------------------------------------------------
 **/

void showBuffer(const char * const data, size_t N)
{
    size_t i;
    if (N == 0) return;
    fprintf(stdout,"[");
    for (i=0; i<N; i++) {
        fprintf(stdout, "%c", data[i]);
    }
    fprintf(stdout,"]\n");
}


void saveSentence(const char *const data, size_t N, char *target, unsigned int *p)
{
    memcpy(target+*p, data, N);
    (*p)+= N;
}


/**     ----------------------------------------------------------------------
 **     list node creation and destuction functions
 **/

void const *const constructNode(const void *const data, void *userdata)
{
    /** TODO: this is a trivial case. Need to modify the creation function in list.c to default to this  **/
    return data;
}


void destructNode(void *data)
{
    Paragraph_t *P = data;
    char **S=NULL, *S_tmp=NULL;

    if (!P) return;
    if (P->sentences) {
        S = P->sentences;
        while (*S) {
            S_tmp = *S;
            free(S_tmp);
            S++;
        }
        free(P->sentences);
    }
    free(P);
}


void displayNode(void* data, void *userdata)
{
    Paragraph_t *P = (Paragraph_t*)data;
    char **text = P->sentences;
    unsigned int j, i=0;
    fprintf(stdout,"Par ID:[%3d],nsent:[%3d],text:[%x]\n",P->pnum,P->nSentences, text);
    while (*text) {
        i++;
        fprintf(stdout,"sentence #:[%d][%s]\n",i,*text);
        *text++;
    }
}


int wordsearch(void* data, void *userdata)
{
    Criteria_t *criteria = userdata;
    
    Paragraph_t *P = data;
    char **S=NULL;
    int N=0;
    if (!P) return FALSE;
    if (!userdata) return TRUE;
    S = P->sentences;
    while (*S) {
        if (strstr(*S, criteria->word)) N++;
        if (N == criteria->noccur) return TRUE;
        *S++;
    }
    return FALSE;
}


int main(int argc, char **argv)
{
    FILE *fp = NULL;
    char *filename = "loremipsum_2.txt";
    int nbRtn = 0;
    char buffer[1024];
    char saveBuffer[1024];
    char *s_period = NULL;
    char *cur=NULL;
    char *tmp=NULL;

    Paragraph_t *PG = NULL;
    GDDList_t *L = NULL;

    unsigned int pos;
    int  endOfP;
    unsigned int i;
    unsigned int paragraphNum;


    for (i=0; i<1; i++) {
        fprintf(stdout,"================= [%d] ===================================\n",i);

        memset(buffer,'\0', sizeof(buffer));
        memset(saveBuffer,'\0', sizeof(saveBuffer));
        pos = 0;

        fp = fopen(filename, "rb");
        if (!fp) fprintf(stdout,"fp is null\n");

        L = GDDList_create((GDDFncCreate)constructNode, (GDDFncDestroy)destructNode);
        GDDList_setShowFunction(L, (GDDFncShow)displayNode);

        paragraphNum = 1;
        PG = makeParagraph(paragraphNum);
        GDDList_addNode(L, PG);

        while ((nbRtn = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            cur = buffer;
            while ( (tmp=strchr(cur,'.'))  && cur < buffer+sizeof(buffer)-1) {
                /***
                 *** Found end of sentence; save it
                 ***/

                /**
                 **  Test if end of paragraph (is the next character an ascii character?)
                 **/
                if (tmp-cur+1 < sizeof(buffer) && *(tmp+1) != ' ') {
                    endOfP = TRUE;
                }
                else {
                    endOfP = FALSE;
                }
                saveSentence(cur, tmp-cur, saveBuffer, &pos);   /**  concatenate sentence to what has already been captured **/
                addSentence(PG, saveBuffer);

                if (endOfP) {
                    paragraphNum++;
                    PG = makeParagraph(paragraphNum);
                    GDDList_addNode(L, PG);
                }

                memset(saveBuffer,'\0', sizeof(saveBuffer));
                tmp++;
                cur = tmp;
                if (cur < buffer+sizeof(buffer)-1 && *cur == ' ') {
                    cur++;
                }
                pos = 0;
            }
            /** If not end of sentence, then save what is in buffer. The pos variable keeps track of
             ** of the next location where the data is to be written
             **/
            if (!tmp) {
                saveSentence(cur, sizeof(buffer)-(cur-buffer), saveBuffer, &pos);
            }
            memset(buffer,'\0', sizeof(buffer));
        }

        if (fp) fclose(fp);

        /***  iterator tests on list   **/
        {
            GDDListIterator_t II = { NULL, TRUE };  /**  initialize to this: next elem=NULL, firstTime=TRUE   **/
            while ((PG = GDDList_iterate(L, &II))) {
                displayNode(PG, NULL);
            }
        }

        {
            Criteria_t criteria = { "Cu ius omnis", 2 };
            GDDListIterator_t II = { NULL, TRUE };  /**  initialize to this: next elem=NULL, firstTime=TRUE   **/
            while ( (PG = GDDList_iterateWithFilter(L, wordsearch, &criteria, &II)) ) {
                displayNode(PG, NULL);
            }
        }

        GDDList_destroy(L);
        L = NULL;
    }
    return 0;
}
