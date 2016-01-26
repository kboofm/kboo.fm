(($) ->
  class App.Events.Tabs extends C4.Components.Base
    tabs: ".nav.nav-pills"

    init: ->
      super()
      C4.Utilities.Truncate.truncate $(@tabs)
      true

    bind: ->
      @bindItem "shown.bs.tab", @tabs, @tabChanged
      true

    tabChanged: (event) =>
      tab_pane = $(event.target).attr 'href'
      C4.Utilities.Truncate.truncate $(tab_pane)
      true
) jQuery
