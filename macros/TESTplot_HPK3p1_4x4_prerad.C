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
	
	Double_t** scoresX;
	Double_t** scoresY_T;

	Double_t** shift_scoresX;
	Double_t** shift_scoresYT;

	Double_t og_globalscore;
	Double_t shifted_globalscore;

	Double_t shiftX = 0.0;
	Double_t shiftY = 0.0;

	// Double_t shiftsX[20];
	// Double_t shiftsY[20];

	// Double_t shifted_scoresX[20];
	// Double_t shifted_scores[20];

	// TVectorT<Double_t> shifted_scoresX = new TVectorD();

	// typedef TVectorT<Double_t> shifted_scoresX;

	// TVectorD shifted_scoresY;

	// TVectorD shiftsX;
	//DONT USE TVECTORS - SWITCH TO ARRAYS
	// TVectorD shiftsY;

	std::vector<Double_t> shifted_scoresX;
	std::vector<Double_t> shifted_scoresY;

	std::vector<Double_t> shiftsX;
	std::vector<Double_t> shiftsY;



	TString g_pathname = "/uscms/homes/m/mlazarov/work/CMSSW_9_2_6/src/ETLTestBeamMacros/output/HPK3p1_4x4_prerad/";
	TString og_histname = "HPK3p1_4x4_prerad";
	TString shifted_histname = "HPK3p1_4x4_prerad_shift";


	OptimizerClass Optimizer;
	// Optimizer.createHistograms(og_histname,minX,maxX,minY,maxY);
	TFile* file = TFile::Open(g_pathname+og_histname+".root");
	scoresX = Optimizer.createScoreMatrixX(file);
	scoresY_T = Optimizer.createScoreMatrixY(file);
	og_globalscore = Optimizer.calcScores(scoresX, scoresY_T);

	
	TFile* shift_file = new TFile(g_pathname+shifted_histname+".root","RECREATE");

	
	// //shift histogram - X
	for(int i = -10; i < 11; i++){
		shifted_globalscore = 0.0;
		shiftX = i*0.05;
		Optimizer.createHistograms(shifted_histname,minX+shiftX,maxX+shiftX,minY,maxY);
		shift_scoresX = Optimizer.createScoreMatrixX(shift_file);
		shift_scoresYT  = Optimizer.createScoreMatrixY(shift_file);
		shifted_globalscore = Optimizer.calcScores(shift_scoresX,shift_scoresYT);

		shiftsX.push_back(shiftX);
		shifted_scoresX.push_back(shifted_globalscore);
	}

	// shift histogram - Y
	for(int i = -10; i < 11; i++){
		shifted_globalscore = 0.0;
		shiftY = i*0.05;
		Optimizer.createHistograms(shifted_histname,minX,maxX,minY+shiftY,maxY+shiftY);
		shift_scoresX = Optimizer.createScoreMatrixX(shift_file);
		shift_scoresYT  = Optimizer.createScoreMatrixY(shift_file);
		shifted_globalscore = Optimizer.calcScores(shift_scoresX,shift_scoresYT);

		shiftsY.push_back(shiftY);
		shifted_scoresY.push_back(shifted_globalscore);
	}

	TGraph* gr_xshift = new TGraph(shiftsX.size(),&(shiftsX[0]),&(shifted_scoresX[0]));
	TGraph* gr_yshift = new TGraph(shiftsY,shifted_scoresY);

	TCanvas* cv_x = new TCanvas("cv_x","cv_x",800,600);
	TCanvas* cv_y = new TCanvas("cv_y","cv_y",800,600);

	TFile* f_shiftsx = new TFile("f_shiftsx","RECREATE");
	TFile* f_shiftsy = new TFile("f_shiftsy","RECREATE");


	f_shiftsx->cd();
	cv_x->cd();
	gr_xshift->Draw();
	f_shiftsx->Write();
	f_shiftsx->Close();

	f_shiftsy->cd();
	cv_y->cd();
	gr_yshift->Draw();
	f_shiftsy->Write();
	f_shiftsy->Close();




	
	// //compare shifted scores with OG scores
	




	

	


    //steps - how to work with ETLTestBeamMacros??
	//3. shift histogram +0.5 mm/bin until edge (recalcuate score at each shift, keep if better than last shift)
	//4. repeat step 4 with -0.5 mm/bin
	//5. repeat for each direction
    
    	//1. create histogram from ETLTestBeamMacros macro (start w plot_HPK3p1_4x4_prerad.C)
		//2. create instance of OptimizerClass -> use calcDropoffs on each 1D histogram (2D for loop - start with 1 direction)


}
# endif
