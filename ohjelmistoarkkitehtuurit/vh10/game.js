
Game = {
  h: 350,
  w: 500,
  width: function() {
    return this.h;
  },
  height: function() {
    return this.w;
  },
  start: function() {
    Crafty.init(500,350);
    Crafty.scene("Start");
  }
};
