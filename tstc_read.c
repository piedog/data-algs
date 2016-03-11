#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


void saveSentence(const char *const data, size_t N, char *target, unsigned *p)
{
    memcpy(target+*p, data, N);
    (*p)+= N;
}


int main(int argc, char **argv)
{
    FILE *fp = NULL;
    char *filename = "loremipsum.txt";
    int nbRtn = 0;
    char buffer[1024];
    char saveBuffer[1024];
    char *s_period = NULL;
    char *cur=NULL;
    char *tmp=NULL;

    unsigned pos = 0;
    int  endOfP;

    memset(buffer,'\0', sizeof(buffer));
    memset(saveBuffer,'\0', sizeof(saveBuffer));

    fp = fopen(filename, "rb");
    if (!fp) fprintf(stdout,"fp is null\n");
    while ((nbRtn = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fprintf(stdout, "readbuffer nbRtn=[%d]", nbRtn);
     // showBuffer(buffer, nbRtn);

        cur = buffer;
        /**
         ** look for all the end of sentence ('.'). When found, save the complete sentence
         **/
        while ( (tmp=strchr(cur,'.'))  && cur < buffer+sizeof(buffer)-1) {
            /***
             *** Found end of sentence; save it
             ***/
        //  fprintf(stdout, "end of sentence:[%d]", tmp-buffer);
        //  showBuffer(cur, tmp-cur+1);

            /**
             **  Test if end of paragraph (is the next character an ascii character?)
             **/
            if (tmp-cur+1 < sizeof(buffer) && *(tmp+1) != ' ') {
                endOfP = TRUE;
            }
            else {
                endOfP = FALSE;
            }

            saveSentence(cur, tmp-cur, saveBuffer, &pos);
            fprintf(stdout, "endOfP:[%d] *tmp:[%c] [%s]\n", endOfP, *(tmp+1),saveBuffer);
            memset(saveBuffer,'\0', sizeof(saveBuffer));

            tmp++;
            cur = tmp;
            if (cur < buffer+sizeof(buffer)-1 && *cur == ' ') {
                cur++;
            }
        //  else {
        //      /** if next charcter at cur is space, then it is end of sentence of same paragraph
        //       ** if it is not ' ', then it is end of paragraph.
        //       ** I think this has something to do with VMS record blocking and lack of \n or \r.
        //       **/
        //  }
            pos = 0;
        }

        /** If not end of sentence, then save what is in buffer. The pos variable keeps track of
         ** of the next location where the data is to be written
         **/
        if (!tmp) {
         // fprintf(stdout,"--- tmp=%d, N=%d", cur-buffer);
         // showBuffer(cur, sizeof(buffer)-(cur-buffer));
            saveSentence(cur, sizeof(buffer)-(cur-buffer), saveBuffer, &pos);
        }

        memset(buffer,'\0', sizeof(buffer));

    }


    if (fp) fclose(fp);
    return 0;
}
