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
        virtual void init();

        //This is called whenever the next button is clicked. The internal state should be updated
        virtual bool next();

        //This should return the id of the node that should be highlighted
        virtual int getHighlightedNode();

        //An AlgorithmInterface can accept pushed information about nodes
        //This interface shall not manipulate these Nodes in any way or form
        virtual void processNodes( const QList<const Node*> ) const;

        //An AlgorithmInterface can accept pushed information about edges
        //This interface shall not manipulate these Edges in any way or form
        virtual void processEdges( const QList<const Edge*> ) const;
};

#endif // ALGORITHMINTERFACE_H
