window.C4.Components.Carousel ?= {}

(($) ->
    class C4.Components.Carousel.OutsideIndicators extends C4.Components.Base
        carousel_item: '.carousel-item'
        indicator: '.indicator-item'
        indicators: '.carousel-indicators'

        bind: ->
            @bindItem "slid.bs.carousel", @carouselSlid
            @bindItem "click", @indicator, @indicatorClick
            true

        indicatorClick: (event) =>
            event.preventDefault()
            slide_to = parseInt $(@).attr("data-slide-to")
            @$carousel.carousel slide_to
            $(@indicator + ".active").removeClass "active"
            $(event.currentTarget).addClass "active"
            true

        carouselSlid: =>
            $active_item = $(@carousel_item + ".active")
            slide_no = $active_item.attr "data-slide-no"
            $(@indicator + ".active").removeClass "active"
            $("#{@indicators} [data-slide-to=#{slide_no}]").addClass "active"
            true
) jQuery
