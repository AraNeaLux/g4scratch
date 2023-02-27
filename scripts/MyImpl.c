//#include <cstdio>

void MyImpl(){
  std::cout << "Macro for implantation simulation loaded." << std::endl;
}
 
TGraph* makeImpTrack(int event){

  // Open file with tree
  TFile *_file0 = TFile::Open("output.root");
  TTree *t1 = (TTree*)_file0->Get("t1");

  // Make vectors to store track data
  std::vector<double> xposvec;
  std::vector<double> yposvec;

  // Set initial positions
  double xinit = -90000;
  double yinit = 0;
  xposvec.push_back(xinit);
  yposvec.push_back(yinit);
  //cout << xinit << "\t" << yinit << endl;

  // variable stuff
  double xpos;
  double ypos;
  std::string particleName;
  int EventID;
  int Volume;
  int StepNum;

  // Get tree info locations
  t1->SetBranchAddress("zdep",&xpos);
  t1->SetBranchAddress("y",&ypos);
  t1->SetBranchAddress("EventID",&EventID);
  t1->SetBranchAddress("Volume",&Volume);

  // Add positions to vectors by event number
  for (long i = 0;i<t1->GetEntries();i++){
    t1->GetEntry(i);
    if (EventID==event){
      //cout << xpos << "\t" << ypos << endl;
      xposvec.push_back(xpos); 
      yposvec.push_back(ypos);
    } else if (EventID > event){
      break;
    }
  }

  // Make graph
  TGraph* gr = new TGraph(xposvec.size(),&(xposvec[0]),&(yposvec[0]));

  for(int i = 0;i<xposvec.size();i++){
    gr->SetPoint(i,xposvec[i],yposvec[i]);
  }
  
  _file0->Close();
  return gr;
}


TPolyLine* makeImpTarget(){
  double x[5] = {-10000.,10000.,10000.,-10000.,-10000.};
  double y[5] = {-30000.0,-30000.0,30000.0,30000.0,-30000.0};
  TPolyLine *box = new TPolyLine(5,x,y);
  box->SetLineColor(2);
  box->SetLineWidth(2);
  box->SetFillStyle(0);
  return box;
}

TGraph* makeImpBlankCanvas(){
  // Make an "empty" graph with setup dimensions
  double x[5] = {-100000.,-100000.,100000.,100000.,-100000};
  double y[5] = {-100000.,100000.,100000.,-100000.,-100000};
  TGraph* gr = new TGraph(5,x,y);
  return gr;
}

void makeImpSetup(){
  // Place boxes on graph
  TPolyLine *box = makeImpTarget();
  box->Draw("same");
}

TMultiGraph* makeImpMultiGr(int num=10, int start=10){
  TMultiGraph* mg = new TMultiGraph;
  //mg->Add(makeImpBlankCanvas());
  for (int i=0;i<num;i++){
    mg->Add(makeImpTrack(i+start));
    //gr->Draw("same");
  }
  return mg;
}

void myImpPicture(int num =10, int start = 0){
  
  TMultiGraph* mg = makeImpMultiGr(num, start);
  mg->Draw("Al*");
  makeImpSetup();

}

double avgImpDepth(const char *filename = "output.root"){

  // Open file with tree
  TFile *_file0 = TFile::Open(filename);
  TTree *t1 = (TTree*)_file0->Get("t1");

  // Make vectors to store track data
  std::vector<double> zposvec;
  std::vector<double> zdepposvec;

  double xinit = -90000;

  // variable stuff
  double zpos;
  double zdeppos;
  int EventID;
  int Volume;
  int StepNum;

  // Get tree info locations
  t1->SetBranchAddress("z",&zpos);
  t1->SetBranchAddress("zdep",&zdeppos);
  t1->SetBranchAddress("EventID",&EventID);
  t1->SetBranchAddress("Volume",&Volume);
  t1->SetBranchAddress("StepNum",&StepNum);

  // Add positions to vectors by event number
  for (long i = 0;i<t1->GetEntries()+1;i++){
    t1->GetEntry(i);
    if (StepNum==1){
      if (EventID ==0){}
      else{
        t1->GetEntry(i-1);
        if (Volume ==1){
          //cout << EventID << "\t" << StepNum << "\t" << zpos << endl;
          zposvec.push_back(zpos+10000);
          zdepposvec.push_back(zdeppos+10000);
        }else {}
      }
    }
  }

   double zposavg = accumulate(zposvec.begin(), zposvec.end(), 0.0) / zposvec.size();
  cout << zposavg << endl;


  return zposavg;
  _file0->Close();
  //return zposvec[0];
}
