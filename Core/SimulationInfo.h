/**
 *      @file SimulationInfo.h
 *
 *      @brief Header file for SimulationInfo.
 */
//! Simulation information.

/**
 ** \class SimulationInfo SimulationInfo.h "SimulationInfo.h"
 **
 ** \latexonly  \subsubsection*{Implementation} \endlatexonly
 ** \htmlonly   <h3>Implementation</h3> \endhtmlonly
 **
 ** The SimulationInfo contains all information necessary for the simulation.
 **
 ** \latexonly  \subsubsection*{Credits} \endlatexonly
 ** \htmlonly   <h3>Credits</h3> \endhtmlonly
 **
 ** Some models in this simulator is a rewrite of CSIM (2006) and other 
 ** work (Stiber and Kawasaki (2007?))
 **
 **
 **     @author Allan Ortiz & Cory Mayberry
 **/

#pragma once

#ifndef _SIMULATIONINFO_H_
#define _SIMULATIONINFO_H_

#include "Global.h"

class IModel;
class IRecorder;
class ISInput;
#ifdef PERFORMANCE_METRICS
// Home-brewed performance measurement
#include "Timer.h"
#endif

//cereal
//total data member: 22 (-2 deleted) Note: 2 data member name changed
//serialized datamember: 16
#include <cereal/types/string.hpp> //for string type data member
#include <cereal/types/polymorphic.hpp> //for inheritance
#include <memory> //for smart pointer
#include <cereal/types/memory.hpp> // for smart pointer

//! Class design to hold all of the parameters of the simulation.
class SimulationInfo : public TiXmlVisitor
{
public:
        SimulationInfo() :
            width(0),
            height(0),
            totalNeurons(0),
            currentStep(0),
            maxSteps(0),
            epochDuration(0),
            maxFiringRate(0),
            maxSynapsesPerNeuron(0),
            minSynapticTransDelay(MIN_SYNAPTIC_TRANS_DELAY), 
            deltaT(DEFAULT_dt),
            maxRate(0),
	        seed(0),
            numClusters(0),
            model(NULL),
            simRecorder(NULL),
            pInput(NULL)
        {
        }

        virtual ~SimulationInfo() {}

        /**
         *  Attempts to read parameters from a XML file.
         *
         *  @param  simDoc  the TiXmlDocument to read from.
         *  @return true if successful, false otherwise.
         */
        bool readParameters(TiXmlDocument* simDoc);

        /**
         *  Prints out loaded parameters to ostream.
         *
         *  @param  output  ostream to send output to.
         */
        void printParameters(ostream &output) const;

        //Cereal
        template<class Archive>
        void serialize(Archive & archive);

    protected:
        using TiXmlVisitor::VisitEnter;

        /*
         *  Handles loading of parameters using tinyxml from the parameter file.
         *
         *  @param  element TiXmlElement to examine.
         *  @param  firstAttribute  ***NOT USED***.
         *  @return true if method finishes without errors.
         */
        virtual bool VisitEnter(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);

    public:

	//! Width of neuron map (assumes square)
	int width;

	//! Height of neuron map
	int height;

	//! Count of neurons in the simulation
	int totalNeurons;

	//! Current simulation step
	int currentStep;

	//! Maximum number of simulation steps
	int maxSteps; // TODO: delete

	//! The length of each step in simulation time
	BGFLOAT epochDuration; // Epoch duration !!!!!!!!

	//! Maximum firing rate. **Only used by GPU simulation.**
	int maxFiringRate;

	//! Maximum number of synapses per neuron. **Only used by GPU simulation.**
	int maxSynapsesPerNeuron;

    //! The synaptic transmission delay (minimum), descretized into time steps
    int minSynapticTransDelay;

	//! Time elapsed between the beginning and end of the simulation step
	BGFLOAT deltaT; // Inner Simulation Step Duration !!!!!!!!

	//! growth variable (m_targetRate / m_epsilon) TODO: more detail here
	BGFLOAT maxRate;

	//! Seed used for the simulation random SINGLE THREADED
	long seed;

    //! Number of clusters.
    int numClusters;

    //! File name of the simulation results.
    string resultOutputFileName;
    //string stateOutputFileName;

    //! File name of the parameter description file.
    string resultInputFileName;
    //string stateInputFileName;

    //! File name of the memory dump output file.
    //Deleted it due to Cereal implementation
    //string memOutputFileName;

    //! File name of the memory dump input file.
    //Deleted it due to Cereal implementation
    //string memInputFileName;

    //! File name of the stimulus input file.
    string stimulusInputFileName;

    //! Neural Network Model interface.
    //link to object
    IModel *model;

    //! Recorder object.
    IRecorder* simRecorder;

    //! Stimulus input object.
    ISInput* pInput;
    
#ifdef PERFORMANCE_METRICS
        /**
         * Timer for measuring performance of an epoch.
         */
        Timer timer;
        /**
         * Timer for measuring performance of connection update.
         */
        Timer short_timer;
#endif

    private:
        /**
         *  Checks the number of required parameters to read.
         *
         *  @return true if all required parameters were successfully read, false otherwise.
         */
        virtual bool checkNumParameters();

        //! Number of parameters read.
        int nParams;
};

//Cereal Archive Method
template<class Archive>
void SimulationInfo::serialize(Archive & archive) {

    shared_ptr<IModel> spmodel(model);
    shared_ptr<IRecorder>spsimRecorder(simRecorder);
    shared_ptr<ISInput> sppInput(pInput);

    archive(CEREAL_NVP(width),height, totalNeurons, currentStep, maxSteps,
    epochDuration, maxFiringRate, maxSynapsesPerNeuron, minSynapticTransDelay, deltaT,
    maxRate, seed, numClusters, spmodel, spsimRecorder, sppInput
    );
}

//Cereal
CEREAL_REGISTER_TYPE(SimulationInfo)
CEREAL_REGISTER_POLYMORPHIC_RELATION(TiXmlVisitor,SimulationInfo)

#endif // _SIMULATIONINFO_H_
