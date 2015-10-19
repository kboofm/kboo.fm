window.App.Schedule = window.App.Schedule || {}

(($) ->
    class App.Schedule.Carousel extends C4.Components.Base
        nextButton: ".schedule-carousel-next i"
        prevButton: ".schedule-carousel-prev i"
        carousel_timestamp: ".schedule-carousel-timestamp"
        $content: null

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

        change: (event, direction) =>
            $button = $(event.target).parent()
            carousel_id = $button.data "carousel"
            @$content = $ "##{carousel_id}"

            timestamp = @$content.find(@carousel_timestamp).attr "data-timestamp"
            type = @$content.attr "data-type"

            @getEpisode timestamp, direction if type == 'episode'
            @getDay timestamp, direction if type == 'day'
            @getWeek timestamp, direction if type == 'week'
            true

        getEpisode: (timestamp, direction) =>
            route = "station/episode/#{direction}/#{timestamp}"
            $.get route, @renderEpisode
            true

        getDay: (timestamp, direction) =>
            route = "station/day/#{direction}/#{timestamp}"
            $.get route, @renderDay
            true

        getWeek: (timestamp, direction) =>
#            route = "station/week/#{direction}/#{timestamp}"
#            $.get route, @renderWeek
            true

        dataItem: (item) ->
            data_item =
                "timestamp": item['start']['timestamp']
                "schedule-item":
                    "title-link": item['title']
                    "formatted-date": item['start']['formatted_date']
                    "formatted-time":
                        "start-time": item['start']['formatted_time']
                        "finish-time": item['finish']['formatted_time']
            return data_item

        renderEpisode: (response) =>
            return if response.length == 0

            data = @dataItem response[0]
            directives =
                "schedule-carousel-timestamp":
                    "data-timestamp": -> "#{@timestamp}"

            @$content.render data, directives
            true

        renderDay: (response) =>
            return if response.length == 0

            data =
                timestamp: response[0]['start']['timestamp']
                "schedule-items": []

            for item in response
                data_item = @dataItem item
                data['schedule-items'].push data_item

            directives =
                "schedule-carousel-timestamp":
                    "data-timestamp": -> "#{@timestamp}"

            @$content.render data, directives
            true

        renderWeek: (response) =>
#            return if response.length == 0
#
#            weekdays = []
#            for weekday of response
#                data =
#                    items: []
#
#                for item in response[weekday]
#                    data_item = @dataItem item
#                    data.items.push data_item
#
#                weekdata =
#                    timestamp: response[weekday][0]['start']['timestamp']
#                    data: data
#
#                weekdays.push weekdata
#
#            directives =
#                "schedule-carousel-timestamp":
#                    "data-timestamp": -> "#{@timestamp}"
#
#            @$content.render weekdays, directives
            return true

) jQuery
