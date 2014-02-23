#include "G4SBSRunData.hh"

#include <string.h>
#include <errno.h>

G4SBSRunData::G4SBSRunData(){
    fNthrown = -1;
    fBeamE   = -1e9;
    fGenName[0]  = '\0';
    fGitInfo[0]  = '\0';
    fHostName[0] = '\0';
}

G4SBSRunData::~G4SBSRunData(){
}

void G4SBSRunData::Init(){
    fNthrown = 0;
    fBeamE   = 0;
    strcpy(fGenName, "default");
    strcpy(fGitInfo, gGitInfoStr);
    if(gethostname(fHostName,__RUNSTR_LEN) == -1){
	fprintf(stderr, "%s line %d: ERROR could not get hostname\n", __PRETTY_FUNCTION__ ,  __LINE__ );
	fprintf(stderr, "%s\n",strerror(errno));
    }
    if(getcwd(fRunPath,__RUNSTR_LEN) == NULL){
	fprintf(stderr, "%s line %d: ERROR could not get current working directory\n", __PRETTY_FUNCTION__ ,  __LINE__ );
	fprintf(stderr, "%s\n",strerror(errno));
    }
}

void G4SBSRunData::Print() const { Print(NULL); }

void G4SBSRunData::Print(Option_t *) const {
    printf("git repository info\n-------------------------------------------------\n%s-------------------------------------------------\n\n", fGitInfo);
    printf("Run at %s on %s\n", fRunTime.AsString("ls"), fHostName);
    printf("Run Path %s\n", fRunPath);
    printf("N generated = %ld\n", fNthrown);
    printf("Beam Energy = %f GeV\n", fBeamE);
    printf("Generator   = %s\n", fGenName);

    printf("Field maps:\n");
    unsigned int i;
    for( i = 0; i < fMagData.size(); i++ ){
	printf("\t%s\n", fMagData[i].filename);
	printf("\t%s\n", fMagData[i].hashsum);
	printf("\t%s\n\n", fMagData[i].timestamp.AsString("ls"));
    }

    printf("Macro run:\n-------------------------------------------------\n");

    fMacro.Print();
    

}

ClassImp(G4SBSRunData)











