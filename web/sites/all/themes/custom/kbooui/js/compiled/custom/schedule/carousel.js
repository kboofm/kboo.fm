// Generated by CoffeeScript 1.9.3
(function() {
  var bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  window.App.Schedule = window.App.Schedule || {};

  (function($) {
    return App.Schedule.Carousel = (function(superClass) {
      extend(Carousel, superClass);

      function Carousel() {
        this.renderWeek = bind(this.renderWeek, this);
        this.renderDay = bind(this.renderDay, this);
        this.renderEpisode = bind(this.renderEpisode, this);
        this.getWeek = bind(this.getWeek, this);
        this.getDay = bind(this.getDay, this);
        this.getEpisode = bind(this.getEpisode, this);
        this.change = bind(this.change, this);
        this.prev = bind(this.prev, this);
        this.next = bind(this.next, this);
        return Carousel.__super__.constructor.apply(this, arguments);
      }

      Carousel.prototype.nextButton = ".schedule-carousel-next i";

      Carousel.prototype.prevButton = ".schedule-carousel-prev i";

      Carousel.prototype.carousel_timestamp = ".schedule-carousel-timestamp";

      Carousel.prototype.$content = null;

      Carousel.prototype.bind = function() {
        this.bindItem("click", this.nextButton, this.next);
        this.bindItem("click", this.prevButton, this.prev);
        return true;
      };

      Carousel.prototype.next = function(event) {
        this.change(event, "next");
        return true;
      };

      Carousel.prototype.prev = function(event) {
        this.change(event, "prev");
        return true;
      };

      Carousel.prototype.change = function(event, direction) {
        var $button, carousel_id, timestamp, type;
        $button = $(event.target).parent();
        carousel_id = $button.data("carousel");
        this.$content = $("#" + carousel_id);
        timestamp = this.$content.find(this.carousel_timestamp).attr("data-timestamp");
        type = this.$content.attr("data-type");
        if (type === 'episode') {
          this.getEpisode(timestamp, direction);
        }
        if (type === 'day') {
          this.getDay(timestamp, direction);
        }
        if (type === 'week') {
          this.getWeek(timestamp, direction);
        }
        return true;
      };

      Carousel.prototype.getEpisode = function(timestamp, direction) {
        var route;
        route = "station/episode/" + direction + "/" + timestamp;
        $.get(route, this.renderEpisode);
        return true;
      };

      Carousel.prototype.getDay = function(timestamp, direction) {
        var route;
        route = "station/day/" + direction + "/" + timestamp;
        $.get(route, this.renderDay);
        return true;
      };

      Carousel.prototype.getWeek = function(timestamp, direction) {
        return true;
      };

      Carousel.prototype.dataItem = function(item) {
        var data_item;
        data_item = {
          "timestamp": item['start']['timestamp'],
          "schedule-item": {
            "title-link": item['title'],
            "formatted-date": item['start']['formatted_date'],
            "formatted-time": {
              "start-time": item['start']['formatted_time'],
              "finish-time": item['finish']['formatted_time']
            }
          }
        };
        return data_item;
      };

      Carousel.prototype.renderEpisode = function(response) {
        var data, directives;
        if (response.length === 0) {
          return;
        }
        data = this.dataItem(response[0]);
        directives = {
          "schedule-carousel-timestamp": {
            "data-timestamp": function() {
              return "" + this.timestamp;
            }
          }
        };
        this.$content.render(data, directives);
        return true;
      };

      Carousel.prototype.renderDay = function(response) {
        var data, data_item, directives, i, item, len;
        if (response.length === 0) {
          return;
        }
        data = {
          timestamp: response[0]['start']['timestamp'],
          "schedule-items": []
        };
        for (i = 0, len = response.length; i < len; i++) {
          item = response[i];
          data_item = this.dataItem(item);
          data['schedule-items'].push(data_item);
        }
        directives = {
          "schedule-carousel-timestamp": {
            "data-timestamp": function() {
              return "" + this.timestamp;
            }
          }
        };
        this.$content.render(data, directives);
        return true;
      };

      Carousel.prototype.renderWeek = function(response) {
        return true;
      };

      return Carousel;

    })(C4.Components.Base);
  })(jQuery);

}).call(this);
