 #ifndef H_MG_LAYER
 #define H_MG_LAYER


  /* Layer.h    -----   LIF7 Auto-Didacte */


#include "Neuron.h"


/* Layer structure*/
typedef struct{

	char type;
	int nbNeurons;
	Neuron ** tabNeurons;

}Layer;


/* Layer constructors */
Layer * newInputLayer(int nbNeurons, int nbHiddenNeuron);
Layer * newHiddenLayer(int nbNeurons, int nbOutputNeuron);
Layer * newOutputLayer(int nbNeurons);

/* Layer get/set */
int getNbNeurons(const Layer* layer);
void setNbNeurons(Layer* layer, int nbNeurons);

char getTypeLayer(const Layer * layer);
void setTypeLayer(Layer * layer, char newType);

Neuron * getNeuron(const Layer * layer, int i);
void setNeuron(Layer * layer, int i, Neuron * newNeuron);


/* Layer functions */
void updateInputLayer(Layer * layer, float * tabNewValues);
void updateLayer(Layer * layer1, Layer* layer2);
void initialiseLayerTEST(Layer * layer);
float sigmoid(float x);


/* Layer destructor */
void deleteLayer(Layer * layer);


#endif

