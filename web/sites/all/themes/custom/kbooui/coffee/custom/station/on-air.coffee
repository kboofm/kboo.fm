(($) ->
  class App.Station.OnAir
    @interval: 60 # in seconds
    @stream: null
    @$el: null

    @watch: =>
      @interval = @interval * 1000
      @$el = $ '.on-air'
      @stream = @$el.attr 'data-stream'

      callback = App.Station.OnAir.timeCheck
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
      route = "/api/schedule/episode/#{@stream}/at/#{timestamp}"
      $.get route, App.Station.OnAir.renderOnAir
      true

    @dataItem: (item) ->
      data_item =
        "program":
          "text": item['title']
          "href": item['url']
        "showhost":
          "text": item['showhost']['name']
          "href": item['showhost']['url']
      data_item

    @renderOnAir: (response) =>
      return if response.length == 0
      data = @dataItem response[0]

      directives =
        "title-link":
          "text": -> @program.text
          "href": -> @program.href
        "showhost-link":
          "text": -> @showhost.text
          "href": -> @showhost.href

      @$el.render data, directives
      true
) jQuery
