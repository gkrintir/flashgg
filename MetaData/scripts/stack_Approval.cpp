#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <sstream>
#include "TFile.h"
#include <fstream>
#include <string>

using namespace std;

TLegend * leg ;


Double_t elePtCut = 20;
Int_t nNjetsCut = 1;

ofstream fout;

/*
fh1NEvents
fh1NElectrons
std::string filename1 = "lessiso";
std::string filename2 = "moreiso";
std::string filename3 = "antiso";
*/

std::string filename1 = "3";//_JECv4_v150825";
std::string filename2 = "moreiso_JECv4_v150825";
std::string filename3 = "antiso_JECv4_v150825";

/*
std::string filename1 = "lessiso_JECv4_METnoHF_merged";
std::string filename2 = "moreiso_JECv4_METnoHF_merged";
std::string filename3 = "antiso_JECv4_METnoHF_merged";
*/

double counter = 0;

void stack_Approval(const TString& variable, const TString& dilepton, const Int_t nBinsX, const Float_t binXLow, const Float_t binXUp, const TString& iso) {
   // Example of stacked histograms: class THStack
   //
   //  Author: Rene Brun

   gStyle->SetOptStat(0);

   leg = new TLegend(0.6129032,0.5035989,0.7983871,0.9156118,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.0446761);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   
   TString folder = "/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/MetaData/scripts/data_jobs_1/";
   THStack *hs_data = new THStack("hs_data","Signal Region");
   
   addToStack(Form("%s/%s.root", folder.Data(),"all"), "__mtw_array", "Single_top", true, kBlack, 21, kBlack, *hs_data );

   /*
   for (int i=1; i<26; i++){ //TTbar:10, DY:26, tW_top: 8, tW_antitop: 10, WW: 7, WZ:5. WJEts:31, Photons1: 31
     //if (i==27)continue;
     addToStack(Form("%s/%s_%d.root", folder.Data(),"AnaResults", i), variable.Data(), dilepton, "Single_top", true, nBinsX, binXLow, binXUp, kBlack, 21, kBlack, *hs_data );
     //addToStack(Form("%s/%s_%d.root", folder.Data(),"AnaResults", i), "fNEvents","Single_top", true, kBlack, 21, kBlack, *hs_data );
   }
   */
   //addToStack(Form("%s/%s_%s.root", folder.Data(),"AnaResults", filename1.data()), "fh1NEvents", "Single_op", true, kBlack, 21, kBlack, *hs_data );

   //addToLegend(Form("%s/%s_%s.root", folder.Data(),"AnaResults", filename1.data()), "Data", true, kBlack, 21, kBlack); 
   

   const TString folder = "/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/MetaData/scripts/bkg_jobs_1/";
   THStack *hs = new THStack("hs","");
   //create three 1-d histograms
   

   addToStack(Form("%s/%s.root", folder.Data(),"dy"), "__mtw_array", "Single_top", false, kRed, 21, kRed, *hs );
   /*
   addToStack(Form("%s/%s_%s.root", folder.Data(),"top", iso.Data()), "__mtw_array", "Single_top", false, kOrange - 3, 21, kOrange - 3, *hs );
   addToStack(Form("%s/%s_%s.root", folder.Data(),"EW", iso.Data()),"__mtw_array", "DY", false, kGreen -2, 22, kGreen -2, *hs);

   addToStack(Form("%s/%s_%s.root", folder.Data(),"QCDTemplate", "antiso_SR"),"__mtw_array", "QCD", false, kGray, 21, kGray, *hs );



   addToLegend(Form("%s/%s_%s.root", folder.Data(),"QCD", iso.Data()), "QCD", false, kGray, 21, kGray);
   addToLegend(Form("%s/%s_%s.root", folder.Data(),"EW", iso.Data()), "W/Z+jets", false, kGreen -2, 22, kGreen -2);
   addToLegend(Form("%s/%s_%s.root", folder.Data(),"top", iso.Data()), "t#bar{t}, tW", false, kOrange - 3, 21, kOrange - 3);
   addToLegend(Form("%s/%s_%s.root", folder.Data(),"tchannel", iso.Data()), "#it{t}-channel", false, kRed, 21, kRed);

   */
   /*
   TCanvas *cst = new TCanvas("cst","stacked hists",10,10,700,700);
   //cst->SetFillColor(41);
   //cst->Divide(2,2);
   // in top left pad, draw the stack with defaults
   cst->cd();
   
        
   //TPad *pad1 = new TPad("pad1", "pad1",0,0.15,1,1);
     TPad *pad1 = new TPad("pad1", "pad1",0,0.0,1,1);
     pad1->Draw();
     pad1->cd();
     pad1->Range(-0.9756097,-809.2457,5.121951,5415.875);
     pad1->SetFillColor(0);
     pad1->SetBorderMode(0);
     pad1->SetBorderSize(2);
     pad1->SetTickx(1);
     pad1->SetTicky(1);
     pad1->SetLeftMargin(0.16);
     pad1->SetRightMargin(0.05);
     pad1->SetTopMargin(0.055);
     pad1->SetBottomMargin(0.13);
     pad1->SetFrameFillStyle(0);
     pad1->SetFrameBorderMode(0);
     pad1->SetFrameFillStyle(0);
     pad1->SetFrameBorderMode(0);
   */
    
     //hs->Draw("");
    //hs->SetMinimum(0);

     hs_data->Draw("nostack,e1p");
   //hs_data->GetStack()->Last()->Draw("e1p");

   //hs_data->GetStack()->Last()->SaveAs(Form("%s_%s.root", variable.Data(), dilepton.Data()));

    //hs->GetXaxis()->SetTitle("#slash{E}_{T} (GeV)");
     /*
    hs_data->GetStack()->Last()->GetXaxis()->SetTitle("m_{T}^{W} (GeV)");
    hs_data->GetStack()->Last()->GetXaxis()->SetLabelFont(42);
    hs_data->GetStack()->Last()->GetXaxis()->SetLabelOffset(0.007);
    hs_data->GetStack()->Last()->GetXaxis()->SetLabelSize(0.045);
    hs_data->GetStack()->Last()->GetXaxis()->SetTitleSize(0.06);
    hs_data->GetStack()->Last()->GetXaxis()->SetTitleOffset(0.95);
    hs_data->GetStack()->Last()->GetXaxis()->SetTitleFont(42);
    hs_data->GetStack()->Last()->GetYaxis()->SetTitle("Events / 10 GeV");
    hs_data->GetStack()->Last()->GetYaxis()->SetLabelFont(42);
    hs_data->GetStack()->Last()->GetYaxis()->SetLabelSize(0.045);
    hs_data->GetStack()->Last()->GetYaxis()->SetTitleSize(0.06);
    //hs_data->GetStack()->Last()->GetYaxis()->SetTitleOffset(1.45);
    hs_data->GetStack()->Last()->GetYaxis()->SetTitleFont(42);
     */
    //hs_data->GetStack()->Last()->SetMaximum(4700);
    TText T; T.SetTextFont(42); T.SetTextAlign(21); T.SetTextSize(0.09);
    //T.DrawTextNDC(.6,.9,"Rel.Isolation < 0.06");

    // leg->Draw();


    TLatex *   tex = new TLatex(0.955,0.955,"13 pb^{-1}(5 TeV)");
    tex->SetNDC();
    tex->SetTextAlign(31);
    tex->SetTextFont(42);
    tex->SetTextSize(0.048);
    tex->SetLineWidth(2);
    //tex->Draw();
    //TLatex *   tex = new TLatex(0.31,0.955,"2-jet 1-tag (SR)"); //rectangula, pads2
    //TLatex *   tex = new TLatex(0.38,0.955,"2-jet 1-tag (inclusive)");//rectangula, pads2

    //TLatex *   tex = new TLatex(0.35,0.955,"2-jet 1-tag (SR)"); //rectangula, pads1
    
    //TLatex *   tex = new TLatex(0.46,0.955,"2-jet 1-tag (SR)"); //square, pad1
    tex->SetNDC();
    tex->SetTextAlign(31);
    tex->SetTextFont(42);
    tex->SetTextSize(0.048);
    tex->SetLineWidth(2);
    //tex->Draw();
    
    //tex = new TLatex(0.26,0.8312.434,"CMS");
    tex = new TLatex(0.33,0.8312.434,"CMS");
    tex->SetNDC();
    tex->SetTextAlign(31);
    tex->SetTextSize(0.05956813);
    tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(0.29,0.78,"Preliminary"); //rectangular, pads2
    tex = new TLatex(0.29,0.78,"Preliminary"); //rectangular, pads2

    tex = new TLatex(0.42,0.78,"Preliminary"); //square, pad1x
    tex->SetNDC();
    tex->SetTextAlign(31);
    tex->SetTextFont(52);
    tex->SetTextSize(0.048);
    tex->SetLineWidth(2);
    //tex->Draw();

    tex = new TLatex(0.8,0.38,"#it{I}_{rel} < 0.15");
    tex->SetNDC();
    tex->SetTextAlign(31);
    //tex->SetTextFont(52);
    tex->SetTextSize(0.048);
    tex->SetLineWidth(2);
    //tex->Draw();
    
    //pad1->Update();

    //cst->cd();
    /*
    TPad *pad2 = new TPad("pad2", "pad1",0,0,1,0.15);
    //pad2->Draw();
    //pad2->cd();
    pad2->Range(-0.9756097,-0.3170732,5.121951,2.121951);
    pad2->SetFillColor(0);
    pad2->SetBorderMode(0);
    pad2->SetBorderSize(2);
    //pad2->SetGridy();
    pad2->SetTickx(1);
    pad2->SetTicky(1);
    pad2->SetLeftMargin(0.16);
    pad2->SetRightMargin(0.02);
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.13);
    pad2->SetFrameFillStyle(0);
    pad2->SetFrameBorderMode(0);
    pad2->SetFrameFillStyle(0);
    pad2->SetFrameBorderMode(0);
    */
    //ratio = ratio_DataOverMC(*hs, *hs_data);

    //gr1 = uncertainty_band(*hs, *ratio);
    /*
    gr1->GetYaxis()->SetTitle("Data/MC");
    gr1->SetFillStyle(3018);
    gr1->SetDirectory(0);
    gr1->SetStats(0);
    gr1->SetFillColor(1);
    gr1->SetLineColor(kBlack);   
    gr1->SetMarkerStyle(20);
    gr1->GetXaxis()->SetLabelFont(42);
    gr1->GetXaxis()->SetLabelSize(0.0000005);
    gr1->GetXaxis()->SetTitleSize(0.09);
    gr1->GetXaxis()->SetTitleFont(42);
    gr1->GetYaxis()->SetLabelFont(42);
    gr1->GetYaxis()->SetLabelSize(0.1);
    gr1->GetYaxis()->SetNdivisions(505);
    gr1->GetYaxis()->SetTitleSize(0.25);
    gr1->GetYaxis()->SetTitleFont(42);
    gr1->GetYaxis()->SetTitleOffset(0.2);

    //gr1->Draw(" e2");
    //ratio->Draw("same");

    // pad2->Update();
    TLine *l;
    l = new TLine(pad2->GetUxmin(),1.3,pad2->GetUxmax(),1.3);
    l->SetLineColor(kBlue);
    l->SetLineStyle(2);
    l->SetLineWidth(2);
    //l->Draw();
    l = new TLine(pad2->GetUxmin(),0.7,pad2->GetUxmax(),0.7);
    l->SetLineColor(kBlue);
    l->SetLineStyle(2);
    l->SetLineWidth(2);
    // l->Draw();
    */

    //cst->SaveAs(Form("%s_%s.root", variable.Data(), dilepton.Data()));
    //fout.close();
    std::cout<< counter << std::endl;
    }

void addToLegend(const TString& filename, const TString& legentry, Bool_t sumw2, const EColor& fillcolor, Int_t MarkerStyle,  const EColor& MarkerColor) {
  
   TFile *f = new TFile(Form("%s",filename.Data()), "R");
   TH1F * pt_muon = dynamic_cast<TH1F*>(f->Get("__mtw_array"));
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
     leg->AddEntry(pt_muon,Form("%s",legentry.Data()),"p");
   }
   else
     leg->AddEntry(pt_muon,Form("%s",legentry.Data()),"f");
      
     
}

void addToStack(const TString& filename, const TString& variable,  const TString& legentry, Bool_t sumw2, const EColor& fillcolor, Int_t MarkerStyle,  const EColor& MarkerColor, THStack& hs) {
  
   TFile *f = new TFile(Form("%s",filename.Data()), "R");
   //f->ls();
   
   TDirectoryFile * tagsDumper = (TDirectoryFile*)f->Get("tagsDumper");
   TDirectoryFile* histograms = (TDirectoryFile*)tagsDumper->Get("histograms");

   TH1F* pt_muon = (TH1F*)histograms->Get("Data_13TeV_UntaggedTag_0mass");
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
   
   hs.Add(pt_muon, "hist");

   
}

void addToStack(const TString& filename, const TString& variable, const TString& dilepton, const TString& legentry, Bool_t sumw2, Int_t nbins, Float_t binXLow, Float_t binXUp,
		const EColor& fillcolor, Int_t MarkerStyle, const EColor& MarkerColor, THStack& hs) {
  
  TFile *f = new TFile(Form("%s",filename.Data()), "R");
  //f->ls();

  TDirectoryFile * tagsDumper = (TDirectoryFile*)f->Get("tagsDumper");
  TDirectoryFile* histograms = (TDirectoryFile*)tagsDumper->Get("histograms");

  TH1F* pt_muon = (TH1F*)histograms->Get("Data_13TeV_UntaggedTag_0mass");

    /*
   TTree * anaTtbarEMuInfo = dynamic_cast<TTree*>(anaPFvsCaloJet->FindObject("anaTtbarDileptonInfo"));
   TBranch * bla; 
   
   std::vector<double> *px=0;  std::vector<double> *weight=0;

   std::vector<int> *ndilep=0; std::vector<int> *dilepsign=0; std::vector<double> *dilepmass=0;  std::vector<double> *dilepPt=0;

   std::vector<double> *njets=0; 

   std::vector<double> *eleeta=0; std::vector<double> *elept=0;

   std::vector<double> *muoniso=0;  std::vector<double> *muonpt=0; std::vector<double> *muoneta=0; std::vector<double> *jetpt=0;  std::vector<double> *jeteta=0; 

   std::vector<int> *evntnumber=0; std::vector<double> *runnumber=0; 

   anaTtbarEMuInfo->SetBranchStatus("fEventWeight",1);
   anaTtbarEMuInfo->SetBranchAddress("fEventWeight", &weight);

   anaTtbarEMuInfo->SetBranchStatus("fEventNumber",1);
   anaTtbarEMuInfo->SetBranchAddress("fEventNumber", &evntnumber);

   anaTtbarEMuInfo->SetBranchStatus("fEventRunNumber",1);
   anaTtbarEMuInfo->SetBranchAddress("fEventRunNumber", &runnumber);
				     
   anaTtbarEMuInfo->SetBranchStatus("fEventWeight",1);
   anaTtbarEMuInfo->SetBranchAddress("fEventWeight", &weight);

   //int px[2000000];
   anaTtbarEMuInfo->SetBranchStatus(Form("%s",variable.Data()),1);
   anaTtbarEMuInfo->SetBranchAddress(Form("%s",variable.Data()), &px);
   
   if (!variable.EqualTo("fNDileptons")){
     anaTtbarEMuInfo->SetBranchStatus("fNDileptons", 1);
     anaTtbarEMuInfo->SetBranchAddress("fNDileptons", &ndilep);
   }
   if (!variable.EqualTo("fSignDilepton")){
     anaTtbarEMuInfo->SetBranchStatus("fSignDilepton", 1);
     anaTtbarEMuInfo->SetBranchAddress("fSignDilepton", &dilepsign);
   }
   if (!variable.EqualTo("fMassDilepton")){
     anaTtbarEMuInfo->SetBranchStatus("fMassDilepton", 1);
     anaTtbarEMuInfo->SetBranchAddress("fMassDilepton", &dilepmass);
   }
   if (!variable.EqualTo("fPtDilepton")){
     anaTtbarEMuInfo->SetBranchStatus("fPtDilepton", 1);
     anaTtbarEMuInfo->SetBranchAddress("fPtDilepton", &dilepPt);
   }
    
   if (!variable.EqualTo("fNJetsIncl")){
     anaTtbarEMuInfo->SetBranchStatus("fNJetsIncl", 1);
     anaTtbarEMuInfo->SetBranchAddress("fNJetsIncl", &njets);
   }

   if (!variable.EqualTo("fElePtLead")){
     anaTtbarEMuInfo->SetBranchStatus("fElePtLead", 1);
     anaTtbarEMuInfo->SetBranchAddress("fElePtLead", &elept);
   }

   if (!variable.EqualTo("fEleEtaLead")){
     anaTtbarEMuInfo->SetBranchStatus("fEleEtaLead", 1);
     anaTtbarEMuInfo->SetBranchAddress("fEleEtaLead", &eleeta);
   }

   if (!variable.EqualTo("fMuonIsoSublead")){
     anaTtbarEMuInfo->SetBranchStatus("fMuonIsoSublead", 1);
     anaTtbarEMuInfo->SetBranchAddress("fMuonIsoSublead", &muoniso);
   }

    if (!variable.EqualTo("fMuonPtSublead")){
     anaTtbarEMuInfo->SetBranchStatus("fMuonPtSublead", 1);
     anaTtbarEMuInfo->SetBranchAddress("fMuonPtSublead", &muonpt);
   }

    if (!variable.EqualTo("fMuonEtaSublead")){
     anaTtbarEMuInfo->SetBranchStatus("fMuonEtaSublead", 1);
     anaTtbarEMuInfo->SetBranchAddress("fMuonEtaSublead", &muoneta);
   }

    
    //if (!variable.EqualTo("fLeadJetPt")){
    // anaTtbarEMuInfo->SetBranchStatus("fLeadJetPt", 1);
    // anaTtbarEMuInfo->SetBranchAddress("fLeadJetPt", &jetpt);
    // }

   if (!variable.EqualTo("fLeadJetEta")){
     anaTtbarEMuInfo->SetBranchStatus("fLeadJetEta", 1);
     anaTtbarEMuInfo->SetBranchAddress("fLeadJetEta", &jeteta);
   }
   

   TH1F * pt_muon = new TH1F(Form("%s",variable.Data()), Form("%s",variable.Data()), nbins, binXLow, binXUp);
   
   //ofstream fout;
   //fout.open( "events_2jets.csv" );

   Long64_t nentries = anaTtbarEMuInfo->GetEntries();
   for (Long64_t i=0;i< nentries;i++) {
     anaTtbarEMuInfo->GetEntry(i);
     for (int j = 0; j < px->size(); ++j) {
	 //std::cout<<i<< "!!!!! "<<std::endl; 
       //if ((*ndilep)[j]>=1 )//&& (*dilepsign)[j]<1 && (*elept)[j]> elePtCut )
       //if ( (*evntnumber)[j]==170877) std::cout<< " "<< (*dilepmass)[j] << " "<< (*muoniso)[j] <<std::endl;
       if ((*ndilep)[j]>=1 && (*dilepsign)[j]<1 && (*dilepmass)[j]>20 ) {// && (*njets)[j]>1 && (*muoniso)[j]<0.15 ){// && (*njets)[j]>nNjetsCut ) {
       //if ((*ndilep)[j]>=1 && (*dilepsign)[j]<1 && (*dilepmass)[j]>20 && (*muoniso)[j]<0.15){// && (*njets)[j]>nNjetsCut && (*elept)[j]> elePtCut ) {
	 //if((*dilepmass)[k]<80 || (*dilepmass)[k]>100)
	 //if( abs((*eleeta)[j]<2.5) && abs((*eleeta)[j]>1.479))
	 //if((*eleeta)[j]>50)
	 //if ((*weight)[j]<1)
	 //   pt_muon->Fill((*px)[j], -1);
         //else
	 // pt_muon->Fill((*px)[j], +1);
	 pt_muon->Fill((*px)[j], (*weight)[j]);
	 //fout <<  (*evntnumber)[j] << " "<< (*weight)[j] << endl;
	 counter+=(*weight)[j];
	 fout <<  (*evntnumber)[j] << " , "<< (*dilepmass)[j] << endl;//" "<< (*weight)[j] << endl;
	 //if (((*runnumber)[j]==262252 && (*px)[j]==170) || (*runnumber)[j]==262235 && (*px)[j]==138)
	 //std::cout<< " ! "<<  (*runnumber)[j]<< " "<<  (*evntnumber)[j] << " "<< (*px)[j] << " "<< (*ndilep)[j] << " "<< (*dilepsign)[j] << " "<< (*dilepmass)[j] << " "<< (*njets)[j] << " "<< (*elept)[j] << " "<< (*eleeta)[j] << " "<< (*muoniso)[j] << " "<< (*muonpt)[j]<< " "<< (*muoneta)[j] << " "<< (*jetpt)[j]<< " "<<  (*jeteta)[j] <<std::endl;
	 //std::cout.precision(5);
	 //std::cout<<  (*evntnumber)[j]<< std::endl;
       //printf("%.7f\n", (*evntnumber)[j]);
       }
     }
   }
   //anaTtbarEMuInfo->Draw(Form("%s>>pt_muon",variable.Data()));
   */
   if (sumw2){
     pt_muon->Sumw2();
     pt_muon->SetMarkerStyle(20);
   }
   else {
     pt_muon->SetFillColor(fillcolor);
     pt_muon->SetMarkerStyle(MarkerStyle);
     pt_muon->SetMarkerColor(MarkerColor);
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
   

   
   //   if (variable.EqualTo("mtw") || variable.EqualTo("met") )
   //pt_muon->Rebin(5);
   //if (variable.Contains("eta") )
   // pt_muon->Rebin(2);

   //if (!sumw2 && !filename.Contains("QCD")) {
   //  pt_muon->Scale(2100.);
   //}
   //else{
   //pt_muon->Scale(1.);
   //}
   /*
   if(filename2.find("JECv4") != std::string::npos ){
      if (filename.Contains("QCD") && filename.Contains("lessiso")){
       std::cout<<"JEC !!!!!!!!!!!!!!!!!!!!!!!!" <<filename.Data()<<std::endl;
       pt_muon->Scale(0.45); //0.416 full, 0.448/0.2 sr 0.338/0.181 sb
      }
      else if (filename.Contains("MuEnrichedPt15") && filename.Contains("antiso")){
	pt_muon->Scale(0.00385); 
	std::cout<<"JEC !!!!!!!!!!!!!!!!!!!!!!!!" <<filename.Data()<<std::endl;
      }
      else if (!filename.Contains("MuEnrichedPt15") && !filename.Contains("data") && filename.Contains("lessiso"))
	pt_muon->Scale(0.98);  //0.988 full+sr
      else if (filename.Contains("MuEnrichedPt15") && filename.Contains("moreiso")){
	pt_muon->Scale(0.3); 
      }
      else if (!filename.Contains("MuEnrichedPt15") && !filename.Contains("data") && filename.Contains("moreiso")){
	std::cout<<" !!!!!!!!!!!!!!!!!!!!!! "<< filename.Data()<<std::endl;
	pt_muon->Scale(1.);
      }
   }
   else if (filename2.find("JECv4_METnoHF") != std::string::npos ){
     if (filename.Contains("MuEnrichedPt15") && filename.Contains("lessiso")){
       std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!" <<filename.Data()<<std::endl;
       pt_muon->Scale(0.448); //0.416 fill
     }
     else if (filename.Contains("MuEnrichedPt15") && filename.Contains("antiso")){
       std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!" <<filename.Data()<<std::endl;
	pt_muon->Scale(0.35);
     }
      else if (!filename.Contains("MuEnrichedPt15") && !filename.Contains("data") && filename.Contains("lessiso"))
	pt_muon->Scale(0.985); //0.955 full 
      else if (filename.Contains("MuEnrichedPt15") && filename.Contains("moreiso")){
	pt_muon->Scale(0.340); 
      }
      else if (!filename.Contains("MuEnrichedPt15") && !filename.Contains("data") && filename.Contains("moreiso")){
	std::cout<<" !!!!!!!!!!!!!!!!!!!!!! "<< filename.Data()<<std::endl;
	pt_muon->Scale(0.85);
      }
   }
   else{
     if (filename.Contains("QCD") && filename.Contains("lessiso")){
       pt_muon->Scale(0.03); 
     }
     else if (filename.Contains("MuEnrichedPt15") && filename.Contains("antiso")){
       std::cout<<"else !!!!!!!!!!!!!!!!!!!!!!!!" <<filename.Data()<<std::endl;
       pt_muon->Scale(0.035);
     }
     else if (!filename.Contains("MuEnrichedPt15") && !filename.Contains("data") && filename.Contains("lessiso"))
       pt_muon->Scale(0.95); 
     else if (filename.Contains("MuEnrichedPt15") && filename.Contains("moreiso")){
       pt_muon->Scale(0.13); 
     }
     else if (!filename.Contains("MuEnrichedPt15") && !filename.Contains("data") && filename.Contains("moreiso")){
       std::cout<<" !!!!!!!!!!!!!!!!!!!!!! "<< filename.Data()<<std::endl;
       pt_muon->Scale(0.78);
     }
   }
   */
   hs.Add(pt_muon, "hist");
   //fout.close();
}

TH1F* ratio_DataOverMC(THStack& hs_MC, THStack& hs_data){
  TList *fQAList = dynamic_cast<TList*>(hs_MC.GetHists());
  fQAList->SetName(hs_MC.GetName());
  fQAList->SetOwner();
  fQAList->ls();

  TH1F* QCD = dynamic_cast<TH1F*>(fQAList->Last())->Clone();
  //cout<<" entries !!!!!!!!!!!!!!!!!!!!!!!!!!!!! "<<QCD->GetName()<<endl;
  QCD->Sumw2();
  for (int i=0; i<fQAList->GetSize()-1; i++){
    TH1F* nonQCD = dynamic_cast<TH1F*>(fQAList->At(i));
    //cout<<" entries !!!!!!!!!!!!!!!!!!!!!!!!!!!!! "<<nonQCD->GetName()<<endl;
    nonQCD->Sumw2();
    QCD->Add(nonQCD);
  }

  TH1F *data = dynamic_cast<TH1F*>(hs_data.GetHists()->Last())->Clone();
  data->Sumw2();
  data->GetEntries();
  
  // Disable errors on the denominator (they should be handled in an
  // uncertainty band around unity)
  for (int i=1; i<=QCD->GetSize()-1; i++)
    QCD->SetBinError(i, 0.0);
  // Divide by the denominator
  data->Divide(QCD);

  
  return data;
}

TH1F* uncertainty_band(THStack& hs_MC, TH1F& ratio) {

  //https://github.com/havoc-io/owls-hep/blob/master/owls_hep/estimation.py
  TList *fQAList = dynamic_cast<TList*>(hs_MC.GetHists());
  fQAList->SetName(hs_MC.GetName());
  fQAList->SetOwner();
  fQAList->ls();

  TH1F* QCD = dynamic_cast<TH1F*>(fQAList->Last())->Clone();
  //cout<<" entries !!!!!!!!!!!!!!!!!!!!!!!!!!!!! "<<QCD->GetName()<<endl;
  QCD->Sumw2();
  for (int i=0; i<fQAList->GetSize()-1; i++){
    TH1F* nonQCD = dynamic_cast<TH1F*>(fQAList->At(i));
    //cout<<" entries !!!!!!!!!!!!!!!!!!!!!!!!!!!!! "<<nonQCD->GetName()<<endl;
    nonQCD->Sumw2();
    QCD->Add(nonQCD);
  }


  Int_t f1(QCD->GetNbinsX()); 
  const Int_t nbins =  f1;
  double x[nbins], cent_val[nbins], x_unc[nbins], up_unc[nbins], down_unc[nbins];
		   
  // Loop over all bins
  // NOTE: We don't handle overflow because TGraphAsymmErrors doesn't have a
  // notion of overflow bins
  
  for (int i=0; i<nbins; i++)
    {
      // Set the band nominal point to center around Y = 1.0
      x[i] = QCD->GetBinCenter(i+1);
      // Extract the bin content
      cent_val[i] = ratio->GetBinContent(i+1);
      //If the bin content is 0, then the uncertainty is 0
      if (cent_val[i] == 0.0) {
	up_unc[i] = 0.0;
	down_unc[i] = 0.0;
      }
      else{
	up_unc[i] = QCD->GetBinError(i+1) / QCD->GetBinContent(i+1);
	up_unc[i] = QCD->GetBinError(i+1) / QCD->GetBinContent(i+1);
	x_unc[i] = 0.5;
      }
    }
  
  gr = new TGraphAsymmErrors(nbins,x,cent_val,x_unc,x_unc,up_unc,down_unc);
  
  TH1F * hist = new TH1F("","", nbins, QCD->GetBinLowEdge(1), QCD->GetBinLowEdge(QCD->GetNbinsX()+1));
  for (int i=1; i<=nbins; i++)
    {
      // Extract the bin content
      hist->SetBinContent(i, cent_val[i-1]);
      //If the bin content is 0, then the uncertainty is 0
      if (cent_val[i-1] == 0.0) {
	hist->SetBinError(i, 0.0);
      }
      else{
	hist->SetBinError(i, up_unc[i-1]);
      }
    }
  cout<<"whoooooooooooooooooooooooooooooooooooola"<<QCD->GetBinLowEdge(1)<<endl;
  return hist;
}


/*//Old colour coding for MC samples
   addToStack(Form("%s/%s_%s.root", folder.Data(),"ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1", iso.Data()), "met", "Single_top", false, kMagenta, 21, kMagenta, *hs );
   addToStack(Form("%s/%s_%s.root", folder.Data(),"tW-channel", iso.Data()), "met", "Single_top", false, kMagenta+2, 21, kMagenta+2, *hs );
   //addToStack(Form("%s/%s_%s.root", folder.Data(),"s-channel", iso.Data()), "met", "Single_top", false, kMagenta+3, 21, kMagenta+3, *hs );
   addToStack(Form("%s/%s_%s.root", folder.Data(),"TT_TuneCUETP8M1_13TeV-powheg-pythia8", iso.Data()), "met", "t#bar{t}", false, kRed+1, 21, kRed+1, *hs );
   addToStack(Form("%s/%s_%s.root", folder.Data(),"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", iso.Data()), "met", "WJets", false, kGreen-3, 20, kGreen-3, *hs );
   addToStack(Form("%s/%s_%s.root", folder.Data(),"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", iso.Data()),"met", "DY", false, kMagenta+2, 22, kMagenta+2, *hs);
   addToStack(Form("%s/%s_%s.root", folder.Data(),"QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8_20toInf", iso.Data()),"met", "QCD", false, kYellow, 21, kYellow, *hs );
   */
