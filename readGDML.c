{
  new TGeoManager("worldcopy", "Read a simple geometry.");
  TGeoManager::Import("simplegeometry.gdml");

  worldcopyTopVol = gGeoManager->GetTopVolume();
  //worldcopyTopVol->SetLineColor(kMagenta);
  //myBlock->SetLineColor(kCyan);
  gGeoManager->SetTopVisible();
  worldcopyTopVol->Draw();

}
