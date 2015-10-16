window.App.Schedule = window.App.Schedule || {}

(($) ->
    class App.Schedule.Carousel extends C4.Components.Base
        next: ".schedule-carousel-next"
        prev: ".schedule-carousel-prev"
        carousel_timestamp: ".schedule-carousel-timestamp"
        carousel_content: ".schedule-carousel-content"
        $content: null

        bind: ->
            @bindItem "click", @next, @nextItem
            @bindItem "click", @prev, @prevItem
            true

        renderScheduleItem: (response) =>
            return if response.length == 0

            data =
                "timestamp": response.start.timestamp
                "schedule-item":
                    "title-link": response.title
                    "formatted-date": response.start.formatted_date
                    "formatted-time":
                        "start-time": response.start.formatted_time
                        "finish-time": response.finish.formatted_time

            directives =
                "schedule-carousel-timestamp":
                    "data-timestamp": -> "#{@timestamp}"

            @$content.render data, directives
            true

        getEpisode: (timestamp, direction) =>
            route = "station/episode/#{direction}/#{timestamp}"
            $.get route, @renderScheduleItem

        nextItem: (event) =>
            @$content = $(event.target).parent().find(@carousel_content)
            timestamp = @$content.find(@carousel_timestamp).data "timestamp"
            @getEpisode timestamp, 'next'
            true

        prevItem: (event) =>
            @$content = $(event.target).parent().find(@carousel_content)
            timestamp = @$content.find(@carousel_timestamp).data "timestamp"
            @getEpisode timestamp, 'prev'
            true
) jQuery
