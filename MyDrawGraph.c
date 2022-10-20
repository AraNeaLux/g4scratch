//#include <cstdio>
 
TGraph* makeRSTrack(int event){

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
  t1->SetBranchAddress("z",&xpos);
  t1->SetBranchAddress("y",&ypos);
  t1->SetBranchAddress("EventID",&EventID);
  t1->SetBranchAddress("StepNum",&StepNum);
  t1->SetBranchAddress("Volume",&Volume);

  double theta = 0;
  double thresh = 0;
  double weight = 1;

  // Add positions to vectors by event number
  TRandom3* r = new TRandom3();
  for (long i = 0;i<t1->GetEntries();i++){
    t1->GetEntry(i);
    if (EventID==event ){//&& weight < thresh){
      cout << event << endl;
      if (StepNum == 1){
        t1->GetEntry(i+2);  
        TVector3 scattervec(0,ypos,(xpos-1));
        theta = scattervec.Theta();
        thresh = 20*TMath::Exp(theta-TMath::Pi())-0.85;
        weight = r->Rndm();
        t1->GetEntry(i);
      } 
      //cout << xpos << "\t" << ypos << endl;
      //cout << thresh << "\t" << weight << endl;
      //if (weight < thresh){
        xposvec.push_back(xpos); 
        yposvec.push_back(ypos);
      //}
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

TPolyLine* makeRSDetector(double theta = TMath::Pi()/2.){

  // Distance to center of box
  double r = 86000;

  double dx1,dy1;
  double dx2,dy2;
  double dx3,dy3;
  double dx4,dy4;

  double dx1p,dy1p;
  double dx2p,dy2p;
  double dx3p,dy3p;
  double dx4p,dy4p;

  // Coords of corners of box
  dx1 = -10000.0;
  dy1 = -20000.0;

  dx2 =  10000.0;
  dy2 = -20000.0;

  dx3 =  10000.0;
  dy3 =  20000.0;

  dx4 = -10000.0;
  dy4 =  20000.0;

  // Rotate boxes
  dx1p = dx1*cos(-theta)+dy1*sin(-theta);
  dy1p = dy1*cos(-theta)-dx1*sin(-theta);

  dx2p = dx2*cos(-theta)+dy2*sin(-theta);
  dy2p = dy2*cos(-theta)-dx2*sin(-theta);

  dx3p = dx3*cos(-theta)+dy3*sin(-theta);
  dy3p = dy3*cos(-theta)-dx3*sin(-theta);

  dx4p = dx4*cos(-theta)+dy4*sin(-theta);
  dy4p = dy4*cos(-theta)-dx4*sin(-theta);

  // Translate boxes
  double xt = r*cos(theta);
  double yt = r*sin(theta);
  double x2[5] = {dx1p+xt,dx2p+xt,dx3p+xt,dx4p+xt,dx1p+xt};
  double y2[5] = {dy1p+yt,dy2p+yt,dy3p+yt,dy4p+yt,dy1p+yt};

  TPolyLine *box2 = new TPolyLine(5,x2,y2);
  box2->SetLineColor(kBlue);
  box2->SetLineWidth(2);
  box2->SetFillStyle(0);
  
  return box2;
}

TPolyLine* makeRSTarget(){
  double x[5] = {-1.,1.,1.,-1.,-1.};
  double y[5] = {-30000.0,-30000.0,30000.0,30000.0,-30000.0};
  TPolyLine *box = new TPolyLine(5,x,y);
  box->SetLineColor(2);
  box->SetLineWidth(2);
  box->SetFillStyle(0);
  return box;
}

TGraph* makeRSBlankCanvas(){
  // Make an "empty" graph with setup dimensions
  double x[5] = {-100000.,-100000.,100000.,100000.,-100000};
  double y[5] = {-100000.,100000.,100000.,-100000.,-100000};
  TGraph* gr = new TGraph(5,x,y);
  return gr;
}

void makeRSSetup(){
  // Place boxes on graph
  TPolyLine *box = makeRSTarget();
  box->Draw("same");

  for (int i=7; i<=17; i++){
    TPolyLine *box2 = makeRSDetector(TMath::Pi()*i/6);
    box2->Draw("same"); 
  }
}

TMultiGraph* makeRSMultiGr(int num=10, int start=10){
  TMultiGraph* mg = new TMultiGraph;
  mg->Add(makeRSBlankCanvas());
  for (int i=0;i<num;i++){
    mg->Add(makeRSTrack(i+start));
    //gr->Draw("same");
  }
  return mg;
}

void makeRSPicture(int num =10, int start = 0){
  
  TMultiGraph* mg = makeRSMultiGr(num, start);
  mg->Draw("Al*");
  makeRSSetup();

}

void MyDrawGraph(int event = 137){
  
  TFile *_file0 = TFile::Open("output.root");
  TTree *t1 = (TTree*)_file0->Get("t1");

  std::vector<double> xposvec;
  std::vector<double> yposvec;
  std::vector<std::string> particleNamevec;

  xposvec.push_back(-9);
  yposvec.push_back(0);

  double xpos; 
  double ypos; 
  std::string particleName;
  int EventID;
  int StepNum;


  t1->SetBranchAddress("x",&xpos);
  t1->SetBranchAddress("y",&ypos);
//  t1->SetBranchAddress("ParticleName",&particleName);
  t1->SetBranchAddress("EventID",&EventID);
  t1->SetBranchAddress("StepNum",&StepNum);

  for (long i = 0;i<t1->GetEntries();i++){
    t1->GetEntry(i);
    if (EventID==event){

      xposvec.push_back(xpos);
      yposvec.push_back(ypos);
  //    particleNamevec.push_back(particleName);

    } else if (EventID > event){
      break;
    }
  }
  //TH2D *h3 = new TH2D("h3","h3",1000,-100,100,1000,-100,100);
 
  TGraph* gr = (TGraph*)gROOT->FindObject("gr");

//  cout << "gr: " << gr << endl;

  bool first = false;
  double ymin,ymax,xmin,xmax;
  
  if (!gr){
    gr = new TGraph(xposvec.size(),&(xposvec[0]),&(yposvec[0]));
    first = true;
    gr->SetName("gr");
    gr->Draw("Al*");
  } else if(gPad){
    ymin = gPad->GetUymin();
    ymax = gPad->GetUymax();

    xmin = gPad->GetUxmin();
    xmax = gPad->GetUxmax();

    gr->Set(xposvec.size());
    for(int i = 0;i<xposvec.size();i++){
      gr->SetPoint(i,xposvec[i],yposvec[i]);
    }

  }
  gr->SetTitle(Form("event: %i",event));

  double x[5] = {-.00001,.00001,.00001,-.00001,-.00001};
  double y[5] = {-3.0,-3.0,3.0,3.0,-3.0};
  TPolyLine *box = new TPolyLine(5,x,y);
  box->SetLineColor(2);
  box->SetLineWidth(2);
  box->SetFillStyle(0);

  double dx1,dy1;
  double dx2,dy2;
  double dx3,dy3;
  double dx4,dy4;

  double dx1p,dy1p;
  double dx2p,dy2p;
  double dx3p,dy3p;
  double dx4p,dy4p;

  dx1 = -1.0;
  dy1 = -3.0;

  dx2 =  1.0;
  dy2 = -3.0;

  dx3 =  1.0;
  dy3 =  3.0;

  dx4 = -1.0;
  dy4 =  3.0;

  double theta = 1.*TMath::Pi()/4.;

  dx1p = dx1*cos(theta)+dy1*sin(theta);
  dy1p = dy1*cos(theta)-dx1*sin(theta);

  dx2p = dx2*cos(theta)+dy2*sin(theta);
  dy2p = dy2*cos(theta)-dx2*sin(theta);

  dx3p = dx3*cos(theta)+dy3*sin(theta);
  dy3p = dy3*cos(theta)-dx3*sin(theta);

  dx4p = dx4*cos(theta)+dy4*sin(theta);
  dy4p = dy4*cos(theta)-dx4*sin(theta);

  double xt = -5.0;
  double yt =  5.0;

  double x2[5] = {dx1p+xt,dx2p+xt,dx3p+xt,dx4p+xt,dx1p+xt};
  double y2[5] = {dy1p+yt,dy2p+yt,dy3p+yt,dy4p+yt,dy1p+yt};
  TPolyLine *box2 = new TPolyLine(5,x2,y2);
  box2->SetLineColor(kBlue);
  box2->SetLineWidth(2);
  box2->SetFillStyle(0);

  gr->GetXaxis()->SetLimits(-0.12,0.12);
  gr->SetMinimum(-.001);
  gr->SetMaximum(.001);

  gr->Draw("Al*");
  box->Draw("same");
  box2->Draw("same");
  if(!first){

//    cout << "xmin: " << xmin << "\txmax: "<< xmax << endl;
//    cout << "ymin: " << ymin << "\tymax: "<< ymax << endl;

    gr->GetYaxis()->SetRangeUser(ymin,ymax);
    gr->GetXaxis()->SetRangeUser(xmin,xmax);
    gPad->Modified();
    gPad->Update();
  }

/*
  TTree *t1 = (TTree*)_file0->Get("t1");

  t1->Project("h1","y:x","ParticleName==\"gamma\" && StepNum==1");
  t1->Project("h2","y:x","ParticleName==\"gamma\" && StepNum==2");
  t1->Project("h3","y:x","ParticleName==\"gamma\" ");

  double x[5] = {-1,1,1,-1,-1};
  double y[5] = {-30,-30,30,30,-30};
  TPolyLine *box = new TPolyLine(5,x,y);
  box->SetLineColor(2);
  box->SetLineWidth(2);
  box->SetFillStyle(0);

  double dx1,dy1;
  double dx2,dy2;
  double dx3,dy3;
  double dx4,dy4;

  double dx1p,dy1p;
  double dx2p,dy2p;
  double dx3p,dy3p;
  double dx4p,dy4p;

  dx1 = -10;
  dy1 = -30;

  dx2 =  10;
  dy2 = -30;

  dx3 =  10;
  dy3 =  30;

  dx4 = -10;
  dy4 =  30;

  double theta = 1.*TMath::Pi()/4.;

  dx1p = dx1*cos(theta)+dy1*sin(theta);
  dy1p = dy1*cos(theta)-dx1*sin(theta);

  dx2p = dx2*cos(theta)+dy2*sin(theta);
  dy2p = dy2*cos(theta)-dx2*sin(theta);

  dx3p = dx3*cos(theta)+dy3*sin(theta);
  dy3p = dy3*cos(theta)-dx3*sin(theta);

  dx4p = dx4*cos(theta)+dy4*sin(theta);
  dy4p = dy4*cos(theta)-dx4*sin(theta);

  double xt = -50;
  double yt =  50;

  double x2[5] = {dx1p+xt,dx2p+xt,dx3p+xt,dx4p+xt,dx1p+xt};
  double y2[5] = {dy1p+yt,dy2p+yt,dy3p+yt,dy4p+yt,dy1p+yt};
  TPolyLine *box2 = new TPolyLine(5,x2,y2);
  box2->SetLineColor(kBlue);
  box2->SetLineWidth(2);
  box2->SetFillStyle(0);

  TCanvas *c = new TCanvas;

  c->Divide(3,1);

  c->cd(1);
  h1->Draw("colz");
  box->Draw("same");
  box2->Draw("same");

  c->cd(2);
  h2->Draw("colz");
  box->Draw("same");
  box2->Draw("same");

  c->cd(3);
  h3->Draw("colz");
  box->Draw("same");
  box2->Draw("same");
*/
}


