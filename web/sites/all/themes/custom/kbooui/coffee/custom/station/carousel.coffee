(($) ->
  class App.Station.Carousel extends C4.Components.Base
    nextButton: ".schedule-carousel-next .schedule-trigger"
    prevButton: ".schedule-carousel-prev .schedule-trigger"
    carouselTimestamp: ".schedule-carousel-timestamp"
    $carousel: null
    $toolbar: null
    $triggers: null
    enabled: true
    stream: null
    type: null
    timestamp: null

    init: ->
      super()
      @$triggers =
        "next": $("#tabs-schedule").find ".schedule-carousel-next .schedule-trigger"
        "prev": $("#tabs-schedule").find ".schedule-carousel-prev .schedule-trigger"

    bind: ->
      @bindItem "click", @nextButton, @next
      @bindItem "click", @prevButton, @prev

    next: (event) =>
      @change event, "next"

    prev: (event) =>
      @change event, "prev"

    change: (event, direction) =>
      return unless @enabled
      @disableTriggers()
      @getCarousel event
      route = "/api/schedule/#{@type}/#{@stream}/#{direction}/#{@timestamp}"
      jQuery.get route, @renderSchedule

    getCarousel: (event) =>
      $button = $(event.target).parent()
      @$toolbar = $button.parent()
      carouselId = $button.data "carousel"
      @$carousel = $ "##{carouselId}"

      @timestamp = @$carousel
        .find @carouselTimestamp
        .attr "data-timestamp"

      @type = @$carousel.attr "data-type"
      @stream = @$carousel.attr "data-stream"

    disableTriggers: () ->
      @enabled = false

      @$triggers["next"]
        .removeClass "fa-arrow-right cursor-pointer"
        .addClass "fa-spinner fa-spin"

      @$triggers["prev"]
        .removeClass "fa-arrow-left cursor-pointer"
        .addClass "fa-spinner fa-spin"

    enableTriggers: () ->
      @enabled = true

      @$triggers["next"]
        .removeClass "fa-spinner fa-spin"
        .addClass "fa-arrow-right cursor-pointer"

      @$triggers["prev"]
        .removeClass "fa-spinner fa-spin"
        .addClass "fa-arrow-left cursor-pointer"

    dataItem: (item) ->
      return {} =
        "program":
          "text": item['title']
          "href": item['url']
        "formatted-date": item['start']['formatted_date']
        "formatted-time":
          "start-time": item['start']['formatted_time']
          "finish-time": item['finish']['formatted_time']

    getDirectives: ->
      return {} =
        "schedule-carousel-timestamp":
          "data-timestamp": -> "#{@timestamp}"
        "schedule-item":
          "title-link":
            "text": -> @program.text
            "href": -> @program.href

    renderToolbar: (start, showTime = false) =>
      datetime = start['formatted_date']

      if showTime
        datetime = "#{datetime} #{start['formatted_time']}"

      data =
        datetime: datetime
      @$toolbar.render data

    renderSchedule: (response) =>
      return if response.length == 0

      @renderEpisode response if @type == "episode"
      @renderDay response if @type == "day"
      @renderWeek response if @type == "week"
      @enableTriggers()

    renderEpisode: (response) =>
      start = response[0]["start"]
      data =
        timestamp: start["timestamp"]
        "schedule-item": [@dataItem response[0]]

      @$carousel.render data, @getDirectives()
      @renderToolbar start, true

    renderDay: (response) =>
      start = response[0]["start"]
      data =
        timestamp: start["timestamp"]
        "schedule-item": @dataItem item for item in response

      @$carousel
        .find ".cull"
        .remove()

      @$carousel.render data, @getDirectives()
      @renderToolbar start

    renderWeek: (response) =>
      weekStart = null

      for weekday, data of response
        unless weekStart?
          weekStart = data[0]["start"]

        $target = @$carousel.find ".weekday-#{weekday.toLowerCase()}"

        $target
          .find '.cull'
          .remove()

        templateData = (@dataItem item for item in data)

        directives =
          "title-link":
            "text": -> @program.text
            "href": -> @program.href

        $target.render templateData, directives

      templateData =
        timestamp: weekStart["timestamp"]

      directives =
        "schedule-carousel-timestamp":
          "data-timestamp": -> "#{@timestamp}"

      @$carousel.render templateData, directives
      @renderToolbar weekStart

  $ ->
    new App.Station.Carousel()
    true
) jQuery
