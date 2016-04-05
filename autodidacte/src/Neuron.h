 #ifndef H_MG_NEURON
 #define H_MG_NEURON


  /* Neuron.h   -----   LIF7 Auto-Didacte */



enum{	INPUT , HIDDEN , OUTPUT   };


/* Neuron structure */


/**
 *  @struct Neuron
 *  @brief The basic entities of Neural Network.
 */
typedef struct
{

    int type; /**< The type of the Neuron (can be INPUT, HIDDEN or OUTPUT).*/
    float value; /**< The value the Neuron is at.*/
    int nbWeights; /**< The number of weights the Neuron has. (depends on the number of neurons in the next layer).*/
    float * tabWeights; /**< Adress of the Neuron's array of weights, of size nbWeights. */

} Neuron;



/* ----- Neuron constructors ----- */

/**
 * @brief      Creates a new Input Neuron.
 *
 * @param[in]  nbHiddenNeuron  The number of weights the Neuron will have.
 *
 * @return     New neuron's adress.
 */
Neuron * newInputNeuron(int nbHiddenNeuron);

/**
 * @brief      Creates a new Hidden Neuron.
 *
 * @param[in]  nbOutputNeuron  The number of weights the Neuron will have.
 *
 * @return     New neuron's adress.
 */
Neuron * newHiddenNeuron(int nbOutputNeuron);

/**
 * @brief      Creates a new Output Neuron. These one don't have weights.
 *
 * @return     New neuron's adress.
 */
Neuron * newOutputNeuron(void);




/* ----- Neuron get/set ----- */

/**
 * @brief      Get the value.
 *
 * @param[in]  neuron  Neuron's adress.
 *
 * @return     Neuron's value.
 */
float getValue(const Neuron * neuron);

/**
 * @brief      Set the value.
 *
 * @param[in,out]      neuron    Neuron's adress.	
 * @param[in]  newValue  Neuron's new value.
 */
void  setValue(Neuron * neuron, float newValue);


/**
 * @brief      Get the weight.
 *
 * @param[in]  neuron  Neuron's adress.
 * @param[in]  i       Weight's index.
 *
 * @return     Ith weight's value.
 */
float getWeight(const Neuron * neuron, int i);

/**
 * @brief      Set the weight.
 *
 * @param[in,out]      neuron     Neuron's adress.
 * @param[in]  i          Weight's index.
 * @param[in]  newWeight  Ith weight's new value.
 */
void  setWeight(Neuron * neuron, int i, float newWeight);


/**
 * @brief      Get the type.
 *
 * @param[in]  neuron  Neuron's adress.
 *
 * @return     Neuron's type.
 */
int getTypeNeuron(const Neuron * neuron);

/**
 * @brief      Set the type.
 *
 * @param[in,out]      neuron   Neuron's adress.
 * @param[in]  newType  Neuron's new type.
 */
void setTypeNeuron(Neuron * neuron, int newType);



/**
 * @brief      Get the nb of weights.
 *
 * @param[in]  neuron  Neuron's adress.
 *
 * @return     Neuron's number of weights.
 */
int getNbWeights(const Neuron * neuron);

/**
 * @brief      Set the nb of weights.
 *
 * @param[in,out]      neuron        Neuron's adress.
 * @param[in]  newNbWeights  Neuron's new number of weights.
 */
void setNbWeights(Neuron * neuron,int newNbWeights);





/* ----- Neuron destructor ----- */


/**
 * @brief      Deletes the Neuron.
 *
 * @param[in,out]      neuron  Neuron's adress.
 */
void deleteNeuron(Neuron * neuron);

#endif
