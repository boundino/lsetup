#ifndef _XJJDFITTER_H
#define _XJJDFITTER_H

/* xjjdfitter.h */

#include "xjjrootuti.h"
#include "xjjuti.h"

namespace xjjdfitter
{
  const double mass_dzero = 1.8649;
  const double d_mass_signal = 0.045;
  const double d_mass_sideband_l = 0.01;
  const double d_mass_sideband_h = 0.015;

  const double mass_dzero_signal_l = mass_dzero - d_mass_signal;
  const double mass_dzero_signal_h = mass_dzero + d_mass_signal;
  
  const double min_hist_dzero = 1.7;
  const double max_hist_dzero = 2.0;
  const double N_HIST_DZERO = 60;
  const double BINWID_HIST_DZERO = (max_hist_dzero-min_hist_dzero)/N_HIST_DZERO;
  
}

TF1* xjjdfitter::fit(TH1D* h, TH1D* hMCSignal, TH1D* hMCSwapped, 
                     TString outputname, Float_t* results, TString collisionsyst,
                     Bool_t verbose, Bool_t ifsethmaximum,
                     const char* fmt...)
{

  Double_t setparam0 = 100.;
  Double_t setparam1 = 1.865;
  Double_t setparam2 = 0.03;
  Double_t setparam10 = 0.005;
  Double_t setparam8 = 0.1;
  Double_t setparam9 = 0.1;
  Double_t fixparam1 = 1.865;
    
  TString fitoption = verbose?"L m":"L m q";
    
  TCanvas* c = new TCanvas("c","",600,600);
  
  TF1* f = new TF1("f","[0]*([7]*([9]*TMath::Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*TMath::Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*TMath::Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", min_hist_dzero, max_hist_dzero);    
  f->SetLineColor(kRed);
    
  f->SetParLimits(4,-1000,1000);
  f->SetParLimits(10,0.001,0.05);
  f->SetParLimits(2,0.01,0.5);
  f->SetParLimits(8,0.02,0.2);
  f->SetParLimits(7,0,1);
  f->SetParLimits(9,0,1);
    
  // -- fit MC
  f->FixParameter(3,0);
  f->FixParameter(4,0);
  f->FixParameter(5,0);
  f->FixParameter(6,0);

  //  - fit signal 
  f->FixParameter(11,0);
  f->FixParameter(1,fixparam1);
  f->FixParameter(7,1);
  f->FixParameter(8,1);
  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(10,setparam10);
  f->SetParameter(9,setparam9);

  hMCSignal->Fit("f","q","",min_hist_dzero,max_hist_dzero);
  hMCSignal->Fit("f","q","",min_hist_dzero,max_hist_dzero);
  f->ReleaseParameter(1);
  hMCSignal->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSignal->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSignal->Fit("f",fitoption,"",min_hist_dzero,max_hist_dzero);

  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));

  //   - fit swapped
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSwapped->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSwapped->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSwapped->Fit("f",fitoption,"",min_hist_dzero,max_hist_dzero);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));

  //  -- fit data
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);
  
  h->Fit("f","q","",min_hist_dzero,max_hist_dzero);
  h->Fit("f","q","",min_hist_dzero,max_hist_dzero);
  f->ReleaseParameter(1);
  f->SetParLimits(1,1.86,1.87);
  f->ReleaseParameter(11);
  // f->SetParLimits(11,-0.5,0.5);
  h->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  h->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  h->Fit("f","L q","",min_hist_dzero,max_hist_dzero);
  h->Fit("f",fitoption,"",min_hist_dzero,max_hist_dzero);
    
  TF1* background = new TF1("background","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetLineStyle(2);
    
  TF1* mass = new TF1("mass","[0]*([3]*([4]*TMath::Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*TMath::Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(11));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetParError(6,f->GetParError(11));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
    
  TF1* massSwap = new TF1("massSwap","[0]*(1-[2])*TMath::Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8),f->GetParameter(11));
  massSwap->SetParError(0,f->GetParError(0));
  massSwap->SetParError(1,f->GetParError(1));
  massSwap->SetParError(2,f->GetParError(7));
  massSwap->SetParError(3,f->GetParError(8));
  massSwap->SetFillColor(kGreen+4);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineColor(kGreen+4);
  massSwap->SetLineWidth(3);
  massSwap->SetLineStyle(1);

  TF1* backgroundnSwap = new TF1("backgroundnSwap","[0]*(1-[2])*TMath::Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))+[5]+[6]*x+[7]*x*x+[8]*x*x*x");
  backgroundnSwap->SetParameters(massSwap->GetParameter(0),massSwap->GetParameter(1),massSwap->GetParameter(2),massSwap->GetParameter(3),massSwap->GetParameter(4),
                                 background->GetParameter(0),background->GetParameter(1),background->GetParameter(2),background->GetParameter(3));
  backgroundnSwap->SetLineStyle(2);
  backgroundnSwap->SetLineWidth(2);
  backgroundnSwap->SetLineColor(12);
  backgroundnSwap->Draw();
  
  h->SetXTitle("m_{#piK} (GeV/c^{2})");
  h->SetYTitle("Entries / (5 MeV/c^{2})");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  if(ifsethmaximum) h->SetAxisRange(0,h->GetMaximum()*1.4*1.2,"Y");
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitleOffset(1.8);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  h->SetStats(0);
  h->Draw("e");

  background->SetRange(min_hist_dzero,max_hist_dzero);
  background->Draw("same");   
  mass->SetRange(min_hist_dzero,max_hist_dzero);
  mass->Draw("same");
  massSwap->SetRange(min_hist_dzero,max_hist_dzero);
  massSwap->Draw("same");
  backgroundnSwap->SetRange(mass_dzero_signal_l,mass_dzero_signal_h);
  backgroundnSwap->Draw("same");
  f->Draw("same");

  TLine* line_signal_l = new TLine(mass_dzero_signal_l, 0, mass_dzero_signal_l, f->Eval(mass_dzero_signal_l));
  line_signal_l->SetLineStyle(2);
  line_signal_l->SetLineWidth(2);
  line_signal_l->SetLineColor(12);
  line_signal_l->Draw();
  TLine* line_signal_h = new TLine(mass_dzero_signal_h, 0, mass_dzero_signal_h, f->Eval(mass_dzero_signal_h));
  line_signal_h->SetLineStyle(2);
  line_signal_h->SetLineWidth(2);
  line_signal_h->SetLineColor(12);
  line_signal_h->Draw();
  
  TLegend* leg = new TLegend(0.65, 0.58, 0.82, 0.88,NULL,"brNDC");
  xjjrootuti::setleg(leg, 0.04);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  xjjrootuti::drawCMS(collisionsyst);

  float texxpos = xjjrootuti::x_tex_left_top + 0.01;
  float texypos = xjjrootuti::y_tex_left_top;
  TLatex* texdphi = new TLatex(xjjrootuti::x_tex_left_top,texypos=(texypos-xjjrootuti::dy_tex_left_top),Form("%.2f < #Delta#phi < %.2f",dphimin,dphimax));
  xjjrootuti::settexndraw(texdphi);
  TLatex* textrkpt = new TLatex(xjjrootuti::x_tex_left_top,texypos=(texypos-xjjrootuti::dy_tex_left_top),Form("|p_{T}^{trk}_{lead D}| > %s GeV/c", xjjuti::number_remove_zero(leading_trkptmin).c_str()));
  xjjrootuti::settexndraw(textrkpt);
  TLatex* texrap = new TLatex(xjjrootuti::x_tex_left_top,texypos=(texypos-xjjrootuti::dy_tex_left_top),"|y^{D}| < 1");
  xjjrootuti::settexndraw(texrap);
  TLatex* texleadpt = new TLatex(xjjrootuti::x_tex_left_top,texypos=(texypos-xjjrootuti::dy_tex_left_top),Form("p_{T}^{D}_{lead} > %s GeV/c",xjjuti::number_remove_zero(leading_ptmin).c_str()));
  xjjrootuti::settexndraw(texleadpt);
  TLatex* texpt = new TLatex(xjjrootuti::x_tex_left_top ,texypos=(texypos-xjjrootuti::dy_tex_left_top),Form("p_{T}^{D} > %s GeV/c",xjjuti::number_remove_zero(other_ptmin).c_str()));
  xjjrootuti::settexndraw(texpt);
  
  c->SaveAs(Form("%s.pdf",outputname.Data()));

  Double_t yield = mass->Integral(min_hist_dzero,max_hist_dzero)/BINWID_HIST_DZERO;
  Double_t yieldErr = mass->Integral(min_hist_dzero,max_hist_dzero)/BINWID_HIST_DZERO*mass->GetParError(0)/mass->GetParameter(0);
  
  results[0] = yield; // S
  results[1] = background->Integral(mass_dzero_signal_l,mass_dzero_signal_h)/BINWID_HIST_DZERO + massSwap->Integral(mass_dzero_signal_h,mass_dzero_signal_h)/BINWID_HIST_DZERO; // B

  delete c;
  
  return mass;
}

#endif
