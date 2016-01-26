(($) ->
  class App.Player.Audio
    swfPath: "/sites/all/themes/custom/kbooui/bower_components/jPlayer/dist/jplayer/jquery.jplayer.swf"

    constructor: (@wrapper) ->
      $wrapper = $ @wrapper
      $player = $wrapper.find ".jp-jplayer"

      container = $wrapper
        .find ".jp-audio"
        .attr "id"

      endpoint = $player.attr "data-endpoint"

      $player.jPlayer
        cssSelectorAncestor: "##{container}",
        swfPath: @swfPath,
        supplied: "mp3"
        preload: "none",
        wmode: "window",
        smoothPlayBar: true,
        keyEnabled: true

        ready: ->
          $(@).jPlayer "setMedia", {mp3: endpoint}

        play: ->
          $(@).jPlayer "pauseOthers"

      true
) jQuery
