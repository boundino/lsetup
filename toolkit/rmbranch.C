#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <TDirectory.h>
#include <TClass.h>
#include <TObject.h>
#include <TROOT.h>

#include <map>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

namespace xjjc
{
  std::string str_replaceall(std::string strs, std::string sub, std::string newsub);
  bool str_contains(std::string str1, std::string str2) { return str1.find(str2)!=std::string::npos; }
  std::vector<std::string> speciallist = {" ", "/", "(", ")", "^", "#", "%", "$", ",", ".", "*"};
  std::string str_replaceallspecial(std::string strs);
}

namespace xjjc
{
  class copydir_recur
  {
  public:
    std::map<TTree*, TDirectory*> trees_output;
    std::map<TTree*, TDirectory*> trees_input;
    copydir_recur(TDirectory* source, TDirectory* des, int fnevt=-1);

  private:
    int nevt; // default = -1
    void copydir(TDirectory* source);
    int fll;
    std::vector<bool> lastll;
    bool lastiter(const TIter& current);
  };
}

void rmbranch(std::string inputname, 
              std::string treename, std::string branchname, bool reverse = false,
              std::string outputname="")
{
  if(outputname == "")
    { outputname = xjjc::str_replaceall(inputname, ".root", ("__rm__"+xjjc::str_replaceallspecial(treename)+(reverse?"_v_":"_")+xjjc::str_replaceallspecial(branchname)+"br.root")); }
  else if(!xjjc::str_contains(outputname, ".root") || inputname==outputname)
    { std::cout<<__FUNCTION__<<": error: invalid outputname."<<std::endl<<"  "<<outputname<<std::endl; return; }

  TFile* inf = new TFile(inputname.c_str());
  if(!inf->IsOpen()) { std::cout<<__FUNCTION__<<": error: invalid input."<<std::endl<<"  "<<inputname<<std::endl; return; }
  TFile* outf = new TFile(outputname.c_str(), "recreate");

  std::cout<<std::endl<<" -- Reading input trees"<<std::endl;
  std::cout<<" -- Removing branch(es) \e[0m"<<(reverse?"\e[31;1mexcept for \e[0m":"")<<"\e[4m"<<branchname<<"\e[0m in \e[4m"<<treename<<"\e[0m"<<std::endl;
  TTree* nt = (TTree*)inf->Get(treename.c_str());
  if(!nt) { std::cout<<__FUNCTION__<<": error: invalid tree."<<std::endl<<"  "<<treename<<std::endl; return; }  

  // >>
  if(!reverse)
    { nt->SetBranchStatus(branchname.c_str(), 0); }
  else
    {
      nt->SetBranchStatus("*", 0);
      nt->SetBranchStatus(branchname.c_str(), 1);
    }
  // <<
  // >> 
  xjjc::copydir_recur dirs(inf, outf, -1);
  // <<

  std::cout<<" -- Writing into new file"<<std::endl;
  outf->Write();
  outf->Close();
  std::cout<<"\e[2mOutput file found:\e[0m "<<outputname<<std::endl<<std::endl;

}

/* ==================== */
std::string xjjc::str_replaceall(std::string strs, std::string sub, std::string newsub)
{
  std::string result(strs);
  std::string str(strs);
  size_t pos = str.find(sub, 0);
  size_t thispos = 0;
  while(pos != std::string::npos)
    {
      result.replace(pos + thispos, sub.size(), newsub);
      thispos += (newsub.size() - sub.size());
      pos = str.find(sub, pos+1);
    }
  return result;
}
std::string xjjc::str_replaceallspecial(std::string strs)
{
  std::string result(strs);
  for(auto& isp : xjjc::speciallist) { result = xjjc::str_replaceall(result, isp, "-"); }
  return result;
}

/* ==================== */
xjjc::copydir_recur::copydir_recur(TDirectory* src, TDirectory* des, int fnevt/*=-1*/) : nevt(fnevt), fll(0)
{
  trees_output.clear();
  trees_input.clear();
  lastll.clear();
  lastll.push_back(true);
  des->cd();
  std::cout<<std::endl<<"   \e[2m("<<src->GetName()<<")\e[0m"
           <<std::endl<<"   \e[1m./\e[0m"<<std::endl;
  copydir(src);
  std::cout<<std::endl;
  des->cd();
}

void xjjc::copydir_recur::copydir(TDirectory* source)
{
  // source->ls();
  TDirectory* savdir = gDirectory;
  TDirectory* adir = savdir;
  if(source->GetMotherDir()) adir = savdir->mkdir(source->GetName());
  adir->cd();
  TKey* key;
  TIter nextkey(source->GetListOfKeys());
  lastll.push_back(true); fll = lastll.size()-1;
  while((key = (TKey*)nextkey()))
    {
      const std::string classname(key->GetClassName()), keyname(key->GetName());
      TClass* cl = gROOT->GetClass(classname.c_str());

      // >> print
      lastll[fll] = lastiter(nextkey);
      for(auto lll = lastll.begin();lll<lastll.end()-1;lll++) { std::cout<<(*lll?" ":"\u2502")<<"  "; }
      std::cout<<(lastll[fll]?"\u2514":"\u251C")<<"\u2500 \e[2m("<<classname<<") =>\e[0m \e[1m"<<keyname<<"\e[0m";
      if(cl->InheritsFrom(TTree::Class())) { std::cout<<" \e[2m("<<((TTree*)source->Get(keyname.c_str()))->GetEntries()<<")\e[0m"; }
      std::cout<<std::endl;
      // << print

      if(!cl) { std::cout<<"\e[31;1m warning: unknown class "<<classname<<"\e[0m"<<std::endl; continue; }
      if(cl->InheritsFrom(TDirectory::Class()))
        {
          source->cd(key->GetName());
          TDirectory* subdir = gDirectory;
          adir->cd();
          copydir(subdir);
          adir->cd();
        }
      else if(cl->InheritsFrom(TTree::Class()))
        {
          TTree* nt = (TTree*)source->Get(key->GetName());
          trees_input.insert(std::pair(nt, source));
          adir->cd();
          TTree* nt_new = nt->CloneTree(nevt); // nevt
          trees_output.insert(std::pair(nt_new, adir));
        }
      else
        {
          source->cd();
          TObject* obj = key->ReadObj();
          adir->cd();
          obj->Write();
          delete obj;
        }
    }
  lastll.pop_back(); fll = lastll.size()-1;
  adir->SaveSelf(kTRUE);
  savdir->cd();
}

bool xjjc::copydir_recur::lastiter(const TIter& current)
{
  TIter iterclone(current);
  return iterclone()==0;
}

int main(int argc, char* argv[])
{
  std::vector<std::string> argvv;
  bool isreverse = false;
  for(int v=1; v<argc; v++)
    {
      if(std::string(argv[v]) == "-v") { isreverse = true; }
      else { argvv.push_back(std::string(argv[v])); }
    }
  if(argvv.size()==4) { rmbranch(argvv[0], argvv[1], argvv[2], isreverse, argvv[3]); return 0; }
  if(argvv.size()==3) { rmbranch(argvv[0], argvv[1], argvv[2], isreverse); return 0; }
  std::cout<<__FUNCTION__<<": ./rmbranch [input] [treename] (-v) [branchname] (optional)[output]"<<std::endl;
  return 1;
}


