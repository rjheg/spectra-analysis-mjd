//
//  strangepeak.c
//  
//
//  Created by Ryan Hegedus on 6/5/18.
//

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TH1F.h"
#include "TRandom.h"
#include <vector>
#include "TSystem.h"
#include "TBenchmark.h"
#include "string.h"

void strangepeak() {
    int run = 0, iEvent = 0, mHL = 0;
    bool muVeto = false, isLNFill1 = false, isLNFill2 = false;
    vector<int>* P = new vector<int>(), *C = new vector<int>();
    vector<int>* D = new vector<int>(), *channel = new vector<int>();
    vector<unsigned int>* wfDCBits = new vector<unsigned int>;
    vector<bool>* isGood = new vector<bool>();
    vector<double>* trapENFCalC = new vector<double>();
    vector<double>* avse = new vector<double>(), *dcr99 = new vector<double>();
    vector<int>* detID = new vector<int>();
    vector<string> *detName = new vector<string>();
    
    int lowbin=5000.0, highbin = 8000.0;
    int numbins=3000/10;
    int line = 1, alpha = 0.7;
    
    
    //    #############################################################
    TChain* tree0 = new TChain("skimTree");
    tree0->Add("/Users/rjheg/Desktop/skimfiles_DS6/skim*.root");

    tree0->SetBranchAddress("run", &run);
    tree0->SetBranchAddress("iEvent", &iEvent);
    tree0->SetBranchAddress("mHL", &mHL);
    tree0->SetBranchAddress("P", &P);
    tree0->SetBranchAddress("C", &C);
    tree0->SetBranchAddress("D", &D);
    tree0->SetBranchAddress("channel", &channel);
    tree0->SetBranchAddress("wfDCBits", &wfDCBits);
    tree0->SetBranchAddress("muVeto", &muVeto);
    tree0->SetBranchAddress("isLNFill1", &isLNFill1);
    tree0->SetBranchAddress("isLNFill2", &isLNFill2);
    tree0->SetBranchAddress("isGood", &isGood);
    tree0->SetBranchAddress("trapENFCalC", &trapENFCalC);
    tree0->SetBranchAddress("avse", &avse);
    tree0->SetBranchAddress("dcr99", &dcr99);
    tree0->SetBranchAddress("detID", &detID);
    tree0->SetBranchAddress("detName", &detName);
    
    TCanvas* c0 = new TCanvas("c0", "", 0, 0, 1200, 800);
    TH1D *h = new TH1D("h", "trapENFCalC", numbins, lowbin, highbin);
    
    printf("-----------------------------------------------------------\n");
    printf("\t Information about the applied cut(s):\n");
    printf("-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------\n");
    
    for(int iev=0; iev<(int)tree0->GetEntries(); iev++){
        tree0->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
            
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                if (isGood->at(ich) == true) {
                    printf("iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Run Number: %i\n", run);
                    printf("Channel Number: %i\n", channel->at(ich));
                    printf("***********************************************************\n\n");
                    h->Fill(trapENFCalC->at(ich));
                }
            }
        }
    }
    
   

    h->GetXaxis()->SetTitle("Energy [KeV]");
    h->GetYaxis()->SetTitle("counts");
    h->SetLineStyle(line);
    h->SetLineColor(kBlue);
    h->SetFillColor(kBlue);
    h->SetFillStyle(3002);

    
    //    ################################################################
    
    TChain* tree1 = new TChain("skimTree");
    tree1->Add("/Users/rjheg/Desktop/skimfiles_DS1/skim*.root");
    
    
    tree1->SetBranchAddress("run", &run);
    tree1->SetBranchAddress("iEvent", &iEvent);
    tree1->SetBranchAddress("mHL", &mHL);
    tree1->SetBranchAddress("P", &P);
    tree1->SetBranchAddress("C", &C);
    tree1->SetBranchAddress("D", &D);
    tree1->SetBranchAddress("channel", &channel);
    tree1->SetBranchAddress("wfDCBits", &wfDCBits);
    tree1->SetBranchAddress("muVeto", &muVeto);
    tree1->SetBranchAddress("isLNFill1", &isLNFill1);
    tree1->SetBranchAddress("isLNFill2", &isLNFill2);
    tree1->SetBranchAddress("isGood", &isGood);
    tree1->SetBranchAddress("trapENFCalC", &trapENFCalC);
    tree1->SetBranchAddress("avse", &avse);
    tree1->SetBranchAddress("dcr99", &dcr99);
    tree1->SetBranchAddress("detID", &detID);
    tree1->SetBranchAddress("detName", &detName);
    
//    TCanvas* c1 = new TCanvas("c1", "");
    TH1D *h1 = new TH1D("h1", "trapENFCalC DS1", numbins, lowbin, highbin);
    
    for(int iev=0; iev<(int)tree1->GetEntries(); iev++){
        tree1->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
            
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                if (isGood->at(ich) == true){
                    printf("iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Run Number: %i\n", run);
                    printf("Channel Number: %i\n", channel->at(ich));
                    printf("***********************************************************\n\n");
                    h1->Fill(trapENFCalC->at(ich));
                }
            }
        }
    }
    
//    h1->GetXaxis()->SetTitle("Energy [KeV]");
//    h1->GetYaxis()->SetTitle("counts");
    
    h1->SetLineStyle(line);
    h1->SetLineColor(kRed+2);
    h1->SetFillColor(kRed+2);
    h1->SetFillStyle(3002);
    
//    h1->Draw();
    
    //    ##########################################################################
    TChain* tree2 = new TChain("skimTree");
    tree2->Add("/Users/rjheg/Desktop/skimfiles_DS2/skim*.root");
    
    
    tree2->SetBranchAddress("run", &run);
    tree2->SetBranchAddress("iEvent", &iEvent);
    tree2->SetBranchAddress("mHL", &mHL);
    tree2->SetBranchAddress("P", &P);
    tree2->SetBranchAddress("C", &C);
    tree2->SetBranchAddress("D", &D);
    tree2->SetBranchAddress("channel", &channel);
    tree2->SetBranchAddress("wfDCBits", &wfDCBits);
    tree2->SetBranchAddress("muVeto", &muVeto);
    tree2->SetBranchAddress("isLNFill1", &isLNFill1);
    tree2->SetBranchAddress("isLNFill2", &isLNFill2);
    tree2->SetBranchAddress("isGood", &isGood);
    tree2->SetBranchAddress("trapENFCalC", &trapENFCalC);
    tree2->SetBranchAddress("avse", &avse);
    tree2->SetBranchAddress("dcr99", &dcr99);
    tree2->SetBranchAddress("detID", &detID);
    tree2->SetBranchAddress("detName", &detName);
    
//    TCanvas* c2 = new TCanvas("c2", "");
    TH1D *h2 = new TH1D("h2", "trapENFCalC DS2", numbins, lowbin, highbin);
    
    for(int iev=0; iev<(int)tree2->GetEntries(); iev++){
        tree2->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
            
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                if (isGood->at(ich) == true){
                    printf("iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Run Number: %i\n", run);
                    printf("Channel Number: %i\n", channel->at(ich));
                    printf("***********************************************************\n\n");
                    h2->Fill(trapENFCalC->at(ich));
                }
            }
        }
    }
    
//    h2->GetXaxis()->SetTitle("Energy [KeV]");
//    h2->GetYaxis()->SetTitle("counts");

    h2->SetLineStyle(line);
    h2->SetLineColor(kGreen+3);
    h2->SetFillColor(kGreen+3);
    h2->SetFillStyle(3002);
//    h2->Draw();
    
    
    //    ##########################################################################
    TChain* tree3 = new TChain("skimTree");
    tree3->Add("/Users/rjheg/Desktop/skimfiles_DS3/skim*.root");
    
    
    tree3->SetBranchAddress("run", &run);
    tree3->SetBranchAddress("iEvent", &iEvent);
    tree3->SetBranchAddress("mHL", &mHL);
    tree3->SetBranchAddress("P", &P);
    tree3->SetBranchAddress("C", &C);
    tree3->SetBranchAddress("D", &D);
    tree3->SetBranchAddress("channel", &channel);
    tree3->SetBranchAddress("wfDCBits", &wfDCBits);
    tree3->SetBranchAddress("muVeto", &muVeto);
    tree3->SetBranchAddress("isLNFill1", &isLNFill1);
    tree3->SetBranchAddress("isLNFill2", &isLNFill2);
    tree3->SetBranchAddress("isGood", &isGood);
    tree3->SetBranchAddress("trapENFCalC", &trapENFCalC);
    tree3->SetBranchAddress("avse", &avse);
    tree3->SetBranchAddress("dcr99", &dcr99);
    tree3->SetBranchAddress("detID", &detID);
    tree3->SetBranchAddress("detName", &detName);
    
//    TCanvas* c3 = new TCanvas("c3", "");
    TH1D *h3 = new TH1D("h3", "trapENFCalC DS3", numbins, lowbin, highbin);
    
    for(int iev=0; iev<(int)tree3->GetEntries(); iev++){
        tree3->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
            
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                if (isGood->at(ich) == true){
                    printf("iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Run Number: %i\n", run);
                    printf("Channel Number: %i\n", channel->at(ich));
                    printf("***********************************************************\n\n");
                    h3->Fill(trapENFCalC->at(ich));
                }
            }
        }
    }
    
//    h3->GetXaxis()->SetTitle("Energy [KeV]");
//    h3->GetYaxis()->SetTitle("counts");
    h3->SetLineStyle(line);
    h3->SetLineColor(kBlack);
    h3->SetFillColor(kBlack);
    h3->SetFillStyle(3002);
//    h3->Draw();
    
    //    ##########################################################################
    TChain* tree4 = new TChain("skimTree");
    tree4->Add("/Users/rjheg/Desktop/skimfiles_DS4/skim*.root");
    
    
    tree4->SetBranchAddress("run", &run);
    tree4->SetBranchAddress("iEvent", &iEvent);
    tree4->SetBranchAddress("mHL", &mHL);
    tree4->SetBranchAddress("P", &P);
    tree4->SetBranchAddress("C", &C);
    tree4->SetBranchAddress("D", &D);
    tree4->SetBranchAddress("channel", &channel);
    tree4->SetBranchAddress("wfDCBits", &wfDCBits);
    tree4->SetBranchAddress("muVeto", &muVeto);
    tree4->SetBranchAddress("isLNFill1", &isLNFill1);
    tree4->SetBranchAddress("isLNFill2", &isLNFill2);
    tree4->SetBranchAddress("isGood", &isGood);
    tree4->SetBranchAddress("trapENFCalC", &trapENFCalC);
    tree4->SetBranchAddress("avse", &avse);
    tree4->SetBranchAddress("dcr99", &dcr99);
    tree4->SetBranchAddress("detID", &detID);
    tree4->SetBranchAddress("detName", &detName);
    
//    TCanvas* c4 = new TCanvas("c4", "");
    TH1D *h4 = new TH1D("h4", "trapENFCalC DS4", numbins, lowbin, highbin);
    
    for(int iev=0; iev<(int)tree4->GetEntries(); iev++){
        tree4->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
            
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                if (isGood->at(ich) == true){
                    printf("iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Run Number: %i\n", run);
                    printf("Channel Number: %i\n", channel->at(ich));
                    printf("***********************************************************\n\n");
                    h4->Fill(trapENFCalC->at(ich));
                }
            }
        }
    }
    
//    h4->GetXaxis()->SetTitle("Energy [KeV]");
//    h4->GetYaxis()->SetTitle("counts");
    h4->SetLineStyle(line);
    h4->SetLineColor(kViolet+2);
    h4->SetFillColor(kViolet+2);
    h4->SetFillStyle(3002);
//    h4->Draw();

    //    ##########################################################################
    TChain* tree5 = new TChain("skimTree");
    tree5->Add("/Users/rjheg/Desktop/skimfiles_DS5/skim*.root");
    
    
    tree5->SetBranchAddress("run", &run);
    tree5->SetBranchAddress("iEvent", &iEvent);
    tree5->SetBranchAddress("mHL", &mHL);
    tree5->SetBranchAddress("P", &P);
    tree5->SetBranchAddress("C", &C);
    tree5->SetBranchAddress("D", &D);
    tree5->SetBranchAddress("channel", &channel);
    tree5->SetBranchAddress("wfDCBits", &wfDCBits);
    tree5->SetBranchAddress("muVeto", &muVeto);
    tree5->SetBranchAddress("isLNFill1", &isLNFill1);
    tree5->SetBranchAddress("isLNFill2", &isLNFill2);
    tree5->SetBranchAddress("isGood", &isGood);
    tree5->SetBranchAddress("trapENFCalC", &trapENFCalC);
    tree5->SetBranchAddress("avse", &avse);
    tree5->SetBranchAddress("dcr99", &dcr99);
    tree5->SetBranchAddress("detID", &detID);
    tree5->SetBranchAddress("detName", &detName);
    
//    TCanvas* c5 = new TCanvas("c5", "");
    TH1D *h5 = new TH1D("h5", "trapENFCalC DS5", numbins, lowbin, highbin);
    
    for(int iev=0; iev<(int)tree5->GetEntries(); iev++){
        tree5->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
 
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                if (isGood->at(ich) == true){
                    printf("iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Run Number: %i\n", run);
                    printf("Channel Number: %i\n", channel->at(ich));
                    printf("***********************************************************\n\n");
                    h5->Fill(trapENFCalC->at(ich));
                }
            }
        }
    }

//    h5->GetXaxis()->SetTitle("Energy [KeV]");
//    h5->GetYaxis()->SetTitle("counts");
    

 
    h->Draw();
    h1->Draw("same");
    h2->Draw("same");
    h3->Draw("same");
    h4->Draw("same");
    h5->SetLineStyle(line);
    h5->SetLineColor(kOrange+7);
    h5->Draw("same");
    h5->SetFillColor(kOrange+7);
    c0->Update();
    TLegend* legend = new TLegend(0.45,0.8,0.6,0.5);
    legend->AddEntry(h1,"DS1","f");
    legend->AddEntry(h2,"DS2","f");
    legend->AddEntry(h3,"DS3","f");
    legend->AddEntry(h4,"DS4","f");
    legend->AddEntry(h5,"DS5","f");
    h5->SetFillStyle(3002);

    legend->AddEntry(h,"DS6","f");
    legend->SetBorderSize(4);
    legend->Draw();
    

    
}
