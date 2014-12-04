var map = {}, distance = {}, ids = {};
var startNode, goalNode, previous = {};

function dijkstra(node) {
  var neighbors = map[node];
  var i, len, neighbor;
  for (i = 0; i < neighbors.length; i++) {
    neighbor = neighbors[i];
    len = distance[node] + neighbor[1];
    if (len < distance[neighbor[0]]) {
      distance[neighbor[0]] = len;
      previous[neighbor[0]] = node;
      dijkstra(neighbor[0]);
    }
  }
}

function walkPath() {
  var tmp = [], path = [];
  var n = goalNode;
  while (n != startNode) {
    if( tmp.indexOf( n ) != -1 ) {
      path = null;
      return;
    }
    tmp.push(n);
    n = previous[n];
  }
  tmp.push(startNode);
  path = tmp.reverse();
  console.log(JSON.stringify(path));
  return path;
}

({
  init: function (nodes, edges) {
    // resetting vars
    map = {}; distance = {}; 
    ids = {}; previous = {};
    
    console.log("initializing algorithm");
    var i, j, edge;
    ids = nodes;
    for (i = 0; i < nodes.length; i++) {
      map[nodes[i]] = [];
      distance[nodes[i]] = Number.POSITIVE_INFINITY;
    }
    for (j = 0; j < edges.length; j++) {
      edge = edges[j];
      map[edge[0]].push([edge[1], edge[2]]);
    }
    console.log(JSON.stringify(map));
  },
  run: function (start, end) {
    console.log("algortithm start");
    startNode = start;
    goalNode = end;
    distance[startNode] = 0;
    // start algorithm
    dijkstra(startNode);
    // get shortest path
    return walkPath();
  },
})
