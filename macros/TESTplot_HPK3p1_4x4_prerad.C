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

	Double_t shiftX;
	Double_t shiftY;

	std::vector<Double_t> shifted_scoresX;
	std::vector<Double_t> shifted_scoresY;

	std::vector<Double_t> shiftsX;
	std::vector<Double_t> shiftsY;

	std::vector<TFile*> files;



	TString g_pathname = "/uscms/homes/m/mlazarov/work/CMSSW_9_2_6/src/ETLTestBeamMacros/output/HPK3p1_4x4_prerad/";
	TString og_histname = "HPK3p1_4x4_prerad";
	TString shifted_histname = "HPK3p1_4x4_prerad_shift";


	OptimizerClass Optimizer;
	// Optimizer.createHistograms(og_histname,minX,maxX,minY,maxY);
	TFile* file = TFile::Open(g_pathname+og_histname+".root");
	scoresX = Optimizer.createScoreMatrixX(file);
	scoresY_T = Optimizer.createScoreMatrixY(file);
	og_globalscore = Optimizer.calcScores(scoresX, scoresY_T);

	
	TFile* shift_file; // = new TFile(g_pathname+shifted_histname+".root","RECREATE");

	//shift histogram - X
	for(int i = 0; i < 20; i++){
		shift_file = NULL;
		shifted_globalscore = 0.0;

		shiftX = -0.5 + 0.05*i;
		TString nameX = Form(shifted_histname+"_X%d.root",shiftX);
		cout << nameX << endl;
		if(!gSystem->AccessPathName(nameX)){ //if file exists
			cout << nameX << " exists" << endl;
			// files.push_back(shift_file = TFile::Open(nameX));
		}
		else if(gSystem->AccessPathName(nameX)){ //if file doesn't exist
			cout << "making " << nameX << endl;
			// Optimizer.createHistograms(nameX,minX+shiftX,maxX+shiftX,minY,maxY);
			// files.push_back(shift_file = new TFile(nameX));
		}

		// shift_scoresX = Optimizer.createScoreMatrixX(files[i]);
		// shift_scoresYT  = Optimizer.createScoreMatrixY(files[i]);
		// shifted_globalscore = Optimizer.calcScores(shift_scoresX,shift_scoresYT);

		// shiftsX.push_back(shiftX);
		// shifted_scoresX.push_back(shifted_globalscore);

	}
	
	

	// shift histogram - Y
	// for(int i = 0; i < 2; i++){
	// 	shift_file = NULL;
	// 	shifted_globalscore = 0.0;
	// 	shiftY = -0.5 + 0.05*i;

	// 	TString nameY = Form(shifted_histname+"_Y%d.root",shiftY);
		
	// 	if(!gSystem->AccessPathName(nameY)){ //if file exists
	// 		cout << nameY << " exists" << endl;
	// 		// files.push_back(shift_file = TFile::Open(nameY));
	// 	}
	// 	else if(gSystem->AccessPathName(nameY)){ //if file doesn't exist
	// 		cout << "making " << nameY << endl;
	// 		// Optimizer.createHistograms(nameY,minX,maxX,minY+shiftY,maxY+shiftY);
	// 		// files.push_back(shift_file = new TFile(nameY));
	// 	}

	// 	shift_scoresX = Optimizer.createScoreMatrixX(files[i]);
	// 	shift_scoresYT  = Optimizer.createScoreMatrixY(files[i]);
	// 	shifted_globalscore = Optimizer.calcScores(shift_scoresX,shift_scoresYT);

	// 	shiftsY.push_back(shiftY);
	// 	shifted_scoresY.push_back(shifted_globalscore);
	// }

	// TGraph* gr_xshift = new TGraph(shiftsX.size(),&(shiftsX[0]),&(shifted_scoresX[0]));
	// TGraph* gr_yshift = new TGraph(shiftsY.size(),&(shiftsY[0]),&(shifted_scoresY[0]));

	// TCanvas* cv_x = new TCanvas("cv_x","cv_x",800,600);
	// TCanvas* cv_y = new TCanvas("cv_y","cv_y",800,600);

	// TFile* f_shiftsx = new TFile("f_shiftsx","RECREATE");
	// TFile* f_shiftsy = new TFile("f_shiftsy","RECREATE");


	// f_shiftsx->cd();
	// cv_x->cd();
	// gr_xshift->Draw();
	// f_shiftsx->Write();
	// f_shiftsx->Close();

	// f_shiftsy->cd();
	// cv_y->cd();
	// gr_yshift->Draw();
	// f_shiftsy->Write();
	// f_shiftsy->Close();


	






}
# endif
