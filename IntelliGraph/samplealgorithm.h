#ifndef SAMPLEALGORITHM_H
#define SAMPLEALGORITHM_H

#include <QList>

#include "algorithminterface.h"
#include "workspace.h"

class SampleAlgorithm: public AlgorithmInterface
{
public:
    SampleAlgorithm(Workspace *workspace);

    //An AlgorithmInterface can be destroyed before the algorithm is finised
    ~SampleAlgorithm();

    //This is guaranteed to be called before the first time next() is called
    void init();

    //This is called whenever the next button is clicked. The internal state should be updated
    bool next();

    //This should return the id of the node that should be highlighted
    int getHighlightedNode();

    //An AlgorithmInterface can accept pushed information about nodes
    //This interface shall not manipulate these Nodes in any way or form
    void processNodes( QList<Node*> consnodes);

    //An AlgorithmInterface can accept pushed information about edges
    //This interface shall not manipulate these Edges in any way or form
    void processEdges( QList<Edge*> consedges );

private:
    QList<Node*> nodes;
    QList<Edge*> edges;
    Workspace *workspace;

    int highlightid;

    Node *findNodeByID( int id );
};

#endif // SAMPLEALGORITHM_H
