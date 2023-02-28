{

  new TGeoManager("world", "A simple geometry.");

  TGeoMaterial *mat1 = new TGeoMaterial("Vacuum",1.,0.,0.);
  TGeoMedium *med1 = new TGeoMedium("Vacuum",1,mat1);
  TGeoVolume *myWorld = gGeoManager->MakeBox("myWorld",med1,10.,10.,10.);

//  TGeoMaterial *mat2 = new TGeoMaterial("Aluminum",27,13,2.7);
//  TGeoMedium *med2 = new TGeoMedium("Aluminum",2,mat2);
//  TGeoMaterial *mat2 = new TGeoMaterial("Be",9,4,1.85);
//  TGeoMedium *med2 = new TGeoMedium("Be",2,mat2);
  TGeoMaterial *mat2 = new TGeoMaterial("Au",197,79,19.3);
  TGeoMedium *med2 = new TGeoMedium("Au",2,mat2);
//  TGeoMaterial *mat2 = new TGeoMaterial("Fe",56,26,7.874);
//  TGeoMedium *med2 = new TGeoMedium("Fe",2,mat2);

  TGeoVolume *myBlock = gGeoManager->MakeBox("myBlock",med2,0.0001,3.,5.);

  TGeoMaterial *mat4 = new TGeoMaterial("p",1,1,10);
  TGeoMedium *med4 = new TGeoMedium("p",4,mat4);

  //TGeoVolume *myLayer1 = gGeoManager->MakeBox("myLayer1",med4,0.0000001,3.,5.);

  //TGeoMaterial *mat3 = new TGeoMaterial("Germanium",72,32,5.3);
  //TGeoMedium *med3 = new TGeoMedium("Germanium",3,mat3);
  TGeoMaterial *mat3 = new TGeoMaterial("Silicon",28,14,2.3);
  //TGeoMaterial *mat3 = new TGeoMaterial("Silicon",28,14,0);
  TGeoMedium *med3 = new TGeoMedium("Silicon",3,mat3);

  TGeoVolume *myDetector = gGeoManager->MakeBox("myDetector",med3,1.,2.,5.);

  gGeoManager->SetTopVolume(myWorld);

  TGeoRotation *rot1 = new TGeoRotation("rot1", 0., 90., 90.);
  myWorld->AddNode(myBlock,1, new TGeoCombiTrans(0.,0.,0.,rot1));

  //TGeoRotation *rot2 = new TGeoRotation("rot2", 0., 0., 0.);
  //myWorld->AddNode(myLayer1,1, new TGeoCombiTrans(-0.0001001,0.,0.,rot2));

  float pi = TMath::Pi();

  double r = 8.6;

  TGeoRotation *drot1p = new TGeoRotation("drot2p", 0. ,90. ,90.);
  TGeoRotation *drot2p = new TGeoRotation("drot2p", 0. ,90. ,60.);
  TGeoRotation *drot3p = new TGeoRotation("drot3p", 0. ,90. ,30.);
  TGeoRotation *drot4p = new TGeoRotation("drot4p", 0. ,90. ,0.);
  TGeoRotation *drot5p = new TGeoRotation("drot5p", 0. ,90. ,150.);
  TGeoRotation *drot6p = new TGeoRotation("drot6p", 0. ,90. ,120.);
  TGeoRotation *drot2n = new TGeoRotation("drot2n", 0. ,90. ,-60.);
  TGeoRotation *drot3n = new TGeoRotation("drot3n", 0. ,90. ,-30.);
  TGeoRotation *drot4n = new TGeoRotation("drot4n", 0. ,90. ,0.);
  TGeoRotation *drot5n = new TGeoRotation("drot5n", 0. ,90. ,-150.);
  TGeoRotation *drot6n = new TGeoRotation("drot6n", 0. ,90. ,-120.);
  myWorld->AddNode(myDetector,1, new TGeoCombiTrans(0.,0.,r,drot1p));
  myWorld->AddNode(myDetector,2, new TGeoCombiTrans(r*sin(pi/6),0.,r*cos(pi/6),drot2p));
  myWorld->AddNode(myDetector,3, new TGeoCombiTrans(r*sin(pi/3),0.,r*cos(pi/3),drot3p));
  myWorld->AddNode(myDetector,4, new TGeoCombiTrans(r*sin(pi/2),0.,r*cos(pi/2),drot4p));
  myWorld->AddNode(myDetector,5, new TGeoCombiTrans(r*sin(pi/3),0.,-r*cos(pi/3),drot5p));
  myWorld->AddNode(myDetector,6, new TGeoCombiTrans(r*sin(pi/6),0.,-r*cos(pi/6),drot6p));
  myWorld->AddNode(myDetector,7, new TGeoCombiTrans(-r*sin(pi/6),0.,r*cos(pi/6),drot2n));
  myWorld->AddNode(myDetector,8, new TGeoCombiTrans(-r*sin(pi/3),0.,r*cos(pi/3),drot3n));
  myWorld->AddNode(myDetector,9, new TGeoCombiTrans(-r*sin(pi/2),0.,r*cos(pi/2),drot4n));
  myWorld->AddNode(myDetector,10, new TGeoCombiTrans(-r*sin(pi/3),0.,-r*cos(pi/3),drot5n));
  myWorld->AddNode(myDetector,11, new TGeoCombiTrans(-r*sin(pi/6),0.,-r*cos(pi/6),drot6n));

  gGeoManager->CloseGeometry();

  myWorld->SetLineColor(kMagenta);
  myBlock->SetLineColor(kCyan);
  gGeoManager->SetTopVisible();
  myWorld->Draw();

  gGeoManager->Export("simplegeometry.gdml");

}
