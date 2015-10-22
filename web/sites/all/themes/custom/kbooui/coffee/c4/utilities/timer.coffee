class C4.Utilities.Timer
    @timers: {}

    # Delay the execution of a function
    # http://stackoverflow.com/a/4541963/2407209
    @delay: (callback, ms, unique_id) =>
        @clearTimer unique_id
        @timers[unique_id] = setTimeout callback, ms
        true

    @repeat: (callback, ms, unique_id) =>
        @clearTimer unique_id
        @timers[unique_id] = setInterval callback, ms
        true

    @clearTimer: (unique_id) =>
        unless unique_id?
            throw "Unique id required but not provided"

        if unique_id in @timers
            clearTimeout @timers[unique_id]
