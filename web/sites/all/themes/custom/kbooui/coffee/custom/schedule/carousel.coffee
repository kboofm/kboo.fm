window.App.Schedule = window.App.Schedule || {}

(($) ->
    class App.Schedule.Carousel extends C4.Components.Base
        next: ".schedule-carousel-next"
        prev: ".schedule-carousel-prev"
        schedule_item: ".schedule-item"
        title_link: ".title-link"
        $content: null

        bind: ->
            @bindItem "click", @next, @nextItem
            @bindItem "click", @prev, @prevItem
            true

        renderScheduleItem: (response) =>
            data =
                "schedule-item":
                    "title-link": response['title']
                    "formatted-date": response['start']['formatted_date']
                    "formatted-time": response['start']['formatted_time']

            @$content.render data
            true

        getEpisode: (timestamp, direction) =>
            route = "station/episode/#{direction}/#{timestamp}"
            $.get route, @renderScheduleItem

        nextItem: (event) =>
            @$content = $(event.target).prev()
            timestamp = @$content.data "timestamp"
            @getEpisode timestamp, 'next'
            true

        prevItem: (event) =>
            @$content = $(event.target).next()
            timestamp = @$content.data "timestamp"
            @getEpisode timestamp, 'prev'
            true
) jQuery
