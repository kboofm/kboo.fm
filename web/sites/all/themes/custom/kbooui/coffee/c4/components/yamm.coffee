class C4.Components.Yamm extends C4.Components.Base
    yamm: '.yamm .dropdown-menu'

    bind: ->
        @addItem "click", @yamm, @yammClick
        true

    yammClick: (event) =>
        event.stopPropagation()
        true
