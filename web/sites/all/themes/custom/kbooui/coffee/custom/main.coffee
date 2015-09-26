(($) ->
    class App.Main extends C4.Components.Base
        init: ->
            super()
            C4.Utilities.Truncate.truncate()
            C4.Utilities.Window.resize C4.Utilities.Truncate.truncate

            new C4.Components.Dropdown()
            new C4.Components.Yamm()

            true

    $ ->
        new App.Main()
        true
) jQuery
