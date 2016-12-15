#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <sstream>
#include "TFile.h"
#include <fstream>
#include <string>
#include "TColor.h"

using namespace std;



void addToStack(const TString& filename, const TString& variable,  const TString& legentry, Bool_t sumw2, const EColor& fillcolor, Int_t MarkerStyle,  const EColor& MarkerColor, THStack& hs) {
  
   TFile *f = new TFile(Form("%s",filename.Data()), "R");
   //f->ls();
   
   TDirectoryFile * tagsDumper = (TDirectoryFile*)f->Get("tagsDumper");
   TDirectoryFile* histograms = (TDirectoryFile*)tagsDumper->Get("histograms");

   TH1F* pt_muon = (TH1F*)histograms->Get(variable.Data());
   //std::cout<<pt_muon->GetBinContent(4)<<std::endl;
   //pt_muon->SetName(Form("%s_%s", filename->Data(),variable->Data()));
   
   if (sumw2){
     pt_muon->Sumw2();
     pt_muon->SetMarkerStyle(20);
   }
   else {
     pt_muon->SetFillColor(fillcolor);
     pt_muon->SetMarkerStyle(MarkerStyle);
     pt_muon->SetMarkerColor(MarkerColor);
     //if (!sumw2 && !filename.Contains("QCD")) {
     pt_muon->Scale(12.);
   }
   pt_muon->GetXaxis()->SetTitle("#slash{E}_{T} (GeV)");
   pt_muon->GetXaxis()->SetLabelFont(42);
   pt_muon->GetXaxis()->SetLabelOffset(0.007);
   pt_muon->GetXaxis()->SetLabelSize(0.045);
   pt_muon->GetXaxis()->SetTitleSize(0.06);
   pt_muon->GetXaxis()->SetTitleOffset(0.95);
   pt_muon->GetXaxis()->SetTitleFont(42);
   //pt_muon->GetYaxis()->SetTitle("Events / 0.5");
   pt_muon->GetYaxis()->SetLabelFont(42);
   pt_muon->GetYaxis()->SetLabelSize(0.045);
   pt_muon->GetYaxis()->SetTitleSize(0.06);
   pt_muon->GetYaxis()->SetTitleOffset(1.45);
   pt_muon->GetYaxis()->SetTitleFont(42);
   pt_muon->Rebin(2);
   hs.Add(pt_muon, "hist");

   
}


void addToLegend(const TString& filename, const TString& legentry, Bool_t sumw2, const EColor& fillcolor, Int_t MarkerStyle,  const EColor& MarkerColor, const TString& variable, TLegend& leg) {
  
   TFile *f = new TFile(Form("%s",filename.Data()), "R");
   //f->ls();
   
   TDirectoryFile * tagsDumper = (TDirectoryFile*)f->Get("tagsDumper");
   TDirectoryFile* histograms = (TDirectoryFile*)tagsDumper->Get("histograms");

   TH1F* pt_muon = (TH1F*)histograms->Get(variable.Data());

   pt_muon->SetFillColor(fillcolor);
   pt_muon->SetMarkerStyle(1);
   pt_muon->SetMarkerColor(MarkerColor);
   pt_muon->SetFillStyle(1001);
   pt_muon->SetLineColor(1);
   pt_muon->SetLineStyle(1);
   pt_muon->SetLineWidth(1);
   pt_muon->SetMarkerSize(1);

   pt_muon->GetXaxis()->SetTitle("p_{T, muon}");
   
   if (sumw2){
     pt_muon->SetFillColor(1);
     pt_muon->SetMarkerStyle(20);
     leg.AddEntry(pt_muon,Form("%s",legentry.Data()),"p");
   }
   else
     leg.AddEntry(pt_muon,Form("%s",legentry.Data()),"f");
      
     
}

void stack_Approval_v2(const TString& variable, const TString& dilepton, const Int_t nBinsX, const Float_t binXLow, const Float_t binXUp, const TString& iso) {
   // Example of stacked histograms: class THStack
   //
   //  Author: Rene Brun

   gStyle->SetOptStat(0);

   TLegend * leg  = new TLegend(0.6129032,0.5035989,0.7983871,0.9156118,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.0446761);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetNColumns(2);

   TString folder = "/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/MetaData/scripts/data_jobs_1/";
   THStack *hs_data = new THStack("hs_data","Signal Region");
   
   addToStack(Form("%s/%s.root", folder.Data(),"all"), "Data_13TeV_VBFTag_1mass", "Single_top", true, kBlack, 21, kBlack, *hs_data );

   addToLegend(Form("%s/%s.root", folder.Data(),"all"), "Data", true, kBlack, 21, kBlack, "Data_13TeV_VBFTag_1mass", *leg);

   folder = "/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/MetaData/scripts/bkg_jobs_1/";
   THStack *hs = new THStack("hs","");

   //bkg
   /*
   6 dipho.root
     -rw-r--r--. 1 gkrintir zh    830189 Nov 11 16:42 qcd_2.root
     -rw-r--r--. 1 gkrintir zh   1170835 Nov 11 16:42 qcd_1.root
     -rw-r--r--. 1 gkrintir zh    519815 Nov 11 16:41 qcd_0.root
     -rw-r--r--. 1 gkrintir zh  47356461 Nov 11 16:40 gjet_1.root
     -rw-r--r--. 1 gkrintir zh   3850290 Nov 11 16:37 gjet_0.root
   */

   addToStack(Form("%s/%s.root", folder.Data(),"dy"), "DYjet_13TeV_VBFTag_1mass", "Single_top", false, kRed, 21, kRed, *hs );
   addToLegend(Form("%s/%s.root", folder.Data(),"dy"), "DY", false, kRed, 21, kRed, "DYjet_13TeV_VBFTag_1mass", *leg);
   addToStack(Form("%s/%s.root", folder.Data(),"dipho"), "dipho_13TeV_VBFTag_1mass", "Single_top", false, kBlue, 21, kBlue, *hs );
   addToLegend(Form("%s/%s.root", folder.Data(),"dipho"), "Di#gammaJets", false, kBlue, 21, kBlue, "dipho_13TeV_VBFTag_1mass", *leg);
   addToStack(Form("%s/%s.root", folder.Data(),"gjet"), "gjet_13TeV_VBFTag_1mass", "Single_top", false, kYellow, 21, kYellow, *hs );
   //addToStack(Form("%s/%s.root", folder.Data(),"gjet_1"), "gjet_13TeV_VBFTag_1mass", "Single_top", false, kRed, 21, kRed, *hs );
   addToLegend(Form("%s/%s.root", folder.Data(),"gjet"), "#gammaJets", false, kYellow, 21, kYellow, "gjet_13TeV_VBFTag_1mass", *leg);
   
   addToStack(Form("%s/%s.root", folder.Data(),"qcd"), "qcd_13TeV_VBFTag_1mass", "Single_top", false, kGray, 21, kGray, *hs );
   addToLegend(Form("%s/%s.root", folder.Data(),"qcd"), "QCD", false, kGray, 21, kGray, "qcd_13TeV_VBFTag_1mass", *leg);

   //addToStack(Form("%s/%s.root", folder.Data(),"qcd_1"), "qcd_13TeV_VBFTag_1mass", "Single_top", false, kRed, 21, kRed, *hs );
   // addToStack(Form("%s/%s.root", folder.Data(),"qcd_2"), "qcd_13TeV_VBFTag_1mass", "Single_top", false, kRed, 21, kRed, *hs );

   //signal
   folder = "/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/MetaData/scripts/sig_jobs_1/";
   /*
     tth.root
     -rw-r--r--. 1 gkrintir zh 536861005 Nov 11 17:07 gg.root
     -rw-r--r--. 1 gkrintir zh 655314382 Nov 11 17:05 vbf.root
   */
   
   addToStack(Form("%s/%s.root", folder.Data(),"tth"), "tth_125_13TeV_VBFTag_1mass", "Single_top", false, kOrange, 21, kOrange, *hs );
   addToLegend(Form("%s/%s.root",folder.Data(),"tth"), "ttH", false, kOrange, 21, kOrange, "tth_125_13TeV_VBFTag_1mass", *leg);
   addToStack(Form("%s/%s.root", folder.Data(),"vbf"), "vbf_125_13TeV_VBFTag_1mass", "Single_top", false, kViolet, 21, kViolet, *hs );
   addToLegend(Form("%s/%s.root",folder.Data(),"vbf"), "VBF", false, kViolet, 21, kViolet, "vbf_125_13TeV_VBFTag_1mass", *leg);
   addToStack(Form("%s/%s.root", folder.Data(),"gg"), "ggh_125_13TeV_VBFTag_1mass", "Single_top", false, kGreen, 21, kGreen, *hs );
   addToLegend(Form("%s/%s.root",folder.Data(),"gg"), "gg", false, kGreen, 21, kGreen, "ggh_125_13TeV_VBFTag_1mass", *leg);

   hs->Draw("");
   hs_data->Draw("nostack,e1psame");
   leg->Draw();
}
