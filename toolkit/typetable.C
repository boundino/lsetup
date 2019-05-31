#include <RtypesCore.h>
#include <TString.h>

#include "typetable.h"

void typetable()
{
  xjjc::typeinfo<char>       tt_char("char");             tt_char.printinfo(true);    
  xjjc::typeinfo<Char_t>     tt_Char_t("Char_t");         tt_Char_t.printinfo();      
  xjjc::typeinfo<UChar_t>    tt_UChar_t("UChar_t");       tt_UChar_t.printinfo();     
  xjjc::typeinfo<Short_t>    tt_Short_t("Short_t");       tt_Short_t.printinfo();     
  xjjc::typeinfo<UShort_t>   tt_UShort_t("UShort_t");     tt_UShort_t.printinfo();    
  xjjc::typeinfo<int>        tt_int("int");               tt_int.printinfo();         
  xjjc::typeinfo<Int_t>      tt_Int_t("Int_t");           tt_Int_t.printinfo();       
  xjjc::typeinfo<UInt_t>     tt_UInt_t("UInt_t");         tt_UInt_t.printinfo();      
  xjjc::typeinfo<float>      tt_float("float");           tt_float.printinfo();       
  xjjc::typeinfo<Float_t>    tt_Float_t("Float_t");       tt_Float_t.printinfo();     
  xjjc::typeinfo<Float16_t>  tt_Float16_t("Float16_t");   tt_Float16_t.printinfo();   
  xjjc::typeinfo<double>     tt_double("double");         tt_double.printinfo();      
  xjjc::typeinfo<Double_t>   tt_Double_t("Double_t");     tt_Double_t.printinfo();    
  xjjc::typeinfo<Double32_t> tt_Double32_t("Double32_t"); tt_Double32_t.printinfo();  
  xjjc::typeinfo<Long64_t>   tt_Long64_t("Long64_t");     tt_Long64_t.printinfo();    
  xjjc::typeinfo<ULong64_t>  tt_ULong64_t("ULong64_t");   tt_ULong64_t.printinfo();   
  xjjc::typeinfo<bool>       tt_bool("bool");             tt_bool.printinfo();        
  xjjc::typeinfo<Bool_t>     tt_Bool_t("Bool_t");         tt_Bool_t.printinfo();      
  xjjc::typeinfo<TString>    tt_TString("TString");       tt_TString.printinfo(false, true); 
}

int main()
{
  typetable();
  return 0;
}
