%module direwolf;

%include "DWMediator.h"
%include "DWController.h"

%luacode {
    print('copy direwolf in global namespace')
    
    -- could copy all functions from direwolf to global
    -- for k,v in pairs(direwolf) do _G[k]=v end
    
    -- or set metatable for _G
    
    mt = {}
    mt.__index = direwolf
    
    print(getmetatable(_G))
    setmetatable(_G,mt)
}