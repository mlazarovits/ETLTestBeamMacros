#ifndef OptimizerClass_HH
#define OptimizerClass_HH
#include <set>
// using namespace std;
// #include "calcDropoffs.C"
#include "map_plotter.C"


class OptimizerClass{
	public:
		OptimizerClass(){};
		virtual ~OptimizerClass(){};
		std::set<std::pair<Double_t,Double_t>> calcDropoffs(TH1* hist);
		void createHistograms(TString tag, Double_t Xmin, Double_t Xmax, Double_t Ymin, Double_t Ymax);

		Int_t GetnBinsY();
		Int_t GetnBinsX();

		Int_t nBinsY;
		Int_t nBinsX;

		// void Optimizerplotter(TH1* hist, Double_t* x, Double_t* deriv_x);

		Double_t** createScoreMatrixX(TFile* file);
		Double_t** createScoreMatrixY(TFile* file);
		// Double_t mat_scores[4][4];

	private:
		// std::set<pairs> dropoffscores;
		Int_t nPts;
		// Double_t x[nPts];
		// Double_t y[nPts];
		// Double_t deriv_x[nPts-1];
		std::set<std::pair<Double_t,Double_t>> scores; //set of dropoff score and location (middle of pad)

		
};

#endif

inline Int_t OptimizerClass::GetnBinsY(){
	return nBinsY;
}

inline Int_t OptimizerClass::GetnBinsX(){
	return nBinsX;
}

inline Double_t** OptimizerClass::createScoreMatrixX(TFile* file){
	Double_t** mat_scores = 0;
	mat_scores = new Double_t*[4];
	//calculate initial scores in X 
	for(int i = 0; i < 4; i++){
		mat_scores[i] = new Double_t[4];
		TString histname = Form("h_x_eff_0_%i",i);
		TH1F* hist = (TH1F*)file->Get(histname);
		scores = calcDropoffs(hist);
		for(int sc = 0; sc < 4; sc++){
			std::set<std::pair<Double_t,Double_t>>::iterator it = std::next(scores.begin(),sc);
			mat_scores[i][sc] = std::get<1>(*it);
		}		
	}
	return mat_scores;
}

inline Double_t** OptimizerClass::createScoreMatrixY(TFile* file){
	Double_t** mat_scores = 0;
	mat_scores = new Double_t*[4];
	//calculate initial scores in Y
	for(int i = 0; i < 4; i++){
		mat_scores[i] = new Double_t[4];
		TString histname = Form("h_y_eff_0_%i",i);
		TH1F* hist = (TH1F*)file->Get(histname);
		scores = calcDropoffs(hist);
		for(int sc = 0; sc < 4; sc++){
			std::set<std::pair<Double_t,Double_t>>::iterator it = std::next(scores.begin(),sc);
			mat_scores[sc][i] = std::get<1>(*it);
		}		
	}
	return mat_scores;
}

inline std::set<std::pair<Double_t,Double_t>> calcDropoffs(TH1* hist){
	
	// TFile* file = TFile::Open("~/ETLTestBeamMacros/output/HPK3p1_4x4_prerad/HPK3p1_4x4_prerad.root");
	// TString histname = "h_x_eff_0_2";

	// cout << "histogram: " << histname << endl;

	// TH1F* hist = (TH1F*)file->Get(histname);

	

	TGraph* graph = new TGraph(hist);
	graph->GetXaxis()->SetTitle("x distance (mm)");
	graph->GetYaxis()->SetTitle("efficiency");
	graph->SetMarkerStyle(kStar);

	graph->Draw();

	Int_t nPts = graph->GetN();
	Double_t x[nPts];
	Double_t y[nPts];
	Double_t deriv_x[nPts-1];

	for(int i = 0; i < nPts; i++){
		x[i] = hist->GetBinCenter(i);
		y[i] = hist->GetBinContent(i);
	}

	for(int i = 0; i < nPts-1; i++){
		if((x[i-1] == 0 && x[i+1] == 0) || (y[i-1] == 0 && y[i+1] == 0)){
			deriv_x[i] = 0;
			continue;
		}
		deriv_x[i] = pow((y[i+1] - y[i])/(x[i+1] - x[i]),2);
	}
	
	
	
	TGraph* g_deriv = new TGraph(nPts,x,deriv_x);
	g_deriv->SetTitle("Squared Derivative of 1D profile");
	g_deriv->GetXaxis()->SetTitle("x distance (mm)");
	g_deriv->GetYaxis()->SetTitle("Derivative squared");
	g_deriv->SetMarkerStyle(kStar);
	TCanvas* cv = new TCanvas();
	cv->cd();
	g_deriv->Draw();

	// cout << "locations" << endl;
	// cout << "spike 1: " << x[0] << " to " << x[31] << endl;
	// cout << "spike 2: " << x[32] << " to " << x[63] << endl;
	// cout << "spike 3: " << x[64] << " to " << x[95] << endl;
	// cout << "spike 4: " << x[96] << " to " << x[127] << endl;
	// cout << "spike 5: " << x[128] << " to " << x[159] << endl;

	// cout << "amplitudes" << endl;
	// cout << "spike 1: " << *max_element(deriv_x,deriv_x+nPts/5) << endl;
	// cout << "spike 2: " << *max_element(deriv_x+nPts/5,deriv_x+2*nPts/5) << endl;
	// cout << "spike 3: " << *max_element(deriv_x+2*nPts/5,deriv_x+3*nPts/5) << endl;
	// cout << "spike 4: " << *max_element(deriv_x+3*nPts/5,deriv_x+4*nPts/5) << endl;
	// cout << "spike 5: " << *max_element(deriv_x+4*nPts/5,deriv_x+nPts) << endl;
	
	Double_t spike1 = *std::max_element(deriv_x,deriv_x+nPts/5);
	Double_t spike2 = *std::max_element(deriv_x+nPts/5,deriv_x+2*nPts/5);
	Double_t spike3 = *std::max_element(deriv_x+2*nPts/5,deriv_x+3*nPts/5);
	Double_t spike4 = *std::max_element(deriv_x+3*nPts/5,deriv_x+4*nPts/5);
	Double_t spike5 = *std::max_element(deriv_x+4*nPts/5,deriv_x+nPts);

	Int_t pos1 = std::distance(deriv_x, std::max_element(deriv_x,deriv_x+nPts/5));
	Int_t pos2 = std::distance(deriv_x, std::max_element(deriv_x+nPts/5,deriv_x+2*nPts/5));
	Int_t pos3 = std::distance(deriv_x, std::max_element(deriv_x+2*nPts/5,deriv_x+3*nPts/5));
	Int_t pos4 = std::distance(deriv_x, std::max_element(deriv_x+3*nPts/5,deriv_x+4*nPts/5));
	Int_t pos5 = std::distance(deriv_x, std::max_element(deriv_x+4*nPts/5,deriv_x+5*nPts/5));
	
	Int_t mid1 = (pos1+pos2)/2;
	Int_t mid2 = (pos2+pos3)/2;
	Int_t mid3 = (pos3+pos4)/2;
	Int_t mid4 = (pos4+pos5)/2;

	Int_t mids[4] = {mid1, mid2, mid3, mid4};
	Double_t spikes[4] = {spike1+spike2,spike2+spike3, spike3+spike4, spike4+spike5};
	
	std::set<std::pair<Double_t,Double_t>> dropoffscores;

	for(int i = 0; i < 4; i++){
		Int_t index = mids[i];
		std::pair<Double_t,Double_t> thispair = std::make_pair(x[index],spikes[i]);
		dropoffscores.insert(thispair);
	}

	return dropoffscores;
}

// inline void OptimizerClass::Optimizerplotter(TH1* hist,Double_t* x, Double_t* deriv_x){
// 	TGraph* graph = new TGraph(hist);
// 	graph->GetXaxis()->SetTitle("x distance (mm)");
// 	graph->GetYaxis()->SetTitle("efficiency");
// 	graph->SetMarkerStyle(kStar);
// 	graph->Draw();

// 	TGraph* g_deriv = new TGraph(nPts,x,deriv_x);
// 	g_deriv->SetTitle("Squared Derivative of 1D profile");
// 	g_deriv->GetXaxis()->SetTitle("x distance (mm)");
// 	g_deriv->GetYaxis()->SetTitle("Derivative squared");
// 	g_deriv->SetMarkerStyle(kStar);
// 	TCanvas* cv = new TCanvas();
// 	cv->cd();
// 	g_deriv->Draw();
// }

inline void OptimizerClass::createHistograms(TString tag, Double_t Xmin, Double_t Xmax, Double_t Ymin, Double_t Ymax){
	map_plotter mp;
	mp.tag = tag; //This defines names of all output files
	mp.chainPath = "root://cmseos.fnal.gov//store/group/cmstestbeam/2019_04_April_CMSTiming/KeySightScope/RecoData/TimingDAQRECO/RecoWithTracks/v1/confInfo/";
	mp.debug=false;
	//Define run range
	mp.run_start = new vector<int>{12416,12500};
	mp.run_end = new vector<int>{12499,12552};
	//Note: will try to load every run in this range, even if it doesn't exist (so, expect some harmless complaints.)

	//Define rotation angle and manual adjustments of x and y
	mp.angle = new vector<float>{-2.5,-2.5}; //degrees
	mp.x_offset= new vector<float>{0.040,0.040}; //mm
	mp.y_offset= new vector<float>{0.0,0.0}; //mm
	
	//Define xy binning and ranges [mm]
	nBinsX = 160;
	nBinsY = 80;
	mp.nbinsX=nBinsX;//160; 
	mp.nbinsY=nBinsY;//80;
	mp.rebinFactor=2; //coarser binning for maps of gain, timing (finer for efficiency)
	mp.minX=Xmin; mp.maxX=Xmax; //0.1 mm/bin
	mp.minY=Ymin; mp.maxY=Ymax; //0.1 mm/bin

	//Define amplitude, time binning and range, and scope saturation.
	mp.saturation =640.;
	mp.nbinsAmp=60;
	mp.minAmp=0; mp.maxAmp=mp.saturation;
	mp.nbinsTime=60;
	mp.minTime=7.2e-9; mp.maxTime=8.8e-9;

	//define threshold for LGAD hits, and range for photek
	mp.hitThres=vector<float>(mp.npad+1,40.);
	mp.photekMin=25;
	mp.photekMax=55;

	// Define geometric boundaries for 1D "slices"
	mp.xSliceMin={6,9,12,15};
	mp.xSliceMax={8.2,11.2,14.2,17.2};
	mp.ySliceMin={32.6,33.6,34.6,35.6};
	mp.ySliceMax={33,34,35,36};

	//Specify range for colz maps. -1 is ignored.
	mp.zMinEff=-1.; mp.zMaxEff=-1.; 
	mp.zMinGain=70.; mp.zMaxGain=110.; 
	mp.zMinSigmat=0.01e-9; mp.zMaxSigmat=0.08e-9; 
	mp.zMinDeltat=7.75e-9; mp.zMaxDeltat=-1.;


	//Do everything
    mp.makeMaps();
}