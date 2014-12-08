var map, distance, nodes, previous, visited;
var currentNode, startNode, goalNode;
var edgeIterator, lastEdge;

({
  init: function(start, end) {
    console.setName("Dijkstra");
    console.log("initializing algorithm");
    // initialize vars
    var edges = console.getEdges();
    nodes = console.getNodes();
    map = {}; distance = {}; visited = {};
    previous = {}; to_visit = [];
    currentNode = start;
    startNode = start;
    goalNode = end;
    // initialize map
    var i, j, edge;
    for (i = 0; i < nodes.length; i++) {
      map[nodes[i]] = [];
      distance[nodes[i]] = Number.POSITIVE_INFINITY;
      visited[nodes[i]] = false;
      console.setLabel(i, "infinity");
    }
    for (j = 0; j < edges.length; j++) {
      edge = edges[j];
      map[edge[0]].push([edge[1], edge[2]]);
    }
    // highlight first node
    edgeIterator = 0;
    lastEdge = false;
    distance[currentNode] = 0;
    visited[currentNode] = true;
    console.highlightColor(255, 0, 0);
    console.highlightNode(currentNode);
    console.setLabel(currentNode, 0);
  },
  next: function() {
    if (map.hasOwnProperty(currentNode)) {
      var connected = map[currentNode];
      if (edgeIterator < connected.length) {
        var e = connected[edgeIterator];
        // clear old highlights
        if (lastEdge !== false) {
          console.removeHighlightNode(lastEdge[0]);
          console.removeHighlightNode(lastEdge[1]);
          console.removeHighlightEdge(lastEdge[0], lastEdge[1]);
        }
        // highlight
        console.highlightNode(currentNode);
        console.highlightNode(e[0]);
        console.highlightEdge(currentNode, e[0]); 
        // algorithm
        var len = distance[currentNode] + e[1];
        if (len < distance[e[0]]) {
          console.setLabel(e[0], len);
          distance[e[0]] = len;
          previous[e[0]] = currentNode;
        }
        // update loop vars
        lastEdge = [currentNode, e[0]];
        edgeIterator++;
      } 
      if (edgeIterator == connected.length) {
        var minD = Number.POSITIVE_INFINITY, minN = false, n, i;
        // find next node
        visited[currentNode] = true;
        for (i = 0; i < nodes.length; i++) {
          n = nodes[i];
          if (distance[n] < minD && !visited[n]) {
            minN = n;
            minD = distance[n];
          }
        }
        // if no new node
        if (minN === false) {
          // clear old highlights
          if (lastEdge !== false) {
            console.removeHighlightNode(lastEdge[0]);
            console.removeHighlightNode(lastEdge[1]);
            console.removeHighlightEdge(lastEdge[0], lastEdge[1]);
          }
          // show optimal path
          n = goalNode;
          while (n != startNode) {
            console.highlightNode(n);
            console.highlightEdge(n, previous[n]);
            n = previous[n];
          }
        } else {
          currentNode = minN;
          edgeIterator = 0;
        }
      }
    }
  },
})