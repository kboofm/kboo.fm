(($) ->
    class App.Modules.Organization extends C4.Components.Base
        divOrganizationType: "#edit-field-organization-type-und"
        verticalTabs: ".vertical-tab-button"

        init: ->
            super()
            @$venueTab = $ @verticalTabs
                .find "a:contains('Venue')"
                .parent()

            @$venueCheckbox = $ @divOrganizationType
                .find "label:contains('Venue')"
                .parent()
                .find "input"

            @toggleVenueTab()
            true

        bind: ->
            @bindToObject "change", @$venueCheckbox, @venueCheckboxChange
            true

        toggleVenueTab: ->
            if @$venueCheckbox[0].checked
                @$venueTab.show()
            else
                @$venueTab.hide()
            true

        venueCheckboxChange: (event) =>
            @toggleVenueTab()
            true


    $ ->
        new App.Modules.Organization()
        true
) jQuery
