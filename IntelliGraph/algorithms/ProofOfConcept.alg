({
  data: {},
  i: 0,
  init: function () {
    this.data = JSON.parse(arguments[0]);
    this.i = 0; 
    return "parsed " + this.data.length + " nodes";
  },
  next: function () {
    var j = this.i;
    if (j < this.data.length) {
      this.i++;
      return this.data[j].id;
    } else {
      return -1;
    }
  },
})