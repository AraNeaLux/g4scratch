void readGDML(const char *fname="simplegeometry.gdml") {
  TGeoManager *gm = new TGeoManager("worldcopy", "Read a simple geometry.");
  TGeoManager::Import(fname);

  TGeoVolume *worldcopyTopVol = gGeoManager->GetTopVolume();
  //worldcopyTopVol->SetLineColor(kMagenta);
  //myBlock->SetLineColor(kCyan);
  gm->SetTopVisible();
  worldcopyTopVol->Draw();

}
