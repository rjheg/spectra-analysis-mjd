//
//  strangepeak2.c
//  
//
//  Created by Ryan Hegedus on 6/8/18.
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

void strangepeak2() {
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
    double clockTime_s = 0.0;
    
    int lowbin=6800.0, highbin = 7000.0;
    int numbins=3000/10;
    int line = 1;
    
    
    //    #############################################################
    TChain* tree0 = new TChain("skimTree");
    tree0->Add("/Users/rjheg/Desktop/skimfiles_DS1/skim*.root");
    tree0->Add("/Users/rjheg/Desktop/skimfiles_DS2/skim*.root");
    tree0->Add("/Users/rjheg/Desktop/skimfiles_DS3/skim*.root");
    tree0->Add("/Users/rjheg/Desktop/skimfiles_DS4/skim*.root");
    tree0->Add("/Users/rjheg/Desktop/skimfiles_DS5/skim*.root");
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
    tree0->SetBranchAddress("clockTime_s", &clockTime_s);
    
    TCanvas* c0 = new TCanvas("c0", "", 0, 0, 1200, 800);
    TH1D *h = new TH1D("h", "trapENFCalC", numbins, lowbin, highbin);
    
    printf("-----------------------------------------------------------\n");
    printf("\t Information about the applied cut(s):\n");
    printf("-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------\n");
    
    for(int iev=0; iev<(int)tree0->GetEntries(); iev++){
        tree0->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
//            h->Fill(trapENFCalC->at(ich));
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                if ( /*(muVeto == true) && */(isGood->at(ich) == true) /*&&(dcr99->at(ich) < 0) && (avse->at(ich) > -1)*/){
                    printf("\n\n iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Energy: %f keV\n", trapENFCalC->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Time of event (GRETINA): %f seconds\n", clockTime_s);
                    printf("Run Number: %i\n", run);
//                    printf("Channel Number: %i\n", channel->at(ich));
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
    
    h->Draw();
    c0->Update();
    /*
    TLegend* legend = new TLegend(0.45,0.8,0.6,0.5);
    legend->AddEntry(h,"DS1-6","f");
    legend->SetBorderSize(4);
    legend->Draw(); */
    
    
    
}
