 #ifndef H_MG_LAYER
 #define H_MG_LAYER


  /* Layer.h    -----   LIF7 Auto-Didacte */


#include "Neuron.h"


/* ----- Layer structure ----- */

/**
 * @struct Layer
 * @brief  Layers are parts of the Network, and contain Neurons. There are 3 layers in our projet: INPUT, HIDDEN and OUTPUT.
 */
typedef struct{

	int type; /**< The Layer's type.*/
	int nbNeurons; /** The number of Neurons contained in the Layer. */
	Neuron ** tabNeurons; /**< The array containing the Neurons, of size nbNeurons. */

}Layer;


/* ----- Layer constructors ----- */


/**
 * @brief      Creates a new Input Layer.
 *
 * @param[in]  nbNeurons       The number of Input Neurons the layer will have.
 * @param[in]  nbHiddenNeuron  The number of weights these Layer's Neurons will have.
 *
 * @return     New layer's adress.
 */
Layer * newInputLayer(int nbNeurons, int nbHiddenNeuron);


/**
 * @brief      Creates a new Hidden Layer.
 *
 * @param[in]  nbNeurons       The number of Hidden Neurons the layer will have.
 * @param[in]  nbOutputNeuron  The number of weights these Layer's Neurons will have.
 *
 * @return     New layer's adress.
 */
Layer * newHiddenLayer(int nbNeurons, int nbOutputNeuron);


/**
 * @brief      Creates a new Output Layer.
 *
 * @param[in]  nbNeurons  The number of Output Neurons the layer will have.
 *
 * @return     New Layer's adress.
 */
Layer * newOutputLayer(int nbNeurons);





/* ----- Layer get/set ----- */


/**
 * @brief      Get the nb of neurons.
 *
 * @param[in]  layer  Layer's adress.
 *
 * @return     Layer's nb of neurons.
 */
int getNbNeurons(const Layer* layer);

/**
 * @brief      Set the nb of neurons.
 *
 * @param[in,out]      layer      Layer's adress.
 * @param[in]  nbNeurons  Layer's new number of Neurons.
 */
void setNbNeurons(Layer* layer, int nbNeurons);


/**
 * @brief      Get the layer's type.
 *
 * @param[in]      layer  Layer's adress.
 *
 * @return     Layer's type.
 */
int getTypeLayer(const Layer * layer);

/**
 * @brief      Set the layer's type.
 *
 * @param[in,out]      layer    Layer's adress.
 * @param[in]  newType  Layer's new type.
 */
void setTypeLayer(Layer * layer, int newType);


/**
 * @brief      Get the neuron.
 *
 * @param[in]  layer  Layer's adress.
 * @param[in]  i      Neuron's index.
 *
 * @return     Layer's Ith Neuron.
 */
Neuron * getNeuron(const Layer * layer, int i);

/**
 * @brief      Set the neuron.
 *
 * @param[in/out]     layer      Layer's adress.
 * @param[in]  		  i          Neuron's index.
 * @param[in,out]     newNeuron  Layer's new Neuron that replaces Ith Neuron.
 */
void setNeuron(Layer * layer, int i, Neuron * newNeuron);





/* ----- Layer functions ----- */


/**
 * @brief      Updates the Input Layer's Neurons values from sensors. (Represented by a floats array).
 *
 * @param[in,out]      layer         Layer's adress.
 * @param[in]      tabNewValues  Layer's Neurons new values.
 */
void updateInputLayer(Layer * layer, const float * tabNewValues);

/**
 * @brief      Updates the Hidden or Output Layer's Neurons values from the previous layer.
 *
 * @param[in]      layer1  First Layer's adress. Can only be the adress of Input or Hidden Layer.
 * @param[in,out]      layer2  Second Layer's adress. If 1st layer's type is Input, this one's is Hidden. If 1st layer's type is Hidden, this one's is Output.
 */
void updateLayer(const Layer * layer1, Layer* layer2);

/**
 * @brief      Test function, only used in regression tests. Initialises a Layer's Neurons weights.
 *
 * @param[in,out]      layer  Layer's adress. Can only be an Input or Hidden Layer.
 */
void initialiseLayerTEST(Layer * layer);

/**
 * @brief      Checks every Layer's Neuron value and gives the highest one.
 *
 * @param[in,out]      layer  Layer's adress.
 *
 * @return     Returns the Neuron with the highest value index.
 */
int selectHigherValue(Layer * layer);

/**
 * @brief      Regulation and activation function for Neurons, used in updateLayer.
 *
 * @param[in]  x     A real number.
 *
 * @return     sigmoid(x);
 */
float sigmoid(float x);





/* ----- Layer destructor ----- */


/**
 * @brief      Deletes a Layer structure.
 *
 * @param[in,out]      layer  Layer's adress.
 */
void deleteLayer(Layer * layer);


#endif

