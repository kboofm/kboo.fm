(($) ->
  class App.Station.Playlists extends C4.Components.Base
    $el: null
    route: "/api/playlists"
    interval: 5 # in minutes

    init: =>
      super()
      @$el = $ ".playlists"
      @interval = @interval * 60 * 1000

      @renderHeader()
      C4.Utilities.Timer.delay @refresh, 1000, "playlists_init"
      C4.Utilities.Timer.repeat @refresh, @interval, "playlists_update"
      true

    refresh: =>
      jQuery.get @route, @renderOnAir
      true

    renderHeader: =>
      template_data = [
          col: "Artist"
        ,
          col: "Title"
        ,
          col: "Album"
        ,
          col: "Date"
        ,
          col: "Time"
      ]

      @$el.find("thead tr").render template_data
      true

    renderOnAir: (response) =>
      return if response.length == 0

      template_data = []
      for track in response
          template_data.push
            artist: track["ArtistName"]
            title: track["SongName"]
            album: track["DiskName"]
            date: track["Date"]
            time: track["Timestamp"]

      @$el.find("tbody").render template_data

      template_data =
        throbber: ""

      @$el.render template_data
      true

    $ ->
      new App.Station.Playlists()
      true

) jQuery
