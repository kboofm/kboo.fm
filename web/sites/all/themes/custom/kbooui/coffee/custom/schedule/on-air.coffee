window.App.Schedule = window.App.Schedule || {}

(($) ->
    class App.Schedule.OnAir
        @interval: 60 # in seconds
        @stream: null
        @$el: null

        @watch: =>
            @interval = @interval * 1000
            @$el = $ '.on-air'
            @stream = @$el.attr 'data-stream'

            callback = App.Schedule.OnAir.timeCheck
            C4.Utilities.Timer.repeat callback, @interval, "timeCheck"
            true

        @timeCheck: =>
            d = new Date()
            minutes = d.getMinutes()

            zero = (minutes == 0)
            five = (minutes %% 5) == 0

            if zero or five
                @refresh()

            true

        @refresh: =>
            timestamp = Date.now() // 1000
            route = "/station/episode/#{@stream}/at/#{timestamp}"
            $.get route, App.Schedule.OnAir.renderOnAir
            true

        @dataItem: (item) ->
            data_item =
                "title-link": item['title']
            data_item

        @renderOnAir: (response) =>
            return if response.length == 0

            data = @dataItem response[0]
            @$el.render data
            true

) jQuery
