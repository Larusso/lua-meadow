obj = {}

function obj:execute()
    print('execute in external file')
    local mediator = direwolf.Mediator()
    print(mediator)
end

return obj