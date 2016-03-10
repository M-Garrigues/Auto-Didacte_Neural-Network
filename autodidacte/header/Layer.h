 #ifndef H_LAYER
 #define H_LAYER


  /* Layer.h    -----   LIF7 Auto-Didacte */


#include "Neuron.h"

/* Layer structure*/

typedef struct{

	char type;
	int nbNeurons;
	Neuron * tabNeurons;

}Layer;

/* Layer functions */

Layer * newLayer(char type , int nbNeurons);
void deleteLayer(Layer * layer);

char getNbNeurons(const Layer* layer);
void setNbNeurons(int nbNeurons);

Neuron * getNeuron(const Layer* layer, int i);
void setNeuron(Layer * layer, int i);

void updateLayer(Layer * layer);


#endif

