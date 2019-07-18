#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <TDirectory.h>
#include <TClass.h>
#include <TROOT.h>
#include <TString.h>

#include <iostream>
#include <regex>
#include <string>
namespace xjjc
{
  class showdir
  {
  public:
    showdir(TDirectory* src, int opt=0, TString flt="*");
    ~showdir() { ; }

  private:
    void enterdir(TDirectory* source);
    void printtreeinfo(TTree* thistree, TString treename="");
    int fll;
    int fopt;
    TString ffilter;
    std::vector<bool> lastll;
    bool findbranch_scan(TTree* thistree);
    bool findbranch_print(TTree* thistree);

    TString tcolor_red = "\e[38;2;178;107;107m";
    TString tcolor_blue = "\e[38;2;50;98;128m";
  };
}

int main(int argc, char* argv[])
{
  if(argc==2 || argc==3 || argc==4)
    {
      TString infname(argv[1]);
      if(infname.BeginsWith("/store/")) { infname = "root://cms-xrd-global.cern.ch/" + infname; }
      TFile* inf = TFile::Open(infname);

      if(argc==2) xjjc::showdir dirs(inf); 
      else if(argc==3) xjjc::showdir dirs(inf, atoi(argv[2])); 
      else if(argc==4) xjjc::showdir dirs(inf, atoi(argv[2]), argv[3]); 

      return 0;
    }
  std::cout<<__FUNCTION__<<": ./showdir [input] ([opt] [filter])"<<std::endl;
  std::cout<<"  [opt]>0  ([filter]=\"treename\")   : Show([opt]-1)"<<std::endl;
  std::cout<<"\e[38;5;236m  [opt]=-1 ([filter]=\"branchname\") : Print(\"branchname\")\e[0m"<<std::endl;
  std::cout<<"\e[38;5;236m  [opt]=0  ([filter]=\"branchname\") : Scan(\"branchname\")\e[0m"<<std::endl;
  return 1;
}

xjjc::showdir::showdir(TDirectory* src, int opt, TString flt) : fll(0), fopt(opt), ffilter(flt)
{
  lastll.clear();
  lastll.push_back(true);
  enterdir(src);
  std::cout<<std::endl;
}

//
void xjjc::showdir::enterdir(TDirectory* source)
{
  // source->ls();
  TKey* key;
  TIter nextkey(source->GetListOfKeys());
  if(lastll.size()==1) { std::cout<<std::endl<<"   \e[2m("<<source->GetName()<<")\e[0m"<<std::endl<<"   \e[1m./\e[0m"<<std::endl; }
  lastll.push_back(true); fll = lastll.size()-1;
  while((key = (TKey*)nextkey()))
    {
      const char *classname = key->GetClassName(), *keyname = key->GetName();
      TClass* cl = gROOT->GetClass(classname);

      // >> print
      lastll[fll] = TIter(nextkey).Next()==0;
      for(std::vector<bool>::iterator lll = lastll.begin();lll<lastll.end()-1;lll++) { std::cout<<(*lll?" ":"\u2502")<<"   "; }
      std::cout<<(lastll[fll]?"\u2514":"\u251C")<<"\u2500\u2500 \e[32m("<<classname<<")\e[0m\e[2m =>\e[0m \e[1m"<<keyname<<"\e[0m";
      if(cl->InheritsFrom(TTree::Class())) 
        { 
          std::cout<<" \e[33m("<<((TTree*)source->Get(keyname))->GetEntries()<<")\e[0m"; 
          printtreeinfo(((TTree*)source->Get(keyname)), (TString(source->GetName())+"/"+TString(keyname)));
        }
      std::cout<<std::endl;
      // << print

      if(!cl) { continue; }
      if(cl->InheritsFrom(TDirectory::Class()))
        {
          source->cd(key->GetName());
          TDirectory* subdir = gDirectory;
          enterdir(subdir);
        }
    }
  lastll.pop_back(); fll = lastll.size()-1;
}

void xjjc::showdir::printtreeinfo(TTree* thistree, TString treename)
{
  int nentries = thistree->GetEntries();
  // >> complex
  if(fopt==-1)
    {
      if(findbranch_print(thistree))
        {
          std::cout<<tcolor_red<<std::endl;
          thistree->Print(ffilter.Data()); std::cout<<"\e[0m";
        }
    }
  else if(fopt>0)
    {
      if(ffilter=="*" || std::string(treename).find(ffilter)!=std::string::npos)
        {
          std::cout<<tcolor_blue<<std::endl;
          int ievt = fopt<nentries?(fopt-1):(nentries-1);
          thistree->Show(ievt); std::cout<<"\e[0m";
        }
    }
  else if(fopt==0 && ffilter!="*")
    {
      if(findbranch_scan(thistree))
        {
          std::cout<<tcolor_blue<<std::endl;
          thistree->Scan(ffilter.Data()); std::cout<<"\e[0m";
        }
    }
  std::cout<<"\e[0m";
}

bool xjjc::showdir::findbranch_scan(TTree* thistree)
{
  TString pattern(ffilter);
  TObjArray* brs = pattern.Tokenize(":");
  for (int b = 0; b < brs->GetEntries(); b++) 
    {
      TString brname = ((TObjString*)(brs->At(b)))->String();
      if(thistree->FindBranch(brname.Data())) return true;
    }
  return false;
}

bool xjjc::showdir::findbranch_print(TTree* thistree)
{
  TString pattern(ffilter);
  pattern.ReplaceAll("*", ".*");
  std::regex regexpattern(pattern.Data());

  TObjArray *branchList = thistree->GetListOfBranches();
  int nBranch = thistree->GetNbranches();
  for(int b = 0; b < nBranch; b++)
    {
      std::string brname(branchList->At(b)->GetName());
      if(std::regex_match(brname, regexpattern)) return true;
    }
  return false;
}
