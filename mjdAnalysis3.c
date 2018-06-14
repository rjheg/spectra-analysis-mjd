//
//  mjdAnalysis3.c
//  
//
//  Created by Ryan Hegedus on 5/24/18.
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

void mjdAnalysis3() {
    TChain* tree = new TChain("skimTree");
    
    tree->Add("/Users/rjheg/Desktop/skimfiles_DS6/skim*.root");
    
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
    tree->SetBranchAddress("run", &run);
    tree->SetBranchAddress("iEvent", &iEvent);
    tree->SetBranchAddress("mHL", &mHL);
    tree->SetBranchAddress("P", &P);
    tree->SetBranchAddress("C", &C);
    tree->SetBranchAddress("D", &D);
    tree->SetBranchAddress("channel", &channel);
    tree->SetBranchAddress("wfDCBits", &wfDCBits);
    tree->SetBranchAddress("muVeto", &muVeto);
    tree->SetBranchAddress("isLNFill1", &isLNFill1);
    tree->SetBranchAddress("isLNFill2", &isLNFill2);
    tree->SetBranchAddress("isGood", &isGood);
    tree->SetBranchAddress("trapENFCalC", &trapENFCalC);
    tree->SetBranchAddress("avse", &avse);
    tree->SetBranchAddress("dcr99", &dcr99);
    tree->SetBranchAddress("detID", &detID);
    tree->SetBranchAddress("detName", &detName);
    
    int lowbin=5000.0, highbin = 8000.0;
    int numbins=3000/10;
    
    TH1D *h = new TH1D("h", "trapENFCalC", numbins, lowbin, highbin);
    TH1D *h2 = new TH1D("h2", "trapENFCalC", numbins, lowbin, highbin);
    
    for(int iev=0; iev<(int)tree->GetEntries(); iev++){
        tree->GetEvent(iev);
        for(int ich=0; ich<(int)C->size(); ich++){
            h->Fill(trapENFCalC->at(ich));
        }
    }

    printf("-----------------------------------------------------------\n");
    printf("\t Information about the applied cut(s):\n");
    printf("-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------\n");
    
    tree->Add("/Users/rjheg/Desktop/skimfiles_DS1/skim*.root");
    for(int iev=0; iev<(int)tree->GetEntries(); iev++){
        tree->GetEvent(iev);
        
        for(int ich=0; ich<(int)C->size(); ich++){
            h2->Fill(trapENFCalC->at(ich));
            if(trapENFCalC->at(ich) >= lowbin && trapENFCalC->at(ich) < highbin) {
                
                if (muVeto){
                    printf("iev: %i \t ich: %i\n", iev, ich);
                    printf("***********************************************************\n");
                    printf("Cryostat \t String Position \t Detector Position \n    %i\t\t\t%i\t\t\t%i\n\n", C->at(ich), P->at(ich), D->at(ich));
                    printf("Detector ID: %i\n", detID->at(ich));
                    printf("Detector Name: %s\n", detName->data());
                    printf("Run Number: %i\n", run);
                    printf("Channel Number: %i\n", channel->at(ich));
                    printf("***********************************************************\n\n");
                    }
            }
        }
    }

    h2->SetLineColor(kRed);
    h2->Draw();
    h2->GetXaxis()->SetTitle("Energy [KeV]");
    h2->GetYaxis()->SetTitle("counts");
    h->SetLineStyle(2);
    h->SetLineColor(kBlue);
    h->Draw("same");
    
}
