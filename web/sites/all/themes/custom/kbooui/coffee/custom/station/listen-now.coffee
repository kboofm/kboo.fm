(($) ->
  class App.Station.ListenNow extends C4.Components.Base
    button: ".launch-player"
    maxWidth: 768
    maxHeight: 840
    popupParams: "toolbar=yes,location=no,directories=no,status=no,menubar=yes,scrollbars=yes"

    bind: ->
      @bindItem 'click', @button, @onClick
      true

    onClick: (event) =>
      event.preventDefault()
      @launch()
      true

    launch: =>
      deviceWidth = window.screen.width
      deviceWidth = @maxWidth if deviceWidth > @maxWidth

      deviceHeight = window.screen.height
      deviceHeight = @maxHeight if deviceHeight > @maxHeight

      if deviceWidth == @maxWidth
        deviceWidth += @getScrollbarWidth()
        deviceHeight -= 18
        params = "width=#{deviceWidth},height=#{deviceHeight},#{@popupParams}"

      url = "/listen-now"
      window.open url, "player", params
      true

    getScrollbarWidth: =>
      div = document.createElement "div"
      div.innerHTML = """
  <div style="width:50px;height:50px;position:absolute;left:-50px;top:-50px;overflow:auto;">
    <div style="width:1px;height:100px;"></div>
  </div>
"""
      div = div.firstChild
      document.body.appendChild div
      width = div.offsetWidth - div.clientWidth
      document.body.removeChild div
      return width + 20

) jQuery
