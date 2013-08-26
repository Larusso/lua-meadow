local dire = require 'direwolf'
local pretty = require 'pl.pretty'
-- pretty.dump(pretty)
pretty.dump(dire)

local mediator = dire.Mediator:new()
local mediator2 = dire.Mediator:new()


mediator.doit = function(self)
    print("I did it")
end


pretty.dump(mediator)
pretty.dump(getmetatable(mediator))
mediator:print()

local mediator3 = mediator:new()
mediator3:print()
mediator3:move(20,40)
-- pretty.dump(mediator2)

-- mediator:doit()
-- error mediator2:doit()

mediator = nil
collectgarbage();
print(getmetatable(self))
