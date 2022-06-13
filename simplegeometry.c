{

  new TGeoManager("world", "A simple geometry.");

  TGeoMaterial *mat1 = new TGeoMaterial("Vacuum",16.,8.,0.);
  TGeoMedium *med1 = new TGeoMedium("Vacuum",1,mat1);

  TGeoMaterial *mat2 = new TGeoMaterial("Aluminum",27,13,2.7);
  //TGeoMaterial *mat2 = new TGeoMaterial("Aluminum",27,13,0.1);
  TGeoMedium *med2 = new TGeoMedium("Aluminum",2,mat2);

  //TGeoMaterial *mat3 = new TGeoMaterial("Germanium",72,32,5.3);
  //TGeoMedium *med3 = new TGeoMedium("Germanium",3,mat3);
  TGeoMaterial *mat3 = new TGeoMaterial("Silicon",28,14,2.3);
  TGeoMedium *med3 = new TGeoMedium("Silicon",3,mat3);

  TGeoVolume *myWorld = gGeoManager->MakeBox("myWorld",med1,10.,10.,10.);
  TGeoVolume *myBlock = gGeoManager->MakeBox("myBlock",med2,.1,3.,5.);
  TGeoVolume *myDetector = gGeoManager->MakeBox("myDetector",med3,1.,3.,5.);

  gGeoManager->SetTopVolume(myWorld);

  TGeoRotation *rot1 = new TGeoRotation("rot1", 0., 0., 0.);
  myWorld->AddNode(myBlock,1, new TGeoCombiTrans(5,0,0,rot1));

  TGeoRotation *rot2 = new TGeoRotation("rot2", -45., 0., 0.);
  myWorld->AddNode(myDetector,1, new TGeoCombiTrans(0,5,0,rot2));

  gGeoManager->CloseGeometry();

  myWorld->SetLineColor(kMagenta);
  myBlock->SetLineColor(kCyan);
  gGeoManager->SetTopVisible();
  myWorld->Draw();

  gGeoManager->Export("simplegeometry.gdml");

}
