var map = {};
({
  init: function (nodes, edges) {
    algorithm.debug("initializing algorithm");
    var i, j, edge;
    for (i = 0; i < nodes.length; i++) {
      map[nodes[i]] = [];
    }
    for (j = 0; j < edges.length; j++) {
      edge = edges[j];
      map[edge[0]].push(edge[1]);
    }
    algorithm.debug(JSON.stringify(map));
  },
})