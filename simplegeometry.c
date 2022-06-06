{
  new TGeoManager("world", "A simple geometry.");

  TGeoMaterial *mat1 = new TGeoMaterial("Hydrogen",1.,1.,0.1);
  TGeoMedium *med1 = new TGeoMedium("Hydrogen",1,mat1);

  TGeoMaterial *mat2 = new TGeoMaterial("Carbon",12,6,0.5);
  TGeoMedium *med2 = new TGeoMedium("Carbon",2,mat2);

  TGeoVolume *top = gGeoManager->MakeBox("Top",med1,10.,10.,10.);
  TGeoVolume *bot = gGeoManager->MakeTubs("Bottom",med2,0.,5.,5.,0.,360.);

  gGeoManager->SetTopVolume(top);

  top->AddNode(bot,1);

  gGeoManager->CloseGeometry();

  top->SetLineColor(kMagenta);
  bot->SetLineColor(kCyan);
  gGeoManager->SetTopVisible();
  top->Draw();

  gGeoManager->Export("simplegeometry.gdml");

}
