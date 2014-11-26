#include "samplealgorithm.h"

SampleAlgorithm::SampleAlgorithm( Workspace *workspace )
{
    this->workspace = workspace;
}

//An AlgorithmInterface can be destroyed before the algorithm is finised
SampleAlgorithm::~SampleAlgorithm() {
    foreach( Node *node, nodes ) {
        delete node;
    }

    foreach( Edge *edge, edges ) {
        delete edge;
    }
}

//This is guaranteed to be called before the first time next() is called
void SampleAlgorithm::init() {
    highlightid = -1;
    foreach( Node* node, nodes ) {
        if( node->getType() == NodeType::START ) {
            highlightid = node->getID();
            qDebug() << "highlightid: " << highlightid;
            return;
        }
    }
}

//This is called whenever the next button is clicked. The internal state should be updated
bool SampleAlgorithm::next() {
    bool seen = false;
    foreach( Node* node, nodes ) {
        qDebug() << "Node " << node->getID() << "==?" << highlightid;
        if( node->getID() == highlightid ) {
            qDebug() << "found our highlightid";
            seen = true;
        } else if( seen ) {
            qDebug() << "the next node is: " << node->getID();
            highlightid = node->getID();
            return true;
        }
    }
    return false;
}

//This should return the id of the node that should be highlighted
int SampleAlgorithm::getHighlightedNode() {
    return highlightid;
}

//An AlgorithmInterface can accept pushed information about nodes
//This interface shall not manipulate these Nodes in any way or form
void SampleAlgorithm::processNodes( QList<Node*> consnodes ) {
    foreach( Node* node, consnodes ) {
        qDebug() << "node: " << node->getID();
        Node *cnode = node;
        Node* newNode = new Node(cnode->getID(), QPointF(), workspace, cnode->getType());
        newNode->setLabel( cnode->getLabel() );
        nodes.append( newNode );
    }
}

//An AlgorithmInterface can accept pushed information about edges
//This interface shall not manipulate these Edges in any way or form
void SampleAlgorithm::processEdges( QList<Edge*> consedges ) {
    foreach( Edge* edge, consedges ) {
        qDebug() << "edge: " << edge->getID();
        Edge *cedge = edge;
        Edge* newEdge = new Edge(cedge->getID(),findNodeByID(cedge->getBeginNode()->getID()),findNodeByID(cedge->getEndNode()->getID()),workspace);
        newEdge->setLabel(cedge->getLabel(true),true);
        if( cedge->getBidirectional() ) {
            newEdge->setBidirectional(true);
            newEdge->setLabel(cedge->getLabel(false),false);
        }
        edges.append( newEdge );
    }
}

Node* SampleAlgorithm::findNodeByID( int id ) {
    foreach( Node *node, nodes ) {
        if( node->getID() == id ) {
            return node;
        }
    }
    return NULL;
}
