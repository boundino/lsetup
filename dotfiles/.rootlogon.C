{
  /* .rootlogon.C */
  // %TRint.cxx //

  // cmssw/root version
  std::cout<<"\033[1;38;5;74m"<<getenv("CMSSW_VERSION")<<" ==> "<<gApplication->Argv(0)<<"\033[0m"<<std::endl;

  // https://sft.its.cern.ch/jira/browse/ROOT-8452
  TString exec_file = gApplication->Argv(gApplication->Argc()-1);
  if(exec_file.BeginsWith("/store/")) { exec_file = "root://cms-xrd-global.cern.ch/"+exec_file; }
  if(exec_file.EndsWith(".root") && exec_file.BeginsWith("root:") && !exec_file.Contains("root://eoscms.cern.ch/")) 
    {       
      std::cout<<"\033[1;46m[.rootlogon.C]\033[0m Attaching file "<<exec_file<<" as file0..."<<std::endl;
      auto file0 = TFile::Open(exec_file); 
    }

  // =================================================== //

  gStyle->SetPalette(1,0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameLineColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetPalette(1,0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameLineColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetTextFont(62);
  gStyle->SetLabelFont(42,"XYZ");
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetTitleColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleXSize(.055);
  gStyle->SetTitleYSize(.055);
  gStyle->SetTitleXOffset(1.0);
  gStyle->SetTitleYOffset(1.3);
  gStyle->SetLabelSize(0.045,"XYZ");
  gStyle->SetLabelOffset(0.01,"X");
  gStyle->SetLabelOffset(0.01,"Y");
  gStyle->SetTitleColor(1,"XYZ");
  //     gStyle->SetHistFillColor(1);
  //     gStyle->SetHistFillStyle(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(3);
  gStyle->SetHistLineWidth(1);
  gStyle->SetEndErrorSize(0);
  //  gStyle->SetErrorX(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1);
  gStyle->SetOptFit(1111);
  gStyle->SetStatColor(0);
  gStyle->SetStatBorderSize(1);
  gStyle->SetOptStat(0);
  //gStyle->SetStats(0);
  gStyle->SetPadLeftMargin(0.17);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.08);
  // gStyle->SetPadRightMargin(0.15);
}
