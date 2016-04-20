(($) ->
  class App.Player.Live extends C4.Components.Base
    activeStream: null
    params: null
    defaultProgramLabel: "Who's On:"
    wrapper: "#station-audio-wrapper"
    swfPath: "/sites/all/themes/custom/kbooui/bower_components/jPlayer/dist/jplayer/jquery.jplayer.swf"
    updateInterval: 1 # minute

    streams:
      one:
        route: "http://live.kboo.fm:8000/high"
        title: "KBOO"
        programLabel: ""
        programDefault: ""
        program: null
        time: null
        $el: null

    $active: null
    $player: null
    $programInfo: null

    init: ->
      super()

      # convert from minutes to miliseconds
      minute = 60000
      @updateInterval *= minute

      $wrapper = $ @wrapper
      @$player = $wrapper.find ".jp-jplayer"

      container = $wrapper
      .find ".jp-audio"
      .attr "id"

      @$programInfo = $ ".program-info"

      @$player.jPlayer
        cssSelectorAncestor: "##{container}",
        swfPath: @swfPath,
        preload: "none",
        wmode: "window",

      C4.Utilities.Timer.delay @updatePrograms, 1000, "audio_player_init_update"
      C4.Utilities.Timer.repeat @timeCheck, @updateInterval, "audio_player_repeat_update"

      @changeStream "one"
      true

    changeStream: (requestedStream) =>
      @active = requestedStream
      @play @streams[requestedStream].route
      @renderActiveProgram()
      true

    renderActiveProgram: =>
      return unless @active?

      template_data =
        label: @streams[@active].programLabel
        title: @streams[@active].program
        time: @streams[@active].time

      @$programInfo.render template_data
      true

    renderPrograms: =>
      @renderActiveProgram()
      true

    timeCheck: =>
      d = new Date()
      minutes = d.getMinutes()

      zero = (minutes == 0)
      five = (minutes %% 5) == 0

      if zero or five
        @updatePrograms()

      true

    updatePrograms: =>
      timestamp = Date.now() // 1000
      @updateProgramForStream "one", timestamp
      true

    updateProgramForStream: (stream, timestamp) =>
      route = "/api/schedule/episode/#{stream}/at/#{timestamp}"

      params =
        type: "GET"
        url: route
        datatype: "json"
        success: (response) =>
          @processProgramsResponse response, key

      jQuery.ajax params
      true

    processProgramsResponse: (response, key) =>
      @streams[key].programLabel = @defaultProgramLabel
      @streams[key].program = @streams[key].programDefault
      @streams[key].time = ""

      unless response.length == 0
        @streams[key].program = response[0].title
        @streams[key].time = response[0].start.formatted_time

      @renderPrograms()
      true

    play: (endpoint) ->
      @$player.jPlayer "setMedia", {mp3: endpoint}
      @$player.jPlayer "play"
      true

  $ ->
    new App.Player.Live()
    true
) jQuery
