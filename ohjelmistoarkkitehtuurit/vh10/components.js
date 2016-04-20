Crafty.c("GameObject", {
  init: function() {
    this.addComponent("2D, Canvas, Color, Collision");
  },
  place: function(x, y) {
    this.x = x;
    this.y = y;
    return this;
  }
});

Crafty.c("Player", {
  init: function() {
    this.addComponent("GameObject, Twoway, Gravity, Keyboard");
    this.w = 10;
    this.h = 10;
    this.gravity("Floor");
    this.twoway(100);
    this.color("black");
    this.direction = 1;
    this.checkHits("Enemy");
  },

  events: {
    "KeyDown": function(e) {
      if (e.key == Crafty.keys.LEFT_ARROW) {
        this.direction = -1;
      }
      else if (e.key == Crafty.keys.RIGHT_ARROW) {
        this.direction = 1;
      }
      else if (e.key == Crafty.keys.SPACE) {
        Crafty.e("Bullet").place(this.x, this.y).setDir(this.direction);
      }
    },
    "HitOn": function(hitData) {
      Crafty.trigger("Dead", this);
    }
  }

});

Crafty.c("Goal", {
  init: function() {
    this.addComponent("GameObject");
    this.checkHits("Player");
    this.w = 10;
    this.h = 10;
    this.color("blue");
  },

  events: {
    "HitOn": function(hitData) {
      Crafty.trigger("Victory", this);
    }
  }
});

Crafty.c("Platform", {
  init: function() {
    this.addComponent("GameObject, Floor");
    this.color("green");
  },
  size: function(w, h) {
    this.w = w;
    this.h = h;
  }
});

Crafty.c("Bullet", {
  init: function() {
    this.addComponent('GameObject, Motion');
    this.w = 5;
    this.h = 5;
    this.color("green");
  },
  setDir: function(dir) {
    this.velocity().x = 100 * dir;
    return this;
  }
});

Crafty.c("Enemy", {
  init: function() {
    this.addComponent("GameObject, Motion, Gravity");
    this.h = 12;
    this.w = 8;
    this.color("red");
    this.checkHits("Bullet, Floor");
    this.gravity("Floor");
    this.velocity().x = 20;
  },
  setBounds: function(left, right) {
    this.rightBound = right;
    this.leftBound = left;
    return this;
  },
  events: {
    "HitOn": function(hitData) {
      var t = this;
      hitData.forEach(function(hit) {
        if (hit.obj.has("Bullet")) {
          hit.obj.destroy();
          t.destroy();
        }
      });
    },
    "EnterFrame": function(eventData) {
      if (this.rightBound - this.x < 5 || this.x - this.leftBound < 5) {
        this.velocity().x *= -1;
      }
    }
  }
});
