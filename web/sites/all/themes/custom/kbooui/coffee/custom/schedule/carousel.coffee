window.App.Schedule = window.App.Schedule || {}

(($) ->
    class App.Schedule.Carousel extends C4.Components.Base
        next: ".schedule-carousel-next"
        prev: ".schedule-carousel-prev"
        schedule_item: ".schedule-item"
        title_link: ".schedule-item-title-link"

        bind: ->
            @bindItem "click", @next, @nextItem
            @bindItem "click", @prev, @prevItem
            true

        renderScheduleItem: ($schedule_item, data) ->
            true

        getEpisode: ($schedule_item, timestamp, direction) ->
            route = "station/episode/#{direction}/#{timestamp}"
            $.get route, (response) ->
                console.dir response

#            data =
#                "schedule-item-title-link": timestamp
#
#            $schedule_item.render data

        nextItem: (event) =>
            $schedule_item = $(event.target).prev()
            timestamp = $schedule_item.data "timestamp"
            @getEpisode $schedule_item, timestamp, 'next'
            true

        prevItem: (event) =>
            $schedule_item = $(event.target).next()
            timestamp = $schedule_item.data "timestamp"
            @getEpisode $schedule_item, timestamp, 'prev'
            true
) jQuery
