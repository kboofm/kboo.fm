// Generated by CoffeeScript 1.10.0
(function() {
  var bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  (function($) {
    return App.Station.Playlists = (function(superClass) {
      extend(Playlists, superClass);

      function Playlists() {
        this.renderOnAir = bind(this.renderOnAir, this);
        this.renderHeader = bind(this.renderHeader, this);
        this.refresh = bind(this.refresh, this);
        this.init = bind(this.init, this);
        return Playlists.__super__.constructor.apply(this, arguments);
      }

      Playlists.prototype.$el = null;

      Playlists.prototype.route = "/api/playlists";

      Playlists.prototype.init = function() {
        Playlists.__super__.init.call(this);
        this.$el = $(".playlists");
        this.renderHeader();
        C4.Utilities.Timer.delay(this.refresh, 1000, "playlists_init");
        return true;
      };

      Playlists.prototype.refresh = function() {
        jQuery.get(this.route, this.renderOnAir);
        return true;
      };

      Playlists.prototype.renderHeader = function() {
        var template_data;
        template_data = [
          {
            col: "Artist"
          }, {
            col: "Title"
          }, {
            col: "Album"
          }, {
            col: "Time"
          }
        ];
        this.$el.find("thead tr").render(template_data);
        return true;
      };

      Playlists.prototype.renderOnAir = function(response) {
        var i, j, len, len1, playlist, ref, template_data, track;
        if (response.length === 0) {
          return;
        }
        template_data = [];
        for (i = 0, len = response.length; i < len; i++) {
          playlist = response[i];
          ref = playlist["Songs"];
          for (j = 0, len1 = ref.length; j < len1; j++) {
            track = ref[j];
            template_data.push({
              artist: track["ArtistName"],
              title: track["SongName"],
              album: track["DiskName"],
              time: track["Timestamp"]
            });
          }
        }
        this.$el.find("tbody").render(template_data);
        template_data = {
          throbber: ""
        };
        this.$el.render(template_data);
        return true;
      };

      $(function() {
        new App.Station.Playlists();
        return true;
      });

      return Playlists;

    })(C4.Components.Base);
  })(jQuery);

}).call(this);
