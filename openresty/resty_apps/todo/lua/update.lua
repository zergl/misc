
local function do_add(args)
    local _title   = args.title
    local _author   = args.author
    local _content  = args.content

    ngx.say("author: ", _author, "<br>")
    ngx.say("title: ", _title, "<br>")
    ngx.say("content: ", _content, "<br>")
    ngx.say("<br>------------<br>")
 
    if _author == nil then
        ret, err = false, "'author' is invalid."
    end

    if _title == nil then
        ret, err = false, "title is invalid."
    end

    if _content == nill then
        ret, err = false, "content is invalid"
    end

    ngx.say("date: ", os.date("%Y-%m-%d %H:%M:%S"))
    ngx.say("<br>")
    return true, "add succ.", "add succ."
end

local function do_del(args)
    for k,v in pairs(args) do
        ngx.say("[del] ", k, "-> ", v, "<br>")
    end
    return true, "del succ.", "del succ."
end

local function do_update(args)
    for k,v in pairs(args) do
        ngx.say("[update] ", k, "-> ", v, "<br>")
    end
    return true, "update succ.", "update succ."
end

-- export module apis
--[[
local _m = {}
_m.add  = do_add
_m.del  = do_del 
_m.update = do_update
--]]
--
--[[
local _m = {
    ["add"] = do_add,
    ["del"] = do_del,
    ["update"] = do_update
}
--]]
local _m = {add = do_add, del = do_del, update = do_update}
return _m
