(($) ->
    class C4.Utilities.Window
        @resize: (callback) =>
            $(window).resize =>
                C4.Utilities.Timer.delay callback, 500, "c4_window"
            true
) jQuery
