{
  new TGeoManager("world", "A simple geometry.");

  TGeoMaterial *mat1 = new TGeoMaterial("Vacuum",0.,0.,0.);
  TGeoMedium *med1 = new TGeoMedium("Vacuum",1,mat1);

  TGeoMaterial *mat2 = new TGeoMaterial("Aluminum",27,13,2.7);
  TGeoMedium *med2 = new TGeoMedium("Aluminum",2,mat2);

  TGeoVolume *myWorld = gGeoManager->MakeBox("myWorld",med1,10.,10.,10.);
  TGeoVolume *myBlock = gGeoManager->MakeBox("myBlock",med2,1.,5.,9.);

  gGeoManager->SetTopVolume(myWorld);

  myWorld->AddNode(myBlock,1);

  gGeoManager->CloseGeometry();

  myWorld->SetLineColor(kMagenta);
  myBlock->SetLineColor(kCyan);
  gGeoManager->SetTopVisible();
  myWorld->Draw();

  gGeoManager->Export("simplegeometry.gdml");

}
