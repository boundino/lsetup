#ifndef _XJJROOT_DFITTER_H_
#define _XJJROOT_DFITTER_H_

/* dfitter.h */

#include "TF1.h"
#include "TH1.h"
#include "TString.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"

namespace xjjroot
{
  class dfitter
  {
  public:
    const Int_t npar = 12;
    
    TF1* fun_f;
    TF1* fun_mass;
    TF1* fun_swap;
    TF1* fun_background;
    TF1* fun_not_mass;

    Double_t S;
    Double_t B;
    Double_t yield;
    Double_t yieldErr;

    dfitter(Option_t* option="");
    ~dfitter() {};
    TF1* fit(TH1* h, TH1* hMCSignal, TH1* hMCSwapped, TString outputname, TString collisionsyst, std::vector<TString> vtex);
    void setoption(Option_t* option="");
    
  private:
    TString foption;
    Bool_t fplotdetails;
    Bool_t ffitverbose;
    Bool_t fpapermode;
    Bool_t ftmvamode;

    const Double_t setparam0 = 100.;
    const Double_t setparam1 = 1.865;
    const Double_t setparam2 = 0.03;
    const Double_t setparam8 = 0.1;
    const Double_t setparam9 = 0.1;
    const Double_t setparam10 = 0.005;
    const Double_t fixparam1 = 1.865;
    Double_t fixparam7;
    
    const Double_t mass_dzero = 1.8649;
    Double_t d_mass_signal = 0.045;
    Double_t d_mass_sideband_l = 0.01;
    Double_t d_mass_sideband_h = 0.015;
    Double_t mass_dzero_signal_l = mass_dzero - d_mass_signal;
    Double_t mass_dzero_signal_h = mass_dzero + d_mass_signal;
    
    const Double_t n_hist_dzero = 60;
    const Double_t min_hist_dzero = 1.7;
    const Double_t max_hist_dzero = 2.0;
    const Double_t binwid_hist_dzero = (max_hist_dzero-min_hist_dzero)/n_hist_dzero;

    TLine* line_signal_l;
    TLine* line_signal_h;

    void init();
    void reset();
    void setfunstyle();
    void sethist(TH1* h);
    void setfunparameters();
    void createfun();
    void deletefun();
    void drawCMS(TString collision, TString snn="5.02");
    void drawtex(Double_t x, Double_t y, const char* text, Float_t tsize=0.04, Short_t align=12);
    void drawleg(TH1* h);
    void setgstyle();
  };
}

xjjroot::dfitter::dfitter(Option_t* option/*=""*/)
{
  setoption(option);
  init();
}

TF1* xjjroot::dfitter::fit(TH1* h, TH1* hMCSignal, TH1* hMCSwapped, TString outputname, TString collisionsyst, std::vector<TString> vtex)
{
  reset();
  init();

  TString fitoption = ffitverbose?"L m":"L m q";
  sethist(h);
  sethist(hMCSignal);
  sethist(hMCSwapped);

  setgstyle();
    
  TCanvas* c = new TCanvas("c", "" , 600, 600);
  
  fun_f->SetParLimits(4,-1000,1000);
  fun_f->SetParLimits(10,0.001,0.05);
  fun_f->SetParLimits(2,0.01,0.5);
  fun_f->SetParLimits(8,0.02,0.2);
  fun_f->SetParLimits(7,0,1);
  fun_f->SetParLimits(9,0,1);
    
  // -- fit MC
  fun_f->FixParameter(3,0);
  fun_f->FixParameter(4,0);
  fun_f->FixParameter(5,0);
  fun_f->FixParameter(6,0);

  //  - fit signal 
  fun_f->FixParameter(11,0);
  fun_f->FixParameter(1,fixparam1);
  fun_f->FixParameter(7,1);
  fun_f->FixParameter(8,1);
  fun_f->SetParameter(0,setparam0);
  fun_f->SetParameter(1,setparam1);
  fun_f->SetParameter(2,setparam2);
  fun_f->SetParameter(10,setparam10);
  fun_f->SetParameter(9,setparam9);

  hMCSignal->Fit("fun_f","q","",min_hist_dzero,max_hist_dzero);
  hMCSignal->Fit("fun_f","q","",min_hist_dzero,max_hist_dzero);
  fun_f->ReleaseParameter(1);
  hMCSignal->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSignal->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSignal->Fit("fun_f",fitoption,"",min_hist_dzero,max_hist_dzero);

  fun_f->FixParameter(1,fun_f->GetParameter(1));
  fun_f->FixParameter(2,fun_f->GetParameter(2));
  fun_f->FixParameter(10,fun_f->GetParameter(10));
  fun_f->FixParameter(9,fun_f->GetParameter(9));

  fixparam7 = fun_f->GetParameter(0);

  //   - fit swapped
  fun_f->FixParameter(7,0);
  fun_f->ReleaseParameter(8);
  fun_f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSwapped->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSwapped->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  hMCSwapped->Fit("fun_f",fitoption,"",min_hist_dzero,max_hist_dzero);
  
  fixparam7 = fixparam7/(fun_f->GetParameter(0)+fixparam7);
  fun_f->FixParameter(7, fixparam7);
  // fun_f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  fun_f->FixParameter(8,fun_f->GetParameter(8));

  //  -- fit data
  fun_f->ReleaseParameter(3);
  fun_f->ReleaseParameter(4);
  fun_f->ReleaseParameter(5);
  fun_f->ReleaseParameter(6);
  
  h->Fit("fun_f","q","",min_hist_dzero,max_hist_dzero);
  h->Fit("fun_f","q","",min_hist_dzero,max_hist_dzero);
  fun_f->ReleaseParameter(1);
  fun_f->SetParLimits(1,1.86,1.87);
  fun_f->ReleaseParameter(11);
  // fun_f->SetParLimits(11,-0.5,0.5);
  h->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  h->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  h->Fit("fun_f","L q","",min_hist_dzero,max_hist_dzero);
  h->Fit("fun_f",fitoption,"",min_hist_dzero,max_hist_dzero);

  setfunparameters();

  yield = fun_mass->Integral(min_hist_dzero,max_hist_dzero)/binwid_hist_dzero;
  yieldErr = fun_mass->Integral(min_hist_dzero,max_hist_dzero)/binwid_hist_dzero*fun_mass->GetParError(0)/fun_mass->GetParameter(0);
  S = fun_mass->Integral(mass_dzero_signal_l,mass_dzero_signal_h)/binwid_hist_dzero;
  B = fun_background->Integral(mass_dzero_signal_l,mass_dzero_signal_h)/binwid_hist_dzero + fun_swap->Integral(mass_dzero_signal_h,mass_dzero_signal_h)/binwid_hist_dzero;
  
  h->Draw("e");
  fun_background->Draw("same");   
  fun_mass->Draw("same");
  fun_swap->Draw("same");
  if(ftmvamode)
    {
      fun_not_mass->SetRange(mass_dzero_signal_l,mass_dzero_signal_h);
      fun_not_mass->Draw("same");
      line_signal_l->SetY2(fun_f->Eval(mass_dzero_signal_l));
      line_signal_h->SetY2(fun_f->Eval(mass_dzero_signal_h));
      line_signal_l->Draw();
      line_signal_h->Draw();
    }
  fun_f->Draw("same");

  drawleg(h);
  drawCMS(collisionsyst);

  Float_t texxpos = 0.22, texypos = 0.90, texdypos = 0.055;
  for(std::vector<TString>::iterator it=vtex.begin(); it!=vtex.end(); it++)
    {
      drawtex(texxpos, texypos=(texypos-texdypos), *it);
    }
  if(fplotdetails)
    {
      drawtex(texxpos, texypos=(texypos-texdypos), Form("N = %.0f #pm %.0f",yield,yieldErr));
      if(ftmvamode)
        {
          drawtex(texxpos, texypos=(texypos-texdypos), Form("S/#sqrt{S+B} = %.1f",S/TMath::Sqrt(S+B)));
          drawtex(texxpos, texypos=(texypos-texdypos), Form("S = %.0f, B = %.0f",S,B));
        }
    }

  c->SaveAs(Form("%s.pdf",outputname.Data()));

  delete c;  
  return fun_mass;
}

void xjjroot::dfitter::setoption(Option_t* option/*=""*/)
{
  foption = option;
  fplotdetails = false;
  if(foption.Contains("Y")) fplotdetails = true;
  ftmvamode = false;
  if(foption.Contains("T")) ftmvamode = true;
  fpapermode = false;
  if(foption.Contains("P"))
    {
      fpapermode = true;
      fplotdetails = false;
    } 
  ffitverbose = false;
  if(foption.Contains("V")) ffitverbose = true;
}

void xjjroot::dfitter::reset()
{
  deletefun();

  S = 0;
  B = 0;
  yield = 0;
  yieldErr = 0;

}

void xjjroot::dfitter::init()
{
  createfun();
  setfunstyle();

  S = 0;
  B = 0;
  yield = 0;
  yieldErr = 0;
}

void xjjroot::dfitter::createfun()
{
  fun_f = new TF1("fun_f","[0]*([7]*([9]*TMath::Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*TMath::Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*TMath::Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", min_hist_dzero, max_hist_dzero);  
  fun_background = new TF1("fun_background","[0]+[1]*x+[2]*x*x+[3]*x*x*x", min_hist_dzero, max_hist_dzero);
  fun_mass = new TF1("fun_mass","[0]*([3]*([4]*TMath::Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*TMath::Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))", min_hist_dzero, max_hist_dzero);
  fun_swap = new TF1("fun_swap","[0]*(1-[2])*TMath::Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))", min_hist_dzero, max_hist_dzero);
  fun_not_mass = new TF1("fun_not_mass","[0]*(1-[2])*TMath::Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))+[5]+[6]*x+[7]*x*x+[8]*x*x*x", min_hist_dzero, max_hist_dzero);

  line_signal_l = new TLine(mass_dzero_signal_l, 0, mass_dzero_signal_l, 0);
  line_signal_h = new TLine(mass_dzero_signal_h, 0, mass_dzero_signal_h, 0);
}

void xjjroot::dfitter::deletefun()
{
  delete fun_f;
  delete fun_background;
  delete fun_mass;
  delete fun_swap;
  delete fun_not_mass;

  delete line_signal_l;
  delete line_signal_h;
}

void xjjroot::dfitter::setfunstyle()
{
  fun_background->SetLineColor(4);
  fun_background->SetLineStyle(2);
  fun_background->SetLineWidth(3);

  fun_mass->SetLineColor(kOrange-3);
  fun_mass->SetLineStyle(2);
  fun_mass->SetLineWidth(3);
  fun_mass->SetFillColor(kOrange-3);
  fun_mass->SetFillStyle(3002);

  fun_swap->SetLineColor(kGreen+4);
  fun_swap->SetLineStyle(1);
  fun_swap->SetLineWidth(3);
  fun_swap->SetFillColor(kGreen+4);
  fun_swap->SetFillStyle(3005);

  fun_not_mass->SetLineColor(12);
  fun_not_mass->SetLineStyle(2);
  fun_not_mass->SetLineWidth(2);

  line_signal_l->SetLineColor(12);
  line_signal_l->SetLineStyle(2);
  line_signal_l->SetLineWidth(2);

  line_signal_h->SetLineColor(12);
  line_signal_h->SetLineStyle(2);
  line_signal_h->SetLineWidth(2);

  if(fpapermode) {return;}

}

void xjjroot::dfitter::sethist(TH1* h)
{
  h->SetMaximum(-1111);
  h->SetXTitle("m_{#piK} (GeV/c^{2})");
  h->SetYTitle(Form("Entries / (%.0f MeV/c^{2})", binwid_hist_dzero*1.e+3));
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetAxisRange(0,h->GetMaximum()*1.4*1.2,"Y");
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

  if(fpapermode) {return;}
}

void xjjroot::dfitter::setfunparameters()
{
  fun_background->SetParameters(fun_f->GetParameter(3), fun_f->GetParameter(4), fun_f->GetParameter(5), fun_f->GetParameter(6));
  fun_background->SetParError(0,fun_f->GetParError(3));
  fun_background->SetParError(1,fun_f->GetParError(4));
  fun_background->SetParError(2,fun_f->GetParError(5));
  fun_background->SetParError(3,fun_f->GetParError(6));
  
  fun_mass->SetParameters(fun_f->GetParameter(0),fun_f->GetParameter(1),fun_f->GetParameter(2),fun_f->GetParameter(7),fun_f->GetParameter(9),fun_f->GetParameter(10),fun_f->GetParameter(11));
  fun_mass->SetParError(0,fun_f->GetParError(0));
  fun_mass->SetParError(1,fun_f->GetParError(1));
  fun_mass->SetParError(2,fun_f->GetParError(2));
  fun_mass->SetParError(3,fun_f->GetParError(7));
  fun_mass->SetParError(4,fun_f->GetParError(9));
  fun_mass->SetParError(5,fun_f->GetParError(10));
  fun_mass->SetParError(6,fun_f->GetParError(11));
    
  fun_swap->SetParameters(fun_f->GetParameter(0),fun_f->GetParameter(1),fun_f->GetParameter(7),fun_f->GetParameter(8),fun_f->GetParameter(11));
  fun_swap->SetParError(0,fun_f->GetParError(0));
  fun_swap->SetParError(1,fun_f->GetParError(1));
  fun_swap->SetParError(2,fun_f->GetParError(7));
  fun_swap->SetParError(3,fun_f->GetParError(8));
  fun_swap->SetParError(4,fun_f->GetParError(11));

  fun_not_mass->SetParameters(fun_swap->GetParameter(0),fun_swap->GetParameter(1),fun_swap->GetParameter(2),fun_swap->GetParameter(3),fun_swap->GetParameter(4),
                              fun_background->GetParameter(0),fun_background->GetParameter(1),fun_background->GetParameter(2),fun_background->GetParameter(3));
  fun_not_mass->SetParError(0,fun_swap->GetParError(0));
  fun_not_mass->SetParError(1,fun_swap->GetParError(1));
  fun_not_mass->SetParError(2,fun_swap->GetParError(2));
  fun_not_mass->SetParError(3,fun_swap->GetParError(3));
  fun_not_mass->SetParError(4,fun_swap->GetParError(4));
  fun_not_mass->SetParError(5,fun_background->GetParError(0));
  fun_not_mass->SetParError(6,fun_background->GetParError(1));
  fun_not_mass->SetParError(7,fun_background->GetParError(2));
  fun_not_mass->SetParError(8,fun_background->GetParError(3));
}

void xjjroot::dfitter::drawleg(TH1* h)
{
  TLegend* leg = new TLegend(0.65, 0.58, 0.85, 0.88, NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);

  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(fun_f,"Fit","l");
  leg->AddEntry(fun_mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(fun_swap,"K-#pi swapped","f");
  leg->AddEntry(fun_background,"Combinatorial","l");

  if(fpapermode) {return;}
  leg->Draw("same");
}

void xjjroot::dfitter::drawCMS(TString collision, TString snn/*="5.02"*/)
{
  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = %s TeV", collision.Data(), snn.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);

  if(fpapermode) {return;}
  texCms->Draw();
  texCol->Draw();
}

void xjjroot::dfitter::drawtex(Double_t x, Double_t y, const char* text, Float_t tsize/*=0.04*/, Short_t align/*=12*/)
{
  TLatex* tex = new TLatex(x, y, text);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextAlign(align);
  tex->SetTextSize(tsize);
  tex->Draw();
}

void xjjroot::dfitter::setgstyle()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
}

#endif
