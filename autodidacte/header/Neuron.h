 #ifndef H_NEURON
 #define H_NEURON


  /* Neuron.h   -----   LIF7 Auto-Didacte */



/* Neuron structure */

typedef struct
{

    char type;
    float value;
    float * tabWeights;

} Neuron;




/* Neuron functions */

Neuron * newNeuron(char type, int nbHiddenNeuron);
void deleteNeuron(Neuron * neuron);

float getValue(Neuron * neuron);
void  setValue(Neuron * neuron, float newValue);

float getWeight(Neuron * neuron, int i);
void  setWeight(Neuron * neuron, int i, float newWeight);

void  updateNeuron(Neuron * neuron);

#endif
