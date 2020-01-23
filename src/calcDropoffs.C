// using namespace std;
#include "TAttMarker.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TH1.h"
#include "OptimizerClass.hh"

// typedef pair<Double_t,Double_t> pairs;
std::set<Double_t,Double_t> calcDropoffs(TH1* hist){
	
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
	
	Double_t spike1 = *max_element(deriv_x,deriv_x+nPts/5);
	Double_t spike2 = *max_element(deriv_x+nPts/5,deriv_x+2*nPts/5);
	Double_t spike3 = *max_element(deriv_x+2*nPts/5,deriv_x+3*nPts/5);
	Double_t spike4 = *max_element(deriv_x+3*nPts/5,deriv_x+4*nPts/5);
	Double_t spike5 = *max_element(deriv_x+4*nPts/5,deriv_x+nPts);

	Int_t pos1 = std::distance(deriv_x, max_element(deriv_x,deriv_x+nPts/5));
	Int_t pos2 = std::distance(deriv_x, max_element(deriv_x+nPts/5,deriv_x+2*nPts/5));
	Int_t pos3 = std::distance(deriv_x, max_element(deriv_x+2*nPts/5,deriv_x+3*nPts/5));
	Int_t pos4 = std::distance(deriv_x, max_element(deriv_x+3*nPts/5,deriv_x+4*nPts/5));
	Int_t pos5 = std::distance(deriv_x, max_element(deriv_x+4*nPts/5,deriv_x+5*nPts/5));
	
	Int_t mid1 = (pos1+pos2)/2;
	Int_t mid2 = (pos2+pos3)/2;
	Int_t mid3 = (pos3+pos4)/2;
	Int_t mid4 = (pos4+pos5)/2;

	Int_t mids[4] = {mid1, mid2, mid3, mid4};
	Double_t spikes[4] = {spike1+spike2,spike2+spike3, spike3+spike4, spike4+spike5};
	
	// std::set<pairs> dropoffscores;

	for(int i = 0; i < 4; i++){
		Int_t index = mids[i];
		pairs thispair = std::make_pair(x[index],spikes[i]);
		dropoffscores.insert(thispair);
	}

	return dropoffscores;

}