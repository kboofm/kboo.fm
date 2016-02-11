(($) ->
  class App.Station.Carousel extends C4.Components.Base
    nextButton: ".schedule-carousel-next .schedule-trigger"
    prevButton: ".schedule-carousel-prev .schedule-trigger"
    carousel_timestamp: ".schedule-carousel-timestamp"
    $carousel: null
    $toolbar: null
    stream: null
    type: null
    timestamp: null

    bind: ->
      @bindItem "click", @nextButton, @next
      @bindItem "click", @prevButton, @prev
      true

    next: (event) =>
      @change event, "next"
      true

    prev: (event) =>
      @change event, "prev"
      true

    getCarousel: (event) =>
      $button = $(event.target).parent()
      @$toolbar = $button.parent()
      carousel_id = $button.data "carousel"
      @$carousel = $ "##{carousel_id}"

      @timestamp = @$carousel
      .find @carousel_timestamp
      .attr "data-timestamp"

      @type = @$carousel.attr "data-type"
      @stream = @$carousel.attr "data-stream"
      @stream = encodeURIComponent @stream
      true

    change: (event, direction) =>
      @getCarousel event
      route = "/api/schedule/#{@type}/#{@stream}/#{direction}/#{@timestamp}"

      @getEpisode route if @type == 'episode'
      @getDay route if @type == 'day'
      @getWeek route if @type == 'week'
      true

    getEpisode: (route) =>
      jQuery.get route, @renderEpisode
      true

    getDay: (route) =>
      jQuery.get route, @renderDay
      true

    getWeek: (route) =>
      jQuery.get route, @renderWeek
      true

    dataItem: (item) ->
      data_item =
        "title-link": item['title']
        "formatted-date": item['start']['formatted_date']
        "formatted-time":
          "start-time": item['start']['formatted_time']
          "finish-time": item['finish']['formatted_time']

      data_item

    renderToolbar: (start, showTime = false) =>
      datetime = start['formatted_date']

      if showTime
        datetime = "#{datetime} #{start['formatted_time']}"

      data =
        datetime: datetime
      @$toolbar.render data

    renderEpisode: (response) =>
      return if response.length == 0

      start = response[0]['start']
      data =
        timestamp: start['timestamp']
        "schedule-item": [@dataItem response[0]]

      directives =
        "schedule-carousel-timestamp":
          "data-timestamp": -> "#{@timestamp}"

      @$carousel.render data, directives

      @renderToolbar start, true
      true

    renderDay: (response) =>
      return if response.length == 0

      start = response[0]['start']
      data =
        timestamp: start['timestamp']
        "schedule-item": @dataItem item for item in response

      directives =
        "schedule-carousel-timestamp":
          "data-timestamp": -> "#{@timestamp}"

      @$carousel.find('.cull').remove()
      @$carousel.render data, directives

      @renderToolbar start
      true

    renderWeek: (response) =>
      return if response.length == 0

      week_start = null
      weekdays = []
      for weekday of response
        timestamp = response[weekday][0]['start']['timestamp']

        if not week_start
          week_start = response[weekday][0]['start']

        weekdata =
          "schedule-dayofweek": weekday
          "schedule-item": @dataItem item for item in response[weekday]
        weekdays.push weekdata

      container =
        weekdays: weekdays
        timestamp: week_start['timestamp']

      directives =
        "schedule-carousel-timestamp":
          "data-timestamp": -> "#{@timestamp}"

      @$carousel.find('.cull').remove()
      @$carousel.render container, directives
      @renderToolbar week_start
      true

  $ ->
    new App.Station.Carousel()
    true
) jQuery
