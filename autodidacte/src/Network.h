 #ifndef H_MG_NETWORK
 #define H_MG_NETWORK


  /* Network.h    -----   LIF7 Auto-Didacte */


#include "Layer.h"


/* Network structure*/
typedef struct{

	int nbInputNeurons;
	int nbHiddenNeurons;
	int nbOutputNeurons;

	Layer ** tabLayers;

}Network;


/* Network constructor */
Network * newNetwork(int nbInputNeurons, int nbHiddenNeurons, int nbOutputNeurons);

/* Network get/set */
int getNbInputNeurons(const Network * net);
void setNbInputNeurons(Network * net, int nbNeurons);

int getNbHiddenNeurons(const Network * net);
void setNbHiddenNeurons(Network * net, int nbNeurons);

int getNbOutputNeurons(const Network * net);
void setNbOutputNeurons(Network * net, int nbNeurons);

Layer * getLayer(const Network * network, int type);
void setLayer(Network * network, int type, Layer * newLayer);


/* Network functions */
void initialiseNetworkTEST(Network * net);
void feedForward(Network * net, float * tabNewValues);



/* Netwok destructor */
void deleteNetwork(Network * net);







#endif