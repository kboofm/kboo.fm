(($) ->
    class C4.Utilities.Truncate
        @truncated_elements: ".truncate"

        @truncate: ($parent) =>
            $parent = $(document) if typeof($parent) == 'undefined'
            $collection = $parent.find @truncated_elements
            $collection.each @truncateElement

        @truncateElement: (index, element) ->
            $element = $ element

            lines = 1
            if $element.data('truncate-lines')?
                lines = $element.data 'truncate-lines'

            $element.trunk8
                lines: lines

            true
) jQuery
