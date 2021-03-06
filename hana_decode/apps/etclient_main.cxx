// Test of etClient class
// R. Michaels, Feb 2001

#define PRINTOUT 1  // to test speed set to 0, else prints out

#include "THaEtClient.h"
#include <iostream>

using namespace std;
using namespace Decoder;

int main(int argc, char *argv[]) 
{

       int mymode = 1;   // prefered mode for ET
       THaEtClient *et;
       et = new THaEtClient("adaqcp", mymode);  // opens connection to adaqcp computer.
 
       UInt_t* evbuff = new UInt_t[et->getBuffSize()];   // raw data buffer

       int NUMEVT = 10000;
       ULong64_t lensum=0;
       ULong64_t dummysum = 0;

       if (argc > 1) NUMEVT = atoi(argv[1]);

       for (int iev=0; iev<NUMEVT; iev++) {
         if ((iev%1000) == 0) {
	   cout << "Event "<<dec<<iev<<"  sums "<<lensum<<"  "<<dummysum<<endl;
	 }
         int status = et->codaRead();  // This must be done once per event.
         if (status != 0) {
             cout << "Error Status from codaRead " << status << endl;
             exit(0);
	 }
         evbuff = et->getEvBuffer();
         if (PRINTOUT) 
           cout << "Event "<<dec<<iev<<" length "<<evbuff[0]+1<<endl;
         for (UInt_t i=0; i<evbuff[0]+1; i++) {
           if(i < static_cast<UInt_t>(et->getBuffSize())) {
             if(PRINTOUT) {
	       cout<<"evbuffer " <<dec<<i<< "  = "<<hex<<evbuff[i]<<endl;
	     } else {
               lensum += evbuff[0]/100;
	       dummysum += evbuff[i]/100000.;
	     }
	   }

         }
	 //	 if (PRINTOUT) usleep(5000);
       }
       cout << "END, processes "<<NUMEVT<<" events,  sums "<<lensum<<"  "<<dummysum<<endl;

       delete [] evbuff;
}
