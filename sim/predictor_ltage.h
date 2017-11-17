
///////////////////////////////////////////////////////////////////////
// Sriram V Balasubramanian, Udit Khanna
// Portland State University
///////////////////////////////////////////////////////////////////////


#ifndef _PREDICTOR_H_
#define _PREDICTOR_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include "utils.h"
#include "bt9.h"
#include "bt9_reader.h"


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

#define M		5	// Number of predictor componenets
#define A		2	// Common ratio for geometric progression (alfa)
#define LEN_PRED1	1	// History Length for first component
#define LEN_PRED(i)	(A^(i-1))*LEN_PRED1

#define BASE_INDEX_WIDTH	12	// Number of bits to index base predictor
#define PRED_INDEX_WIDTH	10	// Number of bits to index a predictor component

#define NUM_ENTRIES_BASE	(1 << BASE_INDEX_WIDTH)
#define NUM_ENTRIES_PRED	(1 << PRED_INDEX_WIDTH)

// Tagged Component Entry
typedef struct tc_entry_s {
	UINT32 u;
	UINT32 ctr;
	UINT32 tag;
} TC_ENTRY;

class PREDICTOR{

  // L-TAGE Predictor State
  //
 private:
  TC_ENTRY *predictor [M];	// Pointers to the M predictor components
  UINT32 *basePredictor;	// Pointer to the bimodal predictor
  UNIT32 useAltOnNA;		// 4-bit counter

 public:
  PREDICTOR(void);

  bool    GetPrediction(UINT64 PC);  
  void    UpdatePredictor(UINT64 PC, OpType opType, bool resolveDir, bool predDir, UINT64 branchTarget);
  void    TrackOtherInst(UINT64 PC, OpType opType, bool branchDir, UINT64 branchTarget);

  // Internal functions

};

/////////////// STORAGE BUDGET JUSTIFICATION ////////////////
// Total Size 
// = Size of M predictor components + Size of Bimodal Predictor
// =  
/////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

PREDICTOR::PREDICTOR(void){	
	UINT32 i, j;

	basePredictor = new UINT32 [NUM_ENTRIES_BASE];

	// Set all bimodal predictor entries to weakly taken
	for (i=0; i<NUM_ENTRIES_BASE; i++) {
		basePredictor[i] = 1; // Self: Define enum?
	}

	for (i=0; i<M; i++) {
		// Allocate 1K TC_ENTRIES for each component
		predictor[i] = new TC_ENTRY [NUM_ENTRIES_PRED];

		for (j=0; j<NUM_ENTRIES_PRED; j++) {
			predictor[i][j].ctr = 1;
			predictor[i][j].u = 0;
			predictor[i][j].tag = 0;
			// Self: Don't we need a valid bit?
		}
	}
  }
  
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

bool   PREDICTOR::GetPrediction(UINT64 PC){

}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void  PREDICTOR::UpdatePredictor(UINT64 PC, OpType opType, bool resolveDir, bool predDir, UINT64 branchTarget){

}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void    PREDICTOR::TrackOtherInst(UINT64 PC, OpType opType, bool branchDir, UINT64 branchTarget){

  // This function is called for instructions which are not
  // conditional branches, just in case someone decides to design
  // a predictor that uses information from such instructions.
  // We expect most contestants to leave this function untouched.

  return;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


/***********************************************************/
#endif

