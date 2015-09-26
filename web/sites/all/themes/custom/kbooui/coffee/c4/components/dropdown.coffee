(($) ->
    class C4.Components.Dropdown extends C4.Components.Base
        dropdown: ".c4-dropdown"

        bind: ->
            @bindItem "shown.bs.dropdown", @dropdown, @dropdownShown
            true

        dropdownShown: (event) =>
            C4.Utilities.Truncate.truncate $(event.target)
            true
) jQuery
