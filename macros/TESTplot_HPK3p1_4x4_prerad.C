// #include "map_plotter.C"
#include "OptimizerClass.hh"
using namespace std;

# ifndef __CINT__

int main(int argc, char **argv)
{
	Double_t minX = 4.;
	Double_t maxX = 20.;
	Double_t minY = 30.;
	Double_t maxY = 38.;
	set<pair<Double_t, Double_t>> scores; //set of dropoff score and location (middle of pad)
	set<pair<Double_t, Double_t>> tmpscores;
	Double_t** scoresX;
	Double_t** scoresY_T;
	Double_t avgscores; //average of scores per row/column
	Double_t scoresY[4][4];

	Int_t nBinsX;
	Int_t nBinsY;

	TString g_pathname = "/uscms/homes/m/mlazarov/work/CMSSW_9_2_6/src/ETLTestBeamMacros/output/HPK3p1_4x4_prerad/";
	TString og_histname = "HPK3p1_4x4_prerad";
	TString shifted_histname = "HPK3p1_4x4_prerad_shift";


	OptimizerClass Optimizer;
	// Optimizer.createHistograms(og_histname,minX,maxX,minY,maxY);
	TFile* file = TFile::Open(g_pathname+og_histname+".root");
	scoresX = Optimizer.createScoreMatrixX(file);
	scoresY_T = Optimizer.createScoreMatrixY(file);
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			scoresY[i][j] = scoresY_T[j][i]
			cout << "scoresX: " << scoresX[i][j] << " index " << i << ", " << j << endl;
			cout << "scoresY: " << scoresY[i][j] << " index " << i << ", " << j << endl;
		}
	}

	
	// //shift histogram
	// Optimizer.createHistograms(shifted_histname,minX+0.05,maxX+0.05,minY,maxY);
	// shift_matscoresX = Optimizer.createScoreMatrixX(shift_file);

	// //compare shifted scores with OG scores
	// for(int j = 0; j < 4; j++){
	// 	for(int i = 0; i < 4; i++){
	// 		if(og_matscoresX[j][i] > shift_matscoresX[j][i]){

	// 		}
	// 		else if(og_matscoresX[j][i] < shift_matscoresX[j][i]){

	// 		}
	// 		else if(og_matscoresX[j][i] == shift_matscoresX[j][i]){

	// 		}
	// 	}
	// }




	

	


    //steps - how to work with ETLTestBeamMacros??
	//3. shift histogram +0.5 mm/bin until edge (recalcuate score at each shift, keep if better than last shift)
	//4. repeat step 4 with -0.5 mm/bin
	//5. repeat for each direction
    
    	//1. create histogram from ETLTestBeamMacros macro (start w plot_HPK3p1_4x4_prerad.C)
		//2. create instance of OptimizerClass -> use calcDropoffs on each 1D histogram (2D for loop - start with 1 direction)


}
# endif
