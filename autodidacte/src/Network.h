 #ifndef H_MG_NETWORK
 #define H_MG_NETWORK


  /* Network.h    -----   LIF7 Auto-Didacte */


#include "Layer.h"


/* ----- Network structure ----- */	

/**
 * @struct Network
 * @brief The brain of the project, this system contains layers of neurons and decides what the car does.
 */
typedef struct{

	int nbInputNeurons; /**< The number of neurons contained in the Input Layer. */
	int nbHiddenNeurons;/**< The number of neurons contained in the Hidden Layer. */
	int nbOutputNeurons;/**< The number of neurons contained in the Output Layer. */

	Layer ** tabLayers; /**< The array containing the adresses of the layers. */

	float activation; /**< The activation function, used to determine if an Output Neuron is activated.*/

}Network;


/* ----- Network constructor ----- */

/**
 * @brief      Creates a new Network
 *
 * @param[in]  nbInputNeurons   The number of neurons contained in the Input Layer.
 * @param[in]  nbHiddenNeurons  The number of neurons contained in the Hidden Layer.	
 * @param[in]  nbOutputNeurons  The number of neurons contained in the Output Layer.
 *
 * @return     New network's adress.
 */
Network * newNetwork(int nbInputNeurons, int nbHiddenNeurons, int nbOutputNeurons);



/* ----- Network get/set ----- */

/**
 * @brief      Get the nb of input neurons.
 *
 * @param[in]  net   Network's adress.
 *
 * @return     Number of Input Neurons.
 */
int getNbInputNeurons(const Network * net);

/**
 * @brief      Set the nb of Input Neurons.
 *
 * @param[in,out]      net        Network's adress.
 * @param[in]  nbNeurons  New number of Input Neurons.
 */
void setNbInputNeurons(Network * net, int nbNeurons);


/**
 * @brief      Get the nb of Hidden Neurons.
 *
 * @param[in]  net   Network's adress.
 *
 * @return     The number of Hidden Neurons.
 */
int getNbHiddenNeurons(const Network * net);


/**
 * @brief      Set the nb hidden neurons.
 *
 * @param[in,out]      net        Network's adress/
 * @param[in]  nbNeurons  New number of Input's Neurons.
 */
void setNbHiddenNeurons(Network * net, int nbNeurons);



/**
 * @brief      Get the nb output neurons.
 *
 * @param[in]  net   Network's adress.
 *
 * @return     The number of Outputs Neurons.
 */
int getNbOutputNeurons(const Network * net);

/**
 * @brief      Set the nb output neurons.
 *
 * @param[in,out]      net        Network's adress.
 * @param[in]  nbNeurons  New number of Output Neurons.
 */
void setNbOutputNeurons(Network * net, int nbNeurons);

/**
 * @brief      Get the layer.
 *
 * @param[in]  network  Network's adress.
 * @param[in]  type     Index of the queried Layer.
 *
 * @return     Indexed Layer.
 */
Layer * getLayer(const Network * network, int type);


/**
 * @brief      Set the indexed layer with the new layer.
 *
 * @param[in,out]      network   Network's adress.
 * @param[in]  type      Index of the Layer to replace.
 * @param[in,out]      newLayer  New layer.
 */
void setLayer(Network * network, int type, Layer * newLayer);


/**
 * @brief      Get the activation function.
 *
 * @param[in]  net  The network you want the activation function
 *
 * @return     the activation function.
 */
float getActivationNet(const Network * net);


/**
 * @brief      Set the activation function.
 *
 * @param[in,out]      net  The network you want to change the activation function
 * @param[in]  value   The new activation function
 */
void setActivationNet(Network * net, float newActivation);




/* ----- Network functions ----- */


/**	
 * @brief      Test functions, initialize network with pre setted values.
 *
 * @param      Network's adress.
 */
void initialiseNetworkTEST(Network * net);


/**
 * @brief      Updates the Network values when the entries change.
 *
 * @param      net           Network's adress.
 * @param      tabNewValues  New entries.
 */
void feedForward(Network * net, float * tabNewValues);



/* ----- Netwok destructor ----- */

/**
 * @brief      Deletes a Network.
 *
 * @param      net   Network's adress.
 */
void deleteNetwork(Network * net);



/**
 * @brief      Prints the whole network in the console. Only used for the regression test.
 *
 * @param      net   Network's adress.
 */
void printNetwork(Network * net);



/**
 * @brief      ANN's regression test.
 */
void regressionTestANN(void);






#endif