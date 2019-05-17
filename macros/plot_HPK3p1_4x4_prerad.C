#include "map_plotter.C"


# ifndef __CINT__
int main(int argc, char **argv)
{
	map_plotter mp;
	mp.tag = "HPK3p1_4x4_prerad";
	mp.chainPath = "/Users/rheller/tb_tmp/";
	mp.debug=false;
	mp.run_start=12551;
	mp.run_end=12551;
	// static const int nchan=4;
	// static const int nchan_lgad=3;
	// static const int npad=16;//3;//16;
	mp.hitThres=40.;
	mp.photekMin=25;
	mp.photekMax=55;

	mp.angle=-2.5;
	mp.x_offset=0.040;
	mp.y_offset=0.0;
	mp.saturation =640.;
	//Divide interior of each pad in subsections (3x3 grid)
	//Specify bounds on one corner, use avg pad width including dead region to extrapolate to other pads
	//Plot boundaries at end for sanity check.

	mp.y_div = {20.5,20.95,21.4,21.85};
	mp.x_div = {0.3,0.77,1.24,1.7};

	mp.npad_y=2;
	mp.npad_x=8;
	mp.pad_width = 2.1;


	//efficiency
	mp.nbinsX=30;
	mp.nbinsY=10;
	mp.gainbinfactor=2; //coarser binning for gain maps

	//gain
	// int nbinsX=70;
	// int nbinsY=30;

	mp.minX=4;
	mp.maxX=20;
	mp.minY=30;
	mp.maxY=38;


	mp.xSliceMin=9.3;
	mp.xSliceMax=11.3;
	mp.ySliceMin=33.5;
	mp.ySliceMax=34.0;

	mp.nbinsAmp=60;
	mp.nbinsTime=60;
	mp.minAmp=0;
	mp.maxAmp=mp.saturation;
	mp.minTime=7.2e-9;
	mp.maxTime=8.8e-9;

    mp.makeMaps();
    

}
# endif