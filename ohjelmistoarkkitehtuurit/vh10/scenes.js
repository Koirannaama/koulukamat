Crafty.scene("Start", function() {
  Crafty.e('2D, DOM, Text')
		.text('Peli! (paina jotain nappia)')
		.attr({ x: 100, y: 100, w: 100, h: 100 });

  this.startGame = function() {
    console.log("Key pressed in start");
    Crafty.scene("Level 1");
  };
  Crafty.bind("KeyDown", this.startGame);
}, function() {
  this.unbind("KeyDown", this.startGame);
});

Crafty.scene("Level 1", function() {
  Crafty.e("Player").place(0,50);
  Crafty.e("Platform").place(0, 100).size(100, 10);
  Crafty.e("Enemy").place(70, 90).setBounds(0, 100);
  Crafty.e("Enemy").place(30, 90).setBounds(0, 100);

  Crafty.e("Platform").place(125, 100).size(100, 10);
  Crafty.e("Enemy").place(170, 50).setBounds(125, 175);
  Crafty.e("Enemy").place(180, 50).setBounds(175, 225);

  Crafty.e("Platform").place(115, 130).size(50, 10);
  Crafty.e("Goal").place(120, 120);

  Crafty.e("Platform").place(60, 170).size(50, 10);
  Crafty.e("Enemy").place(70, 115).setBounds(60, 110);

  this.bind("Dead", function() {
    Crafty.scene("Level 1");
  });
  this.bind("Victory", function() {
    Crafty.scene("Start");
  });
});
