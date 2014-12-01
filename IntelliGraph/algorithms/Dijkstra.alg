var map = {}, distance = {}, ids = {};
var startNode, goalNode, previous = {};
var inf = Number.POSITIVE_INFINITY;
var path = [], currentPathNode = 0;

function run(node) {
  var neighbors = map[node];
  var i, len, neighbor;
  for (i = 0; i < neighbors.length; i++) {
    neighbor = neighbors[i];
    len = distance[node] + neighbor[1];
    if (len < distance[neighbor[0]]) {
      distance[neighbor[0]] = len;
      previous[neighbor[0]] = node;
      run(neighbor[0]);
    }
  }
}

function walkPath() {
  var tmp = [], n;
  n = goalNode;
  while (n != startNode) {
    tmp.push(n);
    n = previous[n];
  }
  tmp.push(startNode);
  path = tmp.reverse();
}

({
  init: function (nodes, edges) {
    algorithm.debug("initializing algorithm");
    var i, j, edge;
    ids = nodes;
    for (i = 0; i < nodes.length; i++) {
      map[nodes[i]] = [];
      distance[nodes[i]] = inf;
    }
    for (j = 0; j < edges.length; j++) {
      edge = edges[j];
      map[edge[0]].push([edge[1], edge[2]]);
    }
    algorithm.debug(JSON.stringify(map));
  },
  start: function (start, end) {
    algorithm.debug("algortithm start");
    startNode = start;
    goalNode = end;
    distance[startNode] = 0;
    // start algorithm
    run(startNode);
    // get shortest path
    walkPath();
    algorithm.debug(JSON.stringify(path));
  },
  next: function () {
    algorithm.debug("Highlighting: "+path[currentPathNode]);
    algorithm.highlightNode(path[currentPathNode]);
    algorithm.highlightNode(path[currentPathNode]);
    if (currentPathNode < path.length) {
      currentPathNode++;
      return true;
    } else {
      return false;
    }
  },
})
