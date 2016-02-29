(($) ->
  class App.Station.Playlists extends C4.Components.Base
    $el: null
    route: "/api/playlists"

    init: =>
      super()
      @$el = $ ".playlists"

      @renderHeader()
      C4.Utilities.Timer.delay @refresh, 1000, "playlists_init"
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
          col: "Time"
      ]

      @$el.find("thead tr").render template_data
      true

    renderOnAir: (response) =>
      return if response.length == 0

      template_data = []
      for playlist in response
        for track in playlist["Songs"]
          template_data.push
            artist: track["ArtistName"]
            title: track["SongName"]
            album: track["DiskName"]
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
