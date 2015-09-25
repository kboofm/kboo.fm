(($) ->
    class C4.Components.Base
        constructor: ->
            @init()
            @bind()

        init: ->
            @$document = $ document
            true

        bind: ->
            true

        addItem: (event, selector, callback) ->
            @bindItem event, selector, callback, true

        bindItem: (event, selector, callback, ignoreOff = false) ->
            unless callback?
                callback = selector
                @$document.off event unless ignoreOff
                @$document.on event, callback
            else
                @$document.off event, selector unless ignoreOff
                @$document.on event, selector, callback

        bindToObject: (event, $object, callback, ignoreOff = false) ->
            $object.off event unless ignoreOff
            $object.on event, callback
) jQuery
