{

  new TGeoManager("world", "A simple geometry.");

  TGeoMaterial *mat1 = new TGeoMaterial("Vacuum",1.,0.,0.);
  TGeoMedium *med1 = new TGeoMedium("Vacuum",1,mat1);
  TGeoVolume *myWorld = gGeoManager->MakeBox("myWorld",med1,10.,10.,10.);

  TGeoMaterial *mat2 = new TGeoMaterial("Aluminum",27,13,2.7);
  TGeoMedium *med2 = new TGeoMedium("Aluminum",2,mat2);
//  TGeoMaterial *mat2 = new TGeoMaterial("Be",9,4,1.85);
//  TGeoMedium *med2 = new TGeoMedium("Be",2,mat2);
//  TGeoMaterial *mat2 = new TGeoMaterial("Au",197,79,19.3);
//  TGeoMedium *med2 = new TGeoMedium("Au",2,mat2);
//  TGeoMaterial *mat2 = new TGeoMaterial("Fe",56,26,7.874);
//  TGeoMedium *med2 = new TGeoMedium("Fe",2,mat2);

  TGeoVolume *myBlock = gGeoManager->MakeBox("myBlock",med2,1.,3.,5.);

//  TGeoMaterial *mat4 = new TGeoMaterial("p",1,1,10);
//  TGeoMedium *med4 = new TGeoMedium("p",4,mat4);

  //TGeoVolume *myLayer1 = gGeoManager->MakeBox("myLayer1",med4,0.0000001,3.,5.);

  //TGeoMaterial *mat3 = new TGeoMaterial("Germanium",72,32,5.3);
  //TGeoMedium *med3 = new TGeoMedium("Germanium",3,mat3);
  //TGeoMaterial *mat3 = new TGeoMaterial("Silicon",28,14,2.3);
  //TGeoMaterial *mat3 = new TGeoMaterial("Silicon",28,14,0);
  //TGeoMedium *med3 = new TGeoMedium("Silicon",3,mat3);

  //TGeoVolume *myDetector = gGeoManager->MakeBox("myDetector",med3,1.,2.,5.);

  gGeoManager->SetTopVolume(myWorld);

  TGeoRotation *rot1 = new TGeoRotation("rot1", 0., 90., 90.);
  myWorld->AddNode(myBlock,1, new TGeoCombiTrans(0.,0.,0.,rot1));

  //TGeoRotation *rot2 = new TGeoRotation("rot2", 0., 0., 0.);
  //myWorld->AddNode(myLayer1,1, new TGeoCombiTrans(-0.0001001,0.,0.,rot2));
 
  gGeoManager->CloseGeometry();

  myWorld->SetLineColor(kMagenta);
  myBlock->SetLineColor(kCyan);
  gGeoManager->SetTopVisible();
  myWorld->Draw();

  gGeoManager->Export("simplegeometry.gdml");

}
