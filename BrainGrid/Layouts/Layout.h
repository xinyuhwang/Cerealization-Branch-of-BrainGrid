/**
 *      @file Layout.h
 *
 *      @brief The Layout class defines the layout of neurons in neunal networks
 */

/**
 *
 * @class Layout Layout.h "Layout.h"
 *
 * \latexonly  \subsubsection*{Implementation} \endlatexonly
 * \htmlonly   <h3>Implementation</h3> \endhtmlonly
 *
 * The Layout class maintains neurons locations (x, y coordinates), distance of every couple neurons,
 * neurons type map (distribution of excitatory and inhibitory neurons), and starter neurons map
 * (distribution of endogenously active neurons).  
 *
 */

#pragma once

#include "Global.h"
#include "SimulationInfo.h"
#include <vector>
#include <iostream>

//cereal
//total data member: 12
//serialized datamember: 11 (1 not sure)
#include <cereal/types/vector.hpp>
#include <memory> //for smart pointer
#include <cereal/types/memory.hpp> // for smart pointer


using namespace std;

class Layout
{
    public:
        Layout();
        virtual ~Layout();

        /**
         *  Setup the internal structure of the class. 
         *  Allocate memories to store all layout state.
         *
         *  @param  sim_info  SimulationInfo class to read information from.
         */
        virtual void setupLayout(const SimulationInfo *sim_info);

        /**
         *  Checks the number of required parameters to read.
         *
         * @return true if all required parameters were successfully read, false otherwise.
         */
        virtual bool checkNumParameters() = 0;

        /**
         *  Attempts to read parameters from a XML file.
         *
         *  @param  element TiXmlElement to examine.
         *  @return true if successful, false otherwise.
         */
        virtual bool readParameters(const TiXmlElement& element);

        /**
         *  Prints out all parameters of the neurons to ostream.
         *
         *  @param  output  ostream to send output to.
         */
        virtual void printParameters(ostream &output) const;

        /**
         *  Creates a neurons type map.
         *
         *  @param  num_neurons number of the neurons to have in the type map.
         */
        virtual void generateNeuronTypeMap(int num_neurons);

        /**
         *  Populates the starter map.
         *  Selects num_endogenously_active_neurons excitory neurons 
         *  and converts them into starter neurons.
         *
         *  @param  num_neurons number of neurons to have in the map.
         */
        virtual void initStarterMap(const int num_neurons);

        /**
         *  Returns the type of synapse at the given coordinates
         *
         *  @param    src_neuron  integer that points to a Neuron in the type map as a source.
         *  @param    dest_neuron integer that points to a Neuron in the type map as a destination.
         *  @return type of the synapse.
         */
        synapseType synType(const int src_neuron, const int dest_neuron);

        //! Store neuron i's x location.
        BGFLOAT *xloc;

        //! Store neuron i's y location.
        BGFLOAT *yloc;

        // Inter-neuron distance squared. (not used on GPU)
        CompleteMatrix *dist2;

        //! The true inter-neuron distance. (not used on GPU)
        CompleteMatrix *dist;

        //! Probed neurons list.
        vector<int> m_probed_neuron_list;

        //! The neuron type map (INH, EXC).
        neuronType *neuron_type_map;

        //! The starter existence map (T/F).
        bool *starter_map;

        //! Number of endogenously active neurons.
        BGSIZE num_endogenously_active_neurons;

        //Cereal
        template<class Archive>
        void serialize(Archive & archive);

    protected:
        //! Number of parameters read.
        int nParams;

        //! Endogenously active neurons list. 
        vector<int> m_endogenously_active_neuron_list;

        //! Inhibitory neurons list.
        vector<int> m_inhibitory_neuron_layout;

    private:
        /*
         *  Initialize the location maps (xloc and yloc).
         *
         *  @param sim_info   SimulationInfo class to read information from.
         */
        void initNeuronsLocs(const SimulationInfo *sim_info);

        // True if grid layout.
        bool m_grid_layout;
};

//Cereal Archive Method
template<class Archive>
void Layout::serialize(Archive & archive) {
        
        //not sure
        //int nParams;

        shared_ptr<BGFLOAT> spxloc(xloc);
        shared_ptr<BGFLOAT> spyloc(yloc);
        shared_ptr<CompleteMatrix> spdist2(dist2);
        shared_ptr<CompleteMatrix> spdist(dist);

        shared_ptr<neuronType> spneuron_type_map(neuron_type_map);
        shared_ptr<bool> spstarter_map(starter_map);


    archive(spxloc, spyloc, spdist2, spdist, spneuron_type_map, 
    spstarter_map, m_probed_neuron_list, num_endogenously_active_neurons, 
    m_endogenously_active_neuron_list, m_inhibitory_neuron_layout, m_grid_layout
    );

}

