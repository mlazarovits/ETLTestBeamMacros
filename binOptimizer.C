#include "OptimizerClass.hh"

void binOptimizer(){
	//steps - how to work with ETLTestBeamMacros??
	//1. create histogram from ETLTestBeamMacros macro (start w plot_HPK3p1_4x4_prerad.C)
	//2. create array of 1D histogram names
	//3. create instance of OptimizerClass -> use calcDropoffs on each 1D histogram (2D for loop - start with 1 direction)
	//4. shift histogram +0.5 mm/bin
	//5. recalcuate scores
	//6. if loop - if new scores (+shift) are better than old scores, repeat steps 4-5, if not continue
	//7. shift histogram -0.5 mm/bin
	//8. if loop - if new scores (-shift) are better than old scores, repeat steps 6-7, if not continue
	//9. return best scores

}