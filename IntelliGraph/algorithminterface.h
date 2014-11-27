#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

//This is an interface
//This means you can't instantiate this class
//Anything that derives from this class should implement every method defined here

#include "node.h"
#include "edge.h"

class AlgorithmInterface {
    public:
        //An AlgorithmInterface can be destroyed before the algorithm is finised
        virtual ~AlgorithmInterface() {}

        //This is guaranteed to be called before the first time next() is called
        virtual void init() = 0;

        //This is called whenever the next button is clicked. The internal state should be updated
        virtual bool next() = 0;

        //This should return the id of the node that should be highlighted
        virtual int getHighlightedNode() = 0;

        //An AlgorithmInterface can accept pushed information about nodes
        //This interface shall not manipulate these Nodes in any way or form
        virtual void processNodes( QList<Node*> ) = 0;

        //An AlgorithmInterface can accept pushed information about edges
        //This interface shall not manipulate these Edges in any way or form
        virtual void processEdges( QList<Edge*> ) = 0;
};

#endif // ALGORITHMINTERFACE_H
