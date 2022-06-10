#ifndef __MyOutputManager_h__
#define __MyOutputManager_h__

class MyOutputManager{

  public: 
    static MyOutputManager* Get();

    ~MyOutputManager();
    void setupTree(const char *fname);
    void closeTree();


  private:
    MyOutputManager();
    static MyOutputManager* fptr;
//    TFile *foutput;
//    TTree *fTree;

};




#endif
