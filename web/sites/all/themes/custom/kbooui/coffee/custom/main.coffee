(($) ->
    class App.Main extends C4.Components.Base
        init: ->
            super()
            C4.Utilities.Truncate.truncate()
            C4.Utilities.Window.resize C4.Utilities.Truncate.truncate
            App.Schedule.OnAir.watch()

            new App.Schedule.Carousel()
            true

    $ ->
        new App.Main()
        true
) jQuery
